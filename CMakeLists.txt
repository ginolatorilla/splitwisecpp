# Copyright (c) 2020 Gino Latorilla.

cmake_minimum_required(VERSION 3.0)
project(splitwisecpp
    VERSION 0.9.0
    DESCRIPTION "A C++ API for splitwise.com"
)

# Makes include() statements cleaner
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(_section_options)
include(_section_compiler_flags)
include(_section_dependencies)
include(_section_targets)
if(${PROJECT_NAME}_ENABLE_TESTING)
    include(_section_testing)
endif()
