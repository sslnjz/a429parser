# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10...3.18)

project ("A429Parser")

# Specify the C++ standard 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Version config
set(A429Parser_VERSION_MAJOR 0)
set(A429Parser_VERSION_MINOR 0)
set(A429Parser_VERSION_BUILD 1)
set(A429Parser_VERSION_PATCH 0)

configure_file(
	"${PROJECT_SOURCE_DIR}/version.h.in" 
	"${PROJECT_SOURCE_DIR}/version.h"
)

# Setup output directories.

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/bin/install")
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/debug)
else ()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/release)
endif()

# Include sub-projects. 
add_subdirectory ("src")






