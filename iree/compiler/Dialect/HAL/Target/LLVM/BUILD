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
    name = "LLVM",
    srcs = [
        "LLVMTarget.cpp",
    ],
    hdrs = [
        "LLVMTarget.h",
    ],
    deps = [
        ":LLVMIRPasses",
        ":LLVMTargetOptions",
        "//iree/compiler/Conversion/LinalgToLLVM",
        "//iree/compiler/Dialect/HAL/Target",
        "//iree/schemas:llvmir_executable_def_cc_fbs",
        "@llvm_project//llvm:core",
        "@llvm_project//llvm:support",
        "@llvm_project//mlir:TargetLLVMIR",
        # TODO(ataei): Link with native target dep.
        "@llvm_project//llvm:x86_code_gen",
    ],
)

cc_library(
    name = "LLVMIRPasses",
    srcs = [
        "LLVMIRPasses.cpp",
    ],
    hdrs = [
        "LLVMIRPasses.h",
    ],
    deps = [
        ":LLVMTargetOptions",
        "@llvm_project//llvm:core",
        "@llvm_project//llvm:passes",
        "@llvm_project//llvm:support",
        "@llvm_project//llvm:target",
        "@llvm_project//mlir:Support",
    ],
)

cc_library(
    name = "LLVMTargetOptions",
    srcs = [
        "LLVMTargetOptions.cpp",
    ],
    hdrs = [
        "LLVMTargetOptions.h",
    ],
    deps = [
        "@llvm_project//llvm:passes",
        "@llvm_project//llvm:support",
    ],
)
