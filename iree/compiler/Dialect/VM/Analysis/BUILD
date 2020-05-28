package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

cc_library(
    name = "Analysis",
    srcs = [
        "RegisterAllocation.cpp",
        "RegisterAllocationTest.cpp",
        "ValueLiveness.cpp",
        "ValueLivenessTest.cpp",
    ],
    hdrs = [
        "RegisterAllocation.h",
        "TestPasses.h",
        "ValueLiveness.h",
    ],
    deps = [
        "//iree/compiler/Dialect/IREE/IR",
        "//iree/compiler/Dialect/VM/IR",
        "@llvm_project//llvm:support",
        "@llvm_project//mlir:Analysis",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:Pass",
        "@llvm_project//mlir:Support",
    ],
)
