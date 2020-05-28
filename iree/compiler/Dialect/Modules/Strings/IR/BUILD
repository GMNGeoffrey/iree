# Copyright 2019 Google LLC
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

load("//build_tools/bazel:iree_tablegen_doc.bzl", "iree_tablegen_doc")
load("//build_tools/bazel:tblgen.bzl", "gentbl")

package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

filegroup(
    name = "td_files",
    srcs = glob(["*.td"]),
)

cc_library(
    name = "IR",
    srcs = [
        "Ops.cc",
        "Ops.cc.inc",
    ],
    hdrs = [
        "Ops.h",
        "Ops.h.inc",
        "Types.h",
    ],
    deps = [
        ":Ops_gen",
        "//iree/compiler/Dialect/HAL/IR",
        "//iree/compiler/Dialect/IREE/IR",
        "//iree/compiler/Dialect/VM/Conversion",
        "@llvm_project//llvm:support",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:Parser",
        "@llvm_project//mlir:Pass",
        "@llvm_project//mlir:SideEffects",
        "@llvm_project//mlir:Support",
        "@llvm_project//mlir:Transforms",
    ],
)

cc_library(
    name = "Dialect",
    srcs = [
        "Dialect.cc",
    ],
    hdrs = [
        "Dialect.h",
    ],
    deps = [
        ":IR",
        ":Ops_gen",
        "//iree/compiler/Dialect/IREE/IR",
        "//iree/compiler/Dialect/Modules/Strings:strings_imports",
        "//iree/compiler/Dialect/Modules/Strings/Conversion",
        "//iree/compiler/Dialect/VM/Conversion",
        "@llvm_project//llvm:support",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:Parser",
        "@llvm_project//mlir:Pass",
        "@llvm_project//mlir:Support",
        "@llvm_project//mlir:Transforms",
    ],
)

gentbl(
    name = "Ops_gen",
    tbl_outs = [
        ("-gen-op-decls", "Ops.h.inc"),
        ("-gen-op-defs", "Ops.cc.inc"),
    ],
    tblgen = "@llvm_project//mlir:mlir-tblgen",
    td_file = "Ops.td",
    td_srcs = [
        ":td_files",
        "//iree/compiler/Dialect/HAL/IR:td_files",
        "//iree/compiler/Dialect/IREE/IR:td_files",
        "@llvm_project//mlir:StdOpsTdFiles",
    ],
)

iree_tablegen_doc(
    name = "DialectDocGen",
    tbl_outs = [
        ("-gen-dialect-doc", "StringsDialect.md"),
    ],
    tblgen = "@llvm_project//mlir:mlir-tblgen",
    td_file = "Ops.td",
    td_srcs = [
        ":td_files",
        "//iree/compiler/Dialect/HAL/IR:td_files",
        "//iree/compiler/Dialect/IREE/IR:td_files",
        "@llvm_project//mlir:StdOpsTdFiles",
    ],
)
