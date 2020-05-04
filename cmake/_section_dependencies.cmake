# Copyright (c) 2020 Gino Latorilla.
#
# Declare any (production) dependencies of your project here.

# Call `pkg-config --list-all` to know what's available in your system
find_package(PkgConfig)

# You can use this with CMake targets as `PkgConfig::python3`.
pkg_check_modules(curlpp IMPORTED_TARGET curlpp)
pkg_check_modules(curl IMPORTED_TARGET libcurl)
pkg_check_modules(jsoncpp IMPORTED_TARGET jsoncpp)
