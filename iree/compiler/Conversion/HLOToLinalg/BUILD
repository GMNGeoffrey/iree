# Copyright 2020 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

cc_library(
    name = "HLOToLinalg",
    srcs = [
        "DecomposeHLOClamp.cpp",
        "HLOToLinalgOnBuffers.cpp",
        "HLOToLinalgOnTensors.cpp",
        "LinalgFusion.cpp",
        "Passes.cpp",
        "ResolveShapeOps.cpp",
    ],
    hdrs = [
        "Passes.h",
    ],
    deps = [
        "//iree/compiler/Conversion/CodegenUtils",
        "//iree/compiler/Dialect/HAL/IR",
        "//iree/compiler/Dialect/HAL/IR:HALDialect",
        "//iree/compiler/Dialect/IREE/IR",
        "//iree/compiler/Dialect/Shape/IR",
        "@llvm_project//llvm:support",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:LinalgOps",
        "@llvm_project//mlir:LinalgTransforms",
        "@llvm_project//mlir:Pass",
        "@llvm_project//mlir:SPIRVDialect",
        "@llvm_project//mlir:StandardOps",
        "@llvm_project//mlir:Support",
        "@llvm_project//mlir:Transforms",
        "@org_tensorflow//tensorflow/compiler/mlir/xla:hlo",
        "@org_tensorflow//tensorflow/compiler/mlir/xla:map_xla_to_scalar_op",
    ],
)
