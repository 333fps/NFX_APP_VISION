#
#   NFX_APP_VISION
#
#   Main CMake file
#
#   nfx Marine © 2024 <ronan.fesselier@nfxMarine.com>
#

cmake_minimum_required(VERSION 3.21)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()

project(NFX_APP_VISION VERSION 1.0.0.0 LANGUAGES CXX)

if(PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(FATAL_ERROR
        "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

message("Configuring: " ${PROJECT_NAME})
message(STATUS "CMake version: " ${CMAKE_VERSION})
message(STATUS "Using cmake toolchain file: " ${CMAKE_TOOLCHAIN_FILE})

# Set output directories - all binaries in the same folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib/")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "-d")
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

add_subdirectory(3rdParty)

include(cmake/Definitions.cmake)
include(cmake/Options.cmake)
include(cmake/Sources.cmake)
include(cmake/Dependencies.cmake)


set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying DLLs from nfx framework directory: ${NFX_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${NFX_BINARY_DIR}"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    COMMENT "Copying NFX framework DLLs"
    VERBATIM
)
