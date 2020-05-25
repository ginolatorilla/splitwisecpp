# Splitwise C++ API

:warning: **Work in Progress** :warning:

A native C++ API for [the Splitwise App](https://www.splitwise.com/). Written in C++14.

Tested in Linux.

## Quick Start

```cpp
#include <iostream>
#include <cassert>
#include <splitwisecpp/splitwisecpp.h>

int main()
{
    splitwisecpp::Config config;
    config.consumer_key = "your_consumer_key";
    config.consumer_secret = "your_consumer_secret";
    config.oauth1_token = "your_oauth1_token";
    config.oauth1_token_secret = "your_oauth1_token_secret";
    splitwisecpp::Splitwise splitwise(config);

    splitwisecpp::ApiResponse the_user = splitwise.get_current_user();
    assert(spliwisecpp::ErrorCodes::NoError = the_user.error);
    std::cout << the_user.json["user"]["first_name"] << std::endl;
}
```

## Requirements

- [libcurl](https://curl.haxx.se/libcurl/)
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- Includes [liboauthcpp](https://github.com/sirikata/liboauthcpp)

Additional components if you want to develop this:

- C++ compiler that supports C++14 (preferably `gcc` or `clang`)
- CMake
- [gcovr](https://gcovr.com/en/stable/), for code coverage
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html), for code formatting
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy/), for static analysis
- Python 3.6
- Python Jinja2

GTest will be automatically downloaded from GitHub if you don't have it pre-installed.

## Features

- Authentication using OAuth1 tokens.
  Please read the Splitwise [docs](http://dev.splitwise.com/#authentication) to learn more.
- Implemented the following API calls:
  - [`get_current_user`](http://dev.splitwise.com/#get_current_user)
  - [`get_user/:id`](http://dev.splitwise.com/#get_user-id)
  - [`get_groups`](http://dev.splitwise.com/#get_groups)
  - [`create_group`](http://dev.splitwise.com/#create_group)
  - [`delete_group/:id`](http://dev.splitwise.com/#delete_group-id)
- Exports public types from `jsoncpp`

## Limitations

- Thread-unsafe. The `splitwisecpp::Splitwise` class must be instantiated in one thread.

## Backlog

- [ ] Allow C linkage
- [ ] Allow replacement of libcurl via plugins
- [ ] Support OAuth2
- [ ] Support for Windows (ie Win32)
- [ ] Extra tools for:
  - [ ] OAuth1 generation
  - [ ] Command line interface
- [ ] API documentation

## For Developers

Add new API methods in `src/api_method_descriptors.yaml` (the schema is in the comments).
Then run `tools/generate_cpp_api_from_descriptor` to generate interfaces and implementation code.

You may use `pipenv` to install a virtual environment.
