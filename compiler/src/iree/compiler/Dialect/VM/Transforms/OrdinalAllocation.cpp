// Copyright 2019 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/compiler/Dialect/VM/IR/VMOps.h"
#include "iree/compiler/Dialect/VM/Transforms/Passes.h"
#include "llvm/ADT/ArrayRef.h"
#include "mlir/Dialect/Affine/Utils.h"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Support/LogicalResult.h"

namespace mlir {
namespace iree_compiler {
namespace IREE {
namespace VM {

// Assigns per-category ordinals to module-level symbols in the module.
// Each ordinal is unique per-category and ordinals are contiguous starting from
// zero.
//
// NOTE: symbols are serialized in ordinal-order (hence the name!) and we have
// an opportunity here to set the layout of the final binaries, similar to how
// old-timey games would layout files on their spinning plastic discs to
// optimize the time spent moving a physical laser carridge around. Functions
// related to each other and global data accessed in proximity should be
// clustered together to make use of paging in memory mapped files.
class OrdinalAllocationPass
    : public PassWrapper<OrdinalAllocationPass, OperationPass<ModuleOp>> {
 public:
  StringRef getArgument() const override {
    return "iree-vm-ordinal-allocation";
  }

  StringRef getDescription() const override {
    return "Assigns ordinals to function and global symbols";
  }

  void runOnOperation() override {
    Builder builder(&getContext());

    // Assign ordinals based on IR order (which should be deterministic).
    int nextFuncOrdinal = 0;
    int nextImportOrdinal = 0;
    int nextExportOrdinal = 0;
    int nextGlobalRefOrdinal = 0;
    int nextRodataOrdinal = 0;
    SmallVector<SmallVector<VMGlobalOp, 4>, 8> primitiveGlobalOps(
        sizeof(int64_t) + 1);
    for (auto &op : getOperation().getBlock().getOperations()) {
      Optional<int> ordinal = llvm::None;
      if (auto funcOp = dyn_cast<FuncOp>(op)) {
        ordinal = nextFuncOrdinal++;
      } else if (isa<ExportOp>(op)) {
        ordinal = nextExportOrdinal++;
      } else if (isa<ImportOp>(op)) {
        ordinal = nextImportOrdinal++;
      } else if (isa<RodataOp>(op)) {
        ordinal = nextRodataOrdinal++;
      } else if (isa<GlobalRefOp>(op)) {
        ordinal = nextGlobalRefOrdinal++;
      } else if (auto globalOp = dyn_cast<VMGlobalOp>(op)) {
        // Bucket the primitive global ops (like vm.global.i32) so we can
        // run over all of them below.
        primitiveGlobalOps[globalOp.getStorageSize()].push_back(globalOp);
        continue;
      }
      if (ordinal.hasValue()) {
        op.setAttr("ordinal", builder.getI32IntegerAttr(ordinal.getValue()));
      }
    }

    // Assign byte offset values to primitive globals, ensuring that we meet
    // natural alignment requirements on each size type.
    int nextGlobalBytesOrdinal = 0;
    int globalBytes = 0;
    for (auto sizeGlobalOps : llvm::enumerate(primitiveGlobalOps)) {
      size_t storageSize = sizeGlobalOps.index();
      if (sizeGlobalOps.value().empty()) continue;
      nextGlobalBytesOrdinal =
          llvm::alignTo(nextGlobalBytesOrdinal, storageSize);
      for (auto &globalOp : sizeGlobalOps.value()) {
        globalOp->setAttr("ordinal",
                          builder.getI32IntegerAttr(nextGlobalBytesOrdinal));
        nextGlobalBytesOrdinal += storageSize;
        globalBytes = std::max(globalBytes, nextGlobalBytesOrdinal);
      }
    }

    // Assign ordinal counts to module op.
    getOperation().ordinal_countsAttr(OrdinalCountsAttr::get(
        &getContext(), nextImportOrdinal, nextExportOrdinal, nextFuncOrdinal,
        globalBytes, nextGlobalRefOrdinal, nextRodataOrdinal, 0));

    SymbolTable symbolTable(getOperation());

    // Convert all global address pseudo-ops to constants referencing the
    // ordinals we just assigned.
    SmallVector<Operation *, 32> deadOps;
    getOperation().walk([&](IREE::VM::GlobalAddressOp op) {
      auto *globalOp = symbolTable.lookupNearestSymbolFrom(op, op.globalAttr());
      assert(globalOp);
      auto ordinal = globalOp->getAttrOfType<IntegerAttr>("ordinal").getInt();

      OpBuilder builder(op);
      auto ordinalOp =
          builder.create<IREE::VM::ConstI32Op>(op.getLoc(), ordinal);
      op.result().replaceAllUsesWith(ordinalOp);

      deadOps.push_back(op);
    });
    for (auto *deadOp : deadOps) {
      deadOp->erase();
    }
  }
};

std::unique_ptr<OperationPass<ModuleOp>> createOrdinalAllocationPass() {
  return std::make_unique<OrdinalAllocationPass>();
}

static PassRegistration<OrdinalAllocationPass> pass;

}  // namespace VM
}  // namespace IREE
}  // namespace iree_compiler
}  // namespace mlir