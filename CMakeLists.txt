cmake_minimum_required(VERSION 3.3)

set(cpp_version_number 20)

project(figire_finder VERSION 0.0.1)

# Standard requirenments:

set(CMAKE_CXX_STANDARD ${cpp_version_number})
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generates compile_commands.json

# Force cmake to put all libraries and executables in the same directory, so that special compilers can find them:

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Detect Build Type

if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Release")
    set(FIGURE_FINDER_DEBUG OFF)
else()
    set(FIGURE_FINDER_DEBUG ON)
endif()

# Includes:

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/cmake"
)

include(DetectOS)
include(CompilerOptions)

# Default compiler options macro:

macro(target_set_default_flags target)

    if(OS STREQUAL "linux")
        set(common_flags "-std=c++${cpp_version_number}")
        set(debug_flags "")
        set(release_flags "")
    elseif(OS STREQUAL "darwin")
        set(common_flags "-std=c++${cpp_version_number}")
        set(debug_flags "")
        set(release_flags "")
    elseif(OS STREQUAL "windows")
        set(common_flags "/std:c++${cpp_version_number}")
        set(debug_flags "")
        set(release_flags "")
    endif()

    generate_common_flags(
        common_flags "${common_flags}"
        debug_flags "${debug_flags}"
        release_flags "${release_flags}"
    )

    if(FIGURE_FINDER_DEBUG)
        target_compile_options(${target} PRIVATE ${common_flags} ${debug_flags})
    else()
        target_compile_options(${target} PRIVATE ${common_flags} ${release_flags})
    endif()

endmacro()

################### Create executables ###################

# Create executables

set (src_files
    src/core/utils.cpp
    src/core.cpp

    src/figure_finder.cpp
)

if (FIGURE_FINDER_BUILD_STATIC)
    add_library(figure_finder STATIC ${src_files})
else()
    add_library(figure_finder SHARED ${src_files})

    target_compile_definitions(figure_finder PRIVATE
        "FIGURE_FINDER_LIBRARY_SHARED=$<BOOL:${FIGURE_FINDER_LIBRARY_SHARED}>"
        -DFIGURE_FINDER_LIBRARY_BUILD=1
    )
    target_include_directories(figure_finder PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    # Unify symbol visibility across all platforms
    set_target_properties(figure_finder PROPERTIES
        C_VISIBILITY_PRESET hidden
        C_VISIBILITY_INLINE_PRESET hidden
        CXX_VISIBILITY_PRESET hidden
        CXX_VISIBILITY_INLINE_PRESET hidden
    )
endif()

# Set Compile Definitions

target_compile_definitions(figure_finder PUBLIC
    "CORE_ASSERT_ENABLED=$<BOOL:${CORE_ASSERT_ENABLED}>"
    -DFIGURE_FINDER_DEBUG="$<BOOL:${FIGURE_FINDER_DEBUG}>"
)

# Set default flags

target_set_default_flags(figure_finder)

if (FIGURE_FINDER_BUILD_TESTS)
    set (test_files
        test_main.cpp
        tests/t-index.cpp
    )

    add_executable(tests ${test_files})
    target_link_libraries(tests figure_finder)
    target_set_default_flags(tests)

    # Enable testing
    enable_testing()
    add_test(NAME tests COMMAND tests)
endif()

