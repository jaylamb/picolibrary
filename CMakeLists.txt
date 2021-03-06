# picolibrary
#
# Copyright 2020-2021, Andrew Countryman <apcountryman@gmail.com> and the picolibrary
# contributors
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not use this
# file except in compliance with the License. You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software distributed under
# the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the License for the specific language governing
# permissions and limitations under the License.

# File: CMakeLists.txt
# Description: picolibrary core CMake rules.

cmake_minimum_required( VERSION 3.12.4 )
project(
    picolibrary
    LANGUAGES CXX
)

# project configuration
option( PICOLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION "picolibrary: suppress human readable error information" OFF )
option( PICOLIBRARY_ENABLE_INTERACTIVE_TESTING                "picolibrary: enable interactive testing"                OFF )
option( PICOLIBRARY_ENABLE_UNIT_TESTING                       "picolibrary: enable unit testing"                       OFF )
option( PICOLIBRARY_USE_PARENT_PROJECT_BUILD_FLAGS            "picolibrary: use parent project's build flags"          ON  )
option( PICOLIBRARY_USE_PARENT_PROJECT_GOOGLE_TEST            "picolibrary: use parent project's Google Test"          ON  )

if( ${PICOLIBRARY_ENABLE_UNIT_TESTING} AND ${PICOLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION} )
    message( FATAL_ERROR "picolibrary unit tests require human readable error information" )
endif( ${PICOLIBRARY_ENABLE_UNIT_TESTING} AND ${PICOLIBRARY_SUPPRESS_HUMAN_READABLE_ERROR_INFORMATION} )

# load additional CMake modules
list(
    APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/apcountryman-cmake-utilities"
)

# configure compilation and linking
if( NOT ${PICOLIBRARY_USE_PARENT_PROJECT_BUILD_FLAGS} )
    set( CMAKE_CXX_STANDARD 17 )

    set(
        CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} \
        -Werror -Wall -Wextra \
        -Wcast-qual \
        -Wfloat-equal \
        -Wmissing-field-initializers \
        -Wmissing-include-dirs \
        -Wold-style-cast \
        -Wpointer-arith \
        -Wshadow \
        "
    )

    option( PICOLIBRARY_USE_STATIC_ANALYSIS_BUILD_FLAGS "picolibrary: use static analysis build flags" OFF )
    if( NOT ${PICOLIBRARY_USE_STATIC_ANALYSIS_BUILD_FLAGS} )
        set(
            CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} \
            -Wcast-align=strict \
            -Wduplicated-cond \
            -Wextra-semi \
            -Wimplicit-fallthrough=5 \
            -Wlogical-op \
            -Wplacement-new=2 \
            -Wunsafe-loop-optimizations \
            "
        )
    endif( NOT ${PICOLIBRARY_USE_STATIC_ANALYSIS_BUILD_FLAGS} )

    if( ${PICOLIBRARY_ENABLE_UNIT_TESTING} )
        set(
            CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} \
            -fsanitize=address \
            -fno-sanitize-recover=all \
            "
        )
    endif( ${PICOLIBRARY_ENABLE_UNIT_TESTING} )
endif( NOT ${PICOLIBRARY_USE_PARENT_PROJECT_BUILD_FLAGS} )

# capture project version information
include( git-utilities )
execute_git_command(
    PICOLIBRARY_VERSION
    COMMAND describe --match=none --always --dirty --broken
)

# configure Google Test
if( ${PICOLIBRARY_ENABLE_UNIT_TESTING} AND NOT ${PICOLIBRARY_USE_PARENT_PROJECT_GOOGLE_TEST} )
    set( BUILD_GMOCK   ON  CACHE BOOL "" FORCE )
    set( INSTALL_GTEST OFF CACHE BOOL "" FORCE )
    mark_as_advanced(
        BUILD_GMOCK
        INSTALL_GTEST
    )

    set( gtest_build_samples         OFF CACHE BOOL "" FORCE )
    set( gtest_build_tests           OFF CACHE BOOL "" FORCE )
    set( gtest_disable_pthreads      OFF CACHE BOOL "" FORCE )
    set( gtest_force_shared_crt      OFF CACHE BOOL "" FORCE )
    set( gtest_hide_internal_symbols OFF CACHE BOOL "" FORCE )
    mark_as_advanced(
        gtest_build_samples
        gtest_build_tests
        gtest_disable_pthreads
        gtest_force_shared_crt
        gtest_hide_internal_symbols
    )

    set( gmock_build_tests OFF CACHE BOOL "" FORCE )
    mark_as_advanced( gmock_build_tests )

    add_subdirectory( googletest )
endif( ${PICOLIBRARY_ENABLE_UNIT_TESTING} AND NOT ${PICOLIBRARY_USE_PARENT_PROJECT_GOOGLE_TEST} )

# enable unit testing
if( ${PICOLIBRARY_ENABLE_UNIT_TESTING} )
    enable_testing()
endif( ${PICOLIBRARY_ENABLE_UNIT_TESTING} )

# build the library
add_subdirectory( source )

# build the library's tests
add_subdirectory( test )
