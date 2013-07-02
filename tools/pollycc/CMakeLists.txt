
macro(add_polly_executable name)
  add_llvm_executable(${name} ${ARGN})
  set_target_properties(${name} PROPERTIES FOLDER "Polly")
endmacro(add_polly_executable)

set(CLANG_SOURCE_DIR "${LLVM_MAIN_SRC_DIR}/../clang")
set(CLANG_BINARY_DIR "${POLLY_BINARY_DIR}/../clang")
message("CLANG_SOURCE_DIR: ${CLANG_SOURCE_DIR}")
include_directories("${CLANG_BINARY_DIR}/include" "${CLANG_SOURCE_DIR}/include")

add_polly_executable(pollycc
  SOURCES
    driver.cpp 
    cc1as_main.cpp 
    cc1_main.cpp
  TARGET_DEPENDS 
    clang-headers 
    intrinsics_gen
  LINK_COMPONENTS 
    ${LLVM_TARGETS_TO_BUILD}
    asmparser
    bitreader
    bitwriter
    irreader
    codegen
    instrumentation
    ipo
    linker
    selectiondag
  LINK_LIBS 
    LLVMPolly
#    PollyAnalysis
    clangFrontendTool 
    clangAST 
    clangAnalysis 
    clangBasic 
    clangCodeGen 
    clangDriver 
    clangEdit 
    clangFrontend 
    clangLex 
    clangParse 
    clangEdit 
    clangARCMigrate 
    clangRewriteCore 
    clangRewriteFrontend 
    clangSema 
    clangSerialization 
    clangStaticAnalyzerFrontend 
    clangStaticAnalyzerCheckers 
    clangStaticAnalyzerCore 
)
