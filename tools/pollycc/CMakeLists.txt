macro(add_polly_executable name)
  add_llvm_executable(${name} ${ARGN})
  set_target_properties(${name} PROPERTIES FOLDER "Polly")
endmacro(add_polly_executable)

set(CLANG_SOURCE_DIR "${LLVM_MAIN_SRC_DIR}/../clang")
set(CLANG_BINARY_DIR "${POLLY_BINARY_DIR}/../clang")
include_directories("${CLANG_BINARY_DIR}/include" "${CLANG_SOURCE_DIR}/include")


set( LLVM_LINK_COMPONENTS
  ${LLVM_TARGETS_TO_BUILD}
  Analysis
  Core
  IPA
  IPO
  InstCombine
  Instrumentation
  MC
  MCParser
  ObjCARCOpts
  Option
  ScalarOpts
  Support
  TransformUtils
  Vectorize
  )

# Support plugins.
set(LLVM_NO_DEAD_STRIP 1)

add_polly_executable(pollycc
  driver.cpp
  cc1_main.cpp
  cc1as_main.cpp
  )

target_link_libraries(pollycc
  clangBasic
  clangDriver
  clangFrontend
  clangFrontendTool
  )

target_link_libraries(pollycc 
  LLVMPollyLib
)
