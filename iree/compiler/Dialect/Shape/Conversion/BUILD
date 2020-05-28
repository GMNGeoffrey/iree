package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

cc_library(
    name = "ConvertShapeToShapex",
    srcs = ["ConvertShapeToShapex.cpp"],
    deps = [
        "//iree/compiler/Dialect/Shape/IR",
        "@llvm_project//mlir:Dialect",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:Pass",
        "@llvm_project//mlir:Shape",
        "@llvm_project//mlir:Transforms",
    ],
)

cc_library(
    name = "Conversion",
    hdrs = ["Passes.h"],
    deps = [
        ":ConvertShapeToShapex",
        "@llvm_project//mlir:Pass",
    ],
)
