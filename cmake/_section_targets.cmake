# Copyright (c) 2020 Gino Latorilla.
#
# Declare all build targets here.

include(IncludeMeOnce)
IncludeMeOnce()

set(${PROJECT_NAME}_SOURCES src/splitwisecpp.cpp src/curlwrapper.cpp src/context.cpp src/http_request_builder.cpp)

if(${PROJECT_NAME}_BUILD_SHARED)
    set(_library_target_type SHARED)
else()
    set(_library_target_type STATIC)
endif()

# This declares a library target (could be shared or static).
# Expose your API directories with the INTERFACE property.
add_library(${PROJECT_NAME} ${_library_target_type} ${${PROJECT_NAME}_SOURCES})
target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
    PRIVATE
        src
        lib/liboauthcpp/include
        ${libcurl_INCLUDE_DIRS}
        ${jsoncpp_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE oauthcpp)

add_custom_target(coverage
    COMMAND gcovr -j -r ${CMAKE_CURRENT_SOURCE_DIR} -f ${CMAKE_CURRENT_SOURCE_DIR}/src -f ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_custom_target(coverage-wipe
    COMMAND find ${CMAKE_CURRENT_BINARY_DIR} -name '*.gcda' -delete
)
add_custom_target(coverage-html
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/coverage
    COMMAND
        gcovr -j -r ${CMAKE_CURRENT_SOURCE_DIR} -f ${CMAKE_CURRENT_SOURCE_DIR}/src -f ${CMAKE_CURRENT_SOURCE_DIR}/include
        --html-details --output ${CMAKE_CURRENT_BINARY_DIR}/coverage/${PROJECT_NAME}-coverage.html
    COMMAND xdg-open ${CMAKE_CURRENT_BINARY_DIR}/coverage/${PROJECT_NAME}-coverage.html
)