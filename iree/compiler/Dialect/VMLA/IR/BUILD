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

load("//build_tools/bazel:iree_tablegen_doc.bzl", "iree_tablegen_doc")
load("//build_tools/bazel:tblgen.bzl", "gentbl")

package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],  # Apache 2.0
)

exports_files(["VMLAOps.td"])

filegroup(
    name = "td_files",
    srcs = glob(["*.td"]),
)

cc_library(
    name = "IR",
    srcs = [
        "VMLAEnums.cpp.inc",
        "VMLAOpInterface.cpp.inc",
        "VMLAOps.cpp",
        "VMLATypes.cpp",
    ],
    hdrs = [
        "VMLAEnums.h.inc",
        "VMLAOpInterface.h.inc",
        "VMLAOps.h",
        "VMLAOps.h.inc",
        "VMLATraits.h",
        "VMLATypes.h",
    ],
    textual_hdrs = [
        "VMLAOps.cpp.inc",
    ],
    deps = [
        ":VMLAEnumsGen",
        ":VMLAOpInterfaceGen",
        ":VMLAOpsGen",
        "//iree/compiler/Dialect/IREE/IR",
        "//iree/compiler/Dialect/Shape/IR",
        "//iree/compiler/Dialect/VM/IR",
        "@llvm_project//llvm:support",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:SideEffects",
        "@llvm_project//mlir:StandardOps",
        "@llvm_project//mlir:Support",
        "@llvm_project//mlir:TransformUtils",
        "@llvm_project//mlir:Translation",
    ],
)

cc_library(
    name = "VMLADialect",
    srcs = ["VMLADialect.cpp"],
    hdrs = ["VMLADialect.h"],
    deps = [
        ":IR",
        "//iree/compiler/Dialect/VM/Conversion",
        "//iree/compiler/Dialect/VMLA:vmla_imports",
        "//iree/compiler/Dialect/VMLA/Conversion/VMLAToVM",
        "@llvm_project//llvm:support",
        "@llvm_project//mlir:IR",
        "@llvm_project//mlir:Parser",
        "@llvm_project//mlir:StandardOps",
        "@llvm_project//mlir:Support",
        "@llvm_project//mlir:TransformUtils",
    ],
)

gentbl(
    name = "VMLAEnumsGen",
    tbl_outs = [
        ("-gen-enum-decls", "VMLAEnums.h.inc"),
        ("-gen-enum-defs", "VMLAEnums.cpp.inc"),
    ],
    tblgen = "@llvm_project//mlir:mlir-tblgen",
    td_file = "VMLABase.td",
    td_srcs = [
        ":td_files",
        "//iree/compiler/Dialect/IREE/IR:td_files",
        "//iree/compiler/Dialect/Shape/IR:td_files",
        "@llvm_project//mlir:OpBaseTdFiles",
        "@llvm_project//mlir:StdOpsTdFiles",
    ],
)

gentbl(
    name = "VMLAOpsGen",
    tbl_outs = [
        ("-gen-op-decls", "VMLAOps.h.inc"),
        ("-gen-op-defs", "VMLAOps.cpp.inc"),
    ],
    tblgen = "@llvm_project//mlir:mlir-tblgen",
    td_file = "VMLAOps.td",
    td_srcs = [
        ":td_files",
        "//iree/compiler/Dialect/IREE/IR:td_files",
        "//iree/compiler/Dialect/Shape/IR:td_files",
        "@llvm_project//mlir:OpBaseTdFiles",
        "@llvm_project//mlir:StdOpsTdFiles",
    ],
)

gentbl(
    name = "VMLAOpInterfaceGen",
    tbl_outs = [
        ("-gen-op-interface-decls", "VMLAOpInterface.h.inc"),
        ("-gen-op-interface-defs", "VMLAOpInterface.cpp.inc"),
    ],
    tblgen = "@llvm_project//mlir:mlir-tblgen",
    td_file = "VMLABase.td",
    td_srcs = [
        ":td_files",
        "//iree/compiler/Dialect/IREE/IR:td_files",
        "//iree/compiler/Dialect/Shape/IR:td_files",
        "@llvm_project//mlir:OpBaseTdFiles",
    ],
)

iree_tablegen_doc(
    name = "VMLADialecDocGen",
    tbl_outs = [
        ("-gen-dialect-doc", "VMLADialect.md"),
    ],
    tblgen = "@llvm_project//mlir:mlir-tblgen",
    td_file = "VMLAOps.td",
    td_srcs = [
        ":td_files",
        "//iree/compiler/Dialect/IREE/IR:td_files",
        "//iree/compiler/Dialect/Shape/IR:td_files",
        "@llvm_project//mlir:OpBaseTdFiles",
        "@llvm_project//mlir:StdOpsTdFiles",
    ],
)
