package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

cc_library(
    name = "StandardToVM",
    srcs = [
        "ConvertStandardToVM.cpp",
        "ConvertStandardToVMTest.cpp",
    ],
    hdrs = [
        "ConvertStandardToVM.h",
    ],
    deps = [
        "//iree/compiler/Dialect/IREE/IR",
        "//iree/compiler/Dialect/VM/Conversion",
        "//iree/compiler/Dialect/VM/IR",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:Pass",
        "@llvm_project//mlir:StandardOps",
        "@llvm_project//mlir:TransformUtils",
        "@llvm_project//mlir:Transforms",
    ],
)
