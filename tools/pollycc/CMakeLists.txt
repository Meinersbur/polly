
macro(add_polly_executable name)
  add_llvm_executable(${name} ${ARGN})
  set_target_properties(${name} PROPERTIES FOLDER "Polly")
endmacro(add_polly_executable)

set(CLANG_SOURCE_DIR "${LLVM_MAIN_SRC_DIR}/../clang")
set(CLANG_BINARY_DIR "${POLLY_BINARY_DIR}/../clang")
include_directories("${CLANG_BINARY_DIR}/include" "${CLANG_SOURCE_DIR}/include")

set(LLVM_LINK_COMPONENTS
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
  )
  
set(LLVM_LINK_LIBS
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
  clangSema
  clangSerialization
)

if(CLANG_ENABLE_STATIC_ANALYZER)
  list(APPEND LLVM_LINK_LIBS
    clangStaticAnalyzerFrontend
    clangStaticAnalyzerCheckers
    clangStaticAnalyzerCore
    )
endif()

if(CLANG_ENABLE_ARCMT)
  list(APPEND LLVM_LINK_LIBS
    clangARCMigrate
    )
endif()

if(CLANG_ENABLE_REWRITER)
  list(APPEND LLVM_LINK_LIBS
    clangRewriteCore
    clangRewriteFrontend
    )
endif()

add_polly_executable(pollycc
  SOURCES
    driver.cpp 
    cc1as_main.cpp 
    cc1_main.cpp
  TARGET_DEPENDS 
    clang-headers 
    intrinsics_gen
#  LINK_COMPONENTS 
#    ${LLVM_TARGETS_TO_BUILD}
#    asmparser
#    bitreader
#    bitwriter
#    irreader
#    codegen
#    instrumentation
#    ipo
#    linker
#    selectiondag
  LINK_LIBS 
    PollyAnalysis # Once more because of back references
    LLVMPolly
)
