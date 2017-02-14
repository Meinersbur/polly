
# Keep this in sync with llvm/cmake/CMakeLists.txt!
set(LLVM_INSTALL_PACKAGE_DIR "lib${LLVM_LIBDIR_SUFFIX}/cmake/llvm")
set(llvm_cmake_builddir "${LLVM_BINARY_DIR}/${LLVM_INSTALL_PACKAGE_DIR}")

set(POLLY_INSTALL_PACKAGE_DIR "lib${LLVM_LIBDIR_SUFFIX}/cmake/polly")
set(polly_cmake_builddir "${POLLY_BINARY_DIR}/${POLLY_INSTALL_PACKAGE_DIR}")


get_property(POLLY_EXPORTS GLOBAL PROPERTY POLLY_EXPORTS)
export(TARGETS ${POLLY_EXPORTS} FILE ${polly_cmake_builddir}/PollyTargets.cmake)


# Generate PollyConfig.cmake for the build tree.
set(POLLY_CONFIG_LLVM_CMAKE_DIR "${llvm_cmake_builddir}")
set(POLLY_CONFIG_CMAKE_DIR "${polly_cmake_builddir}")

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/PollyConfig.cmake.in
  ${polly_cmake_builddir}/PollyConfig.cmake
  @ONLY)


# Generate PollyConfig.cmake for the install tree.
set(POLLY_CONFIG_LLVM_CMAKE_DIR "\${POLLY_INSTALL_PREFIX}/${LLVM_INSTALL_PACKAGE_DIR}")
set(POLLY_CONFIG_CMAKE_DIR "\${POLLY_INSTALL_PREFIX}/${LLVM_INSTALL_PACKAGE_DIR}")

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/PollyConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/PollyConfig.cmake
  @ONLY)

if (NOT LLVM_INSTALL_TOOLCHAIN_ONLY)
  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/PollyConfig.cmake"
    DESTINATION "${POLLY_INSTALL_PACKAGE_DIR}")
endif ()



