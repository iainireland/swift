//===--- SemaFixture.h - Helper for setting up Sema context -----*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2020 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#include "swift/AST/ASTContext.h"
#include "swift/AST/DiagnosticEngine.h"
#include "swift/AST/Module.h"
#include "swift/AST/SourceFile.h"
#include "swift/AST/Type.h"
#include "swift/Basic/LangOptions.h"
#include "swift/Basic/Platform.h"
#include "swift/Basic/SourceManager.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/Path.h"
#include "gtest/gtest.h"
#include <string>

namespace swift {
namespace unittest {

class SemaTestBase : public ::testing::Test {
public:
  LangOptions LangOpts;
  TypeCheckerOptions TypeCheckerOpts;
  SearchPathOptions SearchPathOpts;
  ClangImporterOptions ClangImporterOpts;
  SourceManager SourceMgr;
  DiagnosticEngine Diags;

  SemaTestBase() : Diags(SourceMgr) {
    LangOpts.Target = llvm::Triple(llvm::sys::getDefaultTargetTriple());

    llvm::SmallString<128> libDir(SWIFTLIB_DIR);
    llvm::sys::path::append(libDir, getPlatformNameForTriple(LangOpts.Target));

    SearchPathOpts.RuntimeResourcePath = SWIFTLIB_DIR;
    SearchPathOpts.RuntimeLibraryPaths.push_back(std::string(libDir.str()));
    SearchPathOpts.RuntimeLibraryImportPaths.push_back(
        std::string(libDir.str()));
  }
};

/// Owns an ASTContext and the associated types.
class SemaTest : public SemaTestBase {
  SourceFile *MainFile;

public:
  ASTContext &Context;
  DeclContext *DC;

  SemaTest();

protected:
  Type getStdlibType(StringRef name) const;
};

} // end namespace unittest
} // end namespace swift
