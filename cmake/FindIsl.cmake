
if (ISL_FIND_REQUIRED)
  find_package(Gmp REQUIRED)
else ()
  find_package(Gmp QUIET)
endif ()

if (GMP_FOUND)
  set(ISL_DEFINITIONS ${GMP_DEFINITIONS})

  find_path(ISL_INCLUDE_DIR "isl/ast.h")
  mark_as_advanced(ISL_INCLUDE_DIR)
  set(ISL_INCLUDE_DIRS ${GMP_INCLUDE_DIRS} ${ISL_INCLUDE_DIR})

  find_library(ISL_LIBRARY NAMES isl)
  mark_as_advanced(ISL_LIBRARY)
  set(ISL_LIBRARIES ${ISL_LIBRARIES} ${GMP_LIBRARIES})
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Isl DEFAULT_MSG ISL_LIBRARY ISL_INCLUDE_DIR)
