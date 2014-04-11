# Check if this is a in tree build.
if (NOT DEFINED LLVM_MAIN_SRC_DIR)
  project(Polly)
  cmake_minimum_required(VERSION 2.8)

  # Where is LLVM installed?
  set(LLVM_INSTALL_ROOT "" CACHE PATH "Root of LLVM install.")
  # Check if the LLVM_INSTALL_ROOT valid.
  if( NOT EXISTS ${LLVM_INSTALL_ROOT}/include/llvm )
    message(FATAL_ERROR "LLVM_INSTALL_ROOT (${LLVM_INSTALL_ROOT}) is not a valid LLVM installation.")
  endif(NOT EXISTS ${LLVM_INSTALL_ROOT}/include/llvm)
  #FileCheck is not install by default, warn the user to Copy FileCheck
  if( NOT EXISTS ${LLVM_INSTALL_ROOT}/bin/FileCheck
      OR NOT EXISTS ${LLVM_INSTALL_ROOT}/bin/not)
    message(WARNING "FileCheck or not are requred by running regress tests, "
                    "but they are not installed! Please copy it to "
                    "${LLVM_INSTALL_ROOT}/bin.")
  endif(NOT EXISTS ${LLVM_INSTALL_ROOT}/bin/FileCheck
        OR NOT EXISTS ${LLVM_INSTALL_ROOT}/bin/not)
  # Add the llvm header path.
  include_directories(${LLVM_INSTALL_ROOT}/include/)

  # Get the system librarys that will link into LLVM.
  function(get_system_libs return_var)
    # Returns in `return_var' a list of system libraries used by LLVM.
    if( NOT MSVC )
      if( MINGW )
        set(system_libs ${system_libs} imagehlp psapi)
      elseif( CMAKE_HOST_UNIX )
        if( HAVE_LIBDL )
          set(system_libs ${system_libs} ${CMAKE_DL_LIBS})
        endif()
        if( LLVM_ENABLE_THREADS AND HAVE_LIBPTHREAD )
          set(system_libs ${system_libs} pthread)
        endif()
      endif( MINGW )
    endif( NOT MSVC )
    set(${return_var} ${system_libs} PARENT_SCOPE)
  endfunction(get_system_libs)

  # Now set the header paths.
  execute_process(COMMAND "${LLVM_INSTALL_ROOT}/bin/llvm-config" --includedir
                  OUTPUT_VARIABLE LLVM_INCLUDE_DIR
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  include_directories( ${LLVM_INCLUDE_DIR} )

  # Get the TARGET_TRIPLE
  execute_process(COMMAND "${LLVM_INSTALL_ROOT}/bin/llvm-config" --host-target
                  OUTPUT_VARIABLE TARGET_TRIPLE
                  OUTPUT_STRIP_TRAILING_WHITESPACE)

  # And then set the cxx flags.
  execute_process(COMMAND "${LLVM_INSTALL_ROOT}/bin/llvm-config" --cxxflags
                  OUTPUT_VARIABLE LLVM_CXX_FLAGS
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS})
endif(NOT DEFINED LLVM_MAIN_SRC_DIR)

