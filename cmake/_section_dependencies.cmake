# Copyright (c) 2020 Gino Latorilla.
#
# Declare any (production) dependencies of your project here.

# Call `pkg-config --list-all` to know what's available in your system
find_package(PkgConfig)

# You can use this with CMake targets as `PkgConfig::python3`.
pkg_check_modules(curl IMPORTED_TARGET libcurl)
pkg_check_modules(jsoncpp IMPORTED_TARGET jsoncpp)

set(LIBOAUTHCPP_BUILD_TESTS FALSE CACHE BOOL "Do not build tests; embedded project")
set(LIBOAUTHCPP_BUILD_DEMOS FALSE CACHE BOOL "Do not build tests; embedded project")
set(LIBOAUTHCPP_TOP_LEVEL FALSE)
add_subdirectory(lib/liboauthcpp/build EXCLUDE_FROM_ALL)
target_compile_options(oauthcpp PRIVATE -fpermissive -fexceptions -Wno-error=pedantic -Wno-error=unused-variable)