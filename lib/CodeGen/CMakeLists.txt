if (CLOOG_FOUND)
  set(CLOOG_FILES
      Cloog.cpp
      CodeGeneration.cpp)
endif (CLOOG_FOUND)

set(ISL_CODEGEN_FILES
    IslAst.cpp
    IslCodeGeneration.cpp)

if (GPU_CODEGEN)
  set (GPGPU_CODEGEN_FILES
       PTXGenerator.cpp)
endif (GPU_CODEGEN)

file(GLOB polly_codegen_headers ${POLLY_SOURCE_DIR}/include/polly/CodeGen/*.h)
add_polly_library(PollyCodeGen
  BlockGenerators.cpp
  ${CLOOG_FILES}
  ${ISL_CODEGEN_FILES}
  LoopGenerators.cpp
  Utils.cpp
  ${GPGPU_CODEGEN_FILES}
  ${polly_codegen_headers}
)