set(POLLY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(POLLY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Add path for custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  )

include("polly_macros")

# Add appropriate flags for GCC
if (CMAKE_COMPILER_IS_GNUCXX)
  # FIXME: Turn off exceptions, RTTI:
  # -fno-exceptions -fno-rtti
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-common -Woverloaded-virtual -Wno-long-long -Wall -W -Wno-unused-parameter -Wwrite-strings -fno-exceptions -fno-rtti")
endif ()

if(NOT MSVC_IDE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
endif(NOT MSVC_IDE)

# Add path for custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${POLLY_SOURCE_DIR}/cmake")

SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_llvm_external_project(isl)
if (NOT LLVM_EXTERNAL_ISL_BUILD)
  FIND_PACKAGE(Isl REQUIRED)
  set(POLLY_LINK_LIBS ${ISL_LIBRARY})
endif ()


FIND_PACKAGE(Pluto)
if(PLUTO_FOUND)
  set(POLLY_LINK_LIBS ${POLLY_LINK_LIBS} ${PLUTO_LIBRARY})
endif(PLUTO_FOUND)

option(POLLY_USE_CLOOG "Build Polly with Cloog support" ON)
if(POLLY_USE_CLOOG)
  # Build Cloog support in Polly (default is for cloog-isl).
  FIND_PACKAGE(Cloog)
  FIND_PACKAGE(Gmp REQUIRED)
  if(CLOOG_FOUND)
    set(POLLY_LINK_LIBS ${POLLY_LINK_LIBS} ${CLOOG_LIBRARY})
  endif(CLOOG_FOUND)
endif(POLLY_USE_CLOOG)

if(GMP_FOUND)
  set(POLLY_LINK_LIBS ${POLLY_LINK_LIBS} ${GMP_LIBRARY})
endif(GMP_FOUND)

option(POLLY_ENABLE_GPGPU_CODEGEN "Enable GPGPU code generation feature" OFF)
if (POLLY_ENABLE_GPGPU_CODEGEN)
  # Do not require CUDA, as GPU code generation test cases can be run without
  # a cuda library.
  FIND_PACKAGE(CUDA)
  set(GPU_CODEGEN TRUE)
endif(POLLY_ENABLE_GPGPU_CODEGEN)

option(POLLY_ENABLE_OPENSCOP "Enable Openscop library for scop import/export" ON)
if (POLLY_ENABLE_OPENSCOP)
  FIND_PACKAGE(OpenScop)
  if(OPENSCOP_FOUND)
    set(POLLY_LINK_LIBS ${POLLY_LINK_LIBS} ${OPENSCOP_LIBRARY})
  endif(OPENSCOP_FOUND)
endif(POLLY_ENABLE_OPENSCOP)

option(POLLY_ENABLE_SCOPLIB "Enable SCoPLib library for scop import/export" ON)
if (POLLY_ENABLE_SCOPLIB)
  FIND_PACKAGE(SCoPLib)
  if(SCOPLIB_FOUND)
    set(POLLY_LINK_LIBS ${POLLY_LINK_LIBS} ${SCOPLIB_LIBRARY})
  endif(SCOPLIB_FOUND)
endif(POLLY_ENABLE_SCOPLIB)

if (CLOOG_FOUND)
  INCLUDE_DIRECTORIES( ${CLOOG_INCLUDE_DIR} )
endif(CLOOG_FOUND)
if (PLUTO_FOUND)
  INCLUDE_DIRECTORIES( ${PLUTO_INCLUDE_DIR} )
endif(PLUTO_FOUND)
INCLUDE_DIRECTORIES( ${ISL_INCLUDE_DIRS} )
if (GMP_FOUND)
  INCLUDE_DIRECTORIES( ${GMP_INCLUDE_DIR} )
endif(GMP_FOUND)

# Support GPGPU code generation if the library is available.
if (CUDALIB_FOUND)
  INCLUDE_DIRECTORIES( ${CUDALIB_INCLUDE_DIR} )
endif(CUDALIB_FOUND)

# Support OpenScop export/import if the library is available.
if (OPENSCOP_FOUND)
  INCLUDE_DIRECTORIES( ${OPENSCOP_INCLUDE_DIR} )
endif(OPENSCOP_FOUND)
if (SCOPLIB_FOUND)
  INCLUDE_DIRECTORIES( ${SCOPLIB_INCLUDE_DIR} )
endif(SCOPLIB_FOUND)

macro(add_polly_library name)
  set(srcs)
  if(MSVC_IDE OR XCODE)
    file( GLOB_RECURSE headers *.h *.td *.def)
    set(srcs ${srcs} ${headers})
    string( REGEX MATCHALL "/[^/]+" split_path ${CMAKE_CURRENT_SOURCE_DIR})
    list( GET split_path -1 dir)
    file( GLOB_RECURSE headers 
      ../../include/polly${dir}/*.h)
    set(srcs ${srcs} ${headers})
    set_source_files_properties(${srcs} PROPERTIES HEADER_FILE_ONLY ON)
  endif(MSVC_IDE OR XCODE)
  
  set(_addlibs ${ISL_TARGET} ${ISL_LIBRARY} ${GMP_LIBRARY})
  if (CLOOG_FOUND)
    list(APPEND _addlibs ${CLOOG_LIBRARY})
  endif(CLOOG_FOUND)
  if (OPENSCOP_FOUND)
    list(APPEND _addlibs ${OPENSCOP_LIBRARY})
  endif(OPENSCOP_FOUND)
  if (SCOPLIB_FOUND)
    list(APPEND _addlibs ${SCOPLIB_LIBRARY})
  endif(SCOPLIB_FOUND)

  add_llvm_library(${name} ${srcs} ${ARGN})
  target_link_libraries(${name} ${LLVM_COMMON_LIBS} ${LLVM_USED_LIBS} ${_addlibs})

  set_target_properties(${name} PROPERTIES FOLDER "Polly")
endmacro(add_polly_library)

macro(add_polly_loadable_module name)
  set(srcs ${ARGN})
  add_polly_library(${name} ${srcs})
  if (APPLE)
    # Darwin-specific linker flags for loadable modules.
    set_target_properties(${name} PROPERTIES
      LINK_FLAGS "-Wl,-flat_namespace -Wl,-undefined -Wl,suppress")
  endif()
endmacro(add_polly_loadable_module)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/JSON/include
  ${CMAKE_CURRENT_BINARY_DIR}/include
  )

install(DIRECTORY include/
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
  )

install(DIRECTORY ${POLLY_BINARY_DIR}/include/
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN "CMakeFiles" EXCLUDE
  PATTERN ".svn" EXCLUDE
  )

add_definitions( -D_GNU_SOURCE )

option(POLLY_INCLUDE_TESTS "Generate build targets for the Polly tests." ON)

add_subdirectory(lib)
if( LLVM_INCLUDE_TESTS )
  add_subdirectory(test)
endif( LLVM_INCLUDE_TESTS )
add_subdirectory(tools)
# TODO: docs.


configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/include/polly/Config/config.h.cmake
                ${POLLY_BINARY_DIR}/include/polly/Config/config.h )

# Add target to check formatting of polly files
file( GLOB_RECURSE files *.h *.cpp)
file( GLOB_RECURSE jsonfiles lib/JSON/*.h lib/JSON/*.cpp)
list( REMOVE_ITEM files ${jsonfiles} )
add_custom_command( OUTPUT formatting COMMAND
  CLANG_FORMAT=${LLVM_BINARY_DIR}/bin/clang-format
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/check_format.sh ${files})
add_custom_target(polly-check-format DEPENDS formatting)
set_target_properties(polly-check-format PROPERTIES FOLDER "Polly")
add_custom_command( OUTPUT formatting-update COMMAND
  CLANG_FORMAT=${LLVM_BINARY_DIR}/bin/clang-format
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/update_format.sh ${files})
add_custom_target(polly-update-format DEPENDS formatting-update)
set_target_properties(polly-update-format PROPERTIES FOLDER "Polly")

# Set the variable POLLY_LINK_LIBS in the llvm/tools/ dir.
set(POLLY_LINK_LIBS ${POLLY_LINK_LIBS} PARENT_SCOPE)
