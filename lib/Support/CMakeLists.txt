file(GLOB polly_support_headers ${POLLY_SOURCE_DIR}/include/polly/CodeGen/*.h)
add_polly_library(PollySupport
  GICHelper.cpp
  SCEVValidator.cpp
  ScopHelper.cpp
  ${polly_support_headers}
  )
