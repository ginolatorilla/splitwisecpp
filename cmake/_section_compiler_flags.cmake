# Copyright (c) 2020 Gino Latorilla.
#
# Declare global compilation flags here.
# I encourage you to use `target_compile_definitions` (for -D<FLAGS>)
# and `target_compiler_options` for target-specific settings.

include(IncludeMeOnce)
IncludeMeOnce()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

macro(add_cxx_flag _flag)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_flag}")
endmacro()

# General compiler feature flags
add_cxx_flag(-fPIC)
add_cxx_flag(-fdiagnostics-color=always)
add_cxx_flag(-pipe)
add_cxx_flag(-fno-rtti)
add_cxx_flag(-fno-exceptions)

if(${PROJECT_NAME}_ENABLE_CODE_COVERAGE)
    add_cxx_flag(--coverage)
endif()

if(${PROJECT_NAME}_ENABLE_TESTING AND ${PROJECT_NAME}_ENABLE_SANITIZERS)
    add_cxx_flag(-fsanitize=address,undefined)
endif()

# I prefer strict compliance to standards.
add_cxx_flag(-Wall)
add_cxx_flag(-Werror)
add_cxx_flag(-Wextra)
add_cxx_flag(-pedantic)

macro(add_cxx_flag_for_build _build_type _flag)
    set(CMAKE_CXX_FLAGS_${_build_type} "${CMAKE_CXX_FLAGS_${_build_type}} ${_flag}")
endmacro()

add_cxx_flag_for_build(DEBUG ${CMAKE_CXX_FLAGS})
add_cxx_flag_for_build(DEBUG -Og)
add_cxx_flag_for_build(DEBUG -ggdb3)
add_cxx_flag_for_build(MINSIZEREL ${CMAKE_CXX_FLAGS})
add_cxx_flag_for_build(MINSIZEREL -Os)
add_cxx_flag_for_build(RELEASE ${CMAKE_CXX_FLAGS})
add_cxx_flag_for_build(RELEASE -O3)
add_cxx_flag_for_build(RELWITHDEBINFO ${CMAKE_CXX_FLAGS})
add_cxx_flag_for_build(RELWITHDEBINFO -Og)

macro(add_exe_linker_flag _flag)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${_flag}")
endmacro()

add_exe_linker_flag(-fuse-ld=gold)
add_exe_linker_flag(-Wl,--disable-new-dtags)
add_exe_linker_flag(-Wl,--no-as-needed)

# Instrumentation
if (${PROJECT_NAME}_ENABLE_CLANG_TIDY)
    cmake_minimum_required(VERSION 3.7.2)
    macro(push_clang_tidy_check _flag)
        set(_clang_tidy_checks "${_clang_tidy_checks},${_flag}")
    endmacro()

    push_clang_tidy_check(-*)
    push_clang_tidy_check(modernize-*)
    push_clang_tidy_check(performance-*)
    push_clang_tidy_check(portability-*)
    push_clang_tidy_check(readability-*)
    push_clang_tidy_check(clang-analyzer-*)
    push_clang_tidy_check(cppcoreguidelines-*)
    push_clang_tidy_check(hicpp-*)

    set(CMAKE_CXX_CLANG_TIDY clang-tidy;-checks=${_clang_tidy_checks};-header-filter='.';)
endif()