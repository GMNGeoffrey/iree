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
    name = "ModelBuilder",
    srcs = ["ModelBuilder.cpp"],
    hdrs = ["ModelBuilder.h"],
    tags = [
        "noga",
    ],
    deps = [
        "@llvm_project//mlir:Affine",
        "@llvm_project//mlir:EDSC",
        "@llvm_project//mlir:GPUDialect",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:LinalgOps",
        "@llvm_project//mlir:LinalgTransforms",
        "@llvm_project//mlir:SCFDialect",
        "@llvm_project//mlir:SCFTransforms",
        "@llvm_project//mlir:SPIRVDialect",
        "@llvm_project//mlir:StandardOps",
        "@llvm_project//mlir:VectorOps",
    ],
)

cc_library(
    name = "VulkanLaunchWrapper",
    srcs = ["VulkanWrapperPass.cpp"],
    hdrs = ["VulkanWrapperPass.h"],
    tags = [
        "noga",
    ],
    deps = [
        "@llvm_project//llvm:support",
        "@llvm_project//mlir:ConversionPassIncGen",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:LLVMDialect",
        "@llvm_project//mlir:Pass",
        "@llvm_project//mlir:SPIRVDialect",
        "@llvm_project//mlir:SPIRVSerialization",
        "@llvm_project//mlir:StandardOps",
        "@llvm_project//mlir:Support",
    ],
)

cc_library(
    name = "ModelRunner",
    srcs = ["ModelRunner.cpp"],
    hdrs = [
        "MemRefUtils.h",
        "ModelRunner.h",
    ],
    linkopts = [
        "-ldl",
    ],
    tags = [
        "noga",
    ],
    deps = [
        ":ModelBuilder",
        "@llvm_project//llvm:support",
        "@llvm_project//mlir:ExecutionEngine",
        "@llvm_project//mlir:ExecutionEngineUtils",
        "@llvm_project//mlir:GPUToSPIRVTransforms",
        "@llvm_project//mlir:GPUToVulkanTransforms",
        "@llvm_project//mlir:GPUTransforms",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:LLVMTransforms",
        "@llvm_project//mlir:LinalgToLLVM",
        "@llvm_project//mlir:LinalgTransforms",
        "@llvm_project//mlir:Pass",
        "@llvm_project//mlir:SPIRVDialect",
        "@llvm_project//mlir:StandardToSPIRVConversions",
        "@llvm_project//mlir:TargetLLVMIR",
        "@llvm_project//mlir:TransformUtils",
        "@llvm_project//mlir:VectorOps",
        "@llvm_project//mlir:VectorToLLVM",
        "@llvm_project//mlir:VectorToSCF",
        "@llvm_project//mlir:mlir_c_runner_utils",
    ],
)
