add_subdirectory(Analysis)
add_subdirectory(CodeGen)
add_subdirectory(Exchange)
add_subdirectory(Support)
add_subdirectory(JSON)

#set(MODULE TRUE)
set(LLVM_NO_RTTI 1)

if (SCOPLIB_FOUND)
  set(POLLY_SCOPLIB_FILES Pocc.cpp)
endif (SCOPLIB_FOUND)

if (PLUTO_FOUND)
  set(POLLY_PLUTO_FILES Pluto.cpp)
endif (PLUTO_FOUND)

set(LLVM_USED_LIBS
  LLVMPollyAnalysis
  LLVMPollyCodeGen
#  LLVMPollyExchange
  LLVMPollySupport
  LLVMPollyJSON
  )

if (PLUTO_FOUND)
  list(APPEND LLVM_NEXT_EXTERNAL_LIBS ${PLUTO_LIBRARY})
endif(PLUTO_FOUND)

file(GLOB polly_headers ${POLLY_SOURCE_DIR}/include/polly/*.h)
set_source_files_properties(${polly_headers} PROPERTIES HEADER_FILE_ONLY ON)
add_polly_library(LLVMPolly
  Canonicalization.cpp
  CodePreparation.cpp
  DeadCodeElimination.cpp
  IndependentBlocks.cpp
  IndVarSimplify.cpp
  Pocc.cpp
  RegisterPasses.cpp
  ScheduleOptimizer.cpp
  PollyContextPass.cpp
  ${POLLY_SCOPLIB_FILES}
  ${POLLY_PLUTO_FILES}
  ${polly_headers}
  )

if (TARGET intrinsics_gen)
  # Check if we are building as part of an LLVM build
  add_dependencies(LLVMPolly intrinsics_gen)
endif()

add_dependencies(LLVMPolly
  LLVMPollyAnalysis
  LLVMPollyCodeGen
  LLVMPollyExchange
  LLVMPollySupport
  LLVMPollyJSON
  )

set_target_properties(LLVMPolly
  PROPERTIES
  LINKER_LANGUAGE CXX
  PREFIX "")
