# Copyright (c) 2020 Gino Latorilla.
#
# Declare all build targets here.

include(IncludeMeOnce)
IncludeMeOnce()

set(${PROJECT_NAME}_SOURCES src/splitwisecpp.cpp src/curlwrapper.cpp src/context.cpp)

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
