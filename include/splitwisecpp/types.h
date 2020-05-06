// Copyright (c) 2020 Gino Latorilla.

#ifndef SPLITWISECPP_TYPES_H_
#define SPLITWISECPP_TYPES_H_

#include <string>
#include <json/value.h>

namespace splitwisecpp
{

using UnspecifiedPtr = void*;
using Json = ::Json::Value;
using IdType = std::uint32_t;

enum class ErrorCodes
{
    NoError,
    OAuth1_Sign_Url_Error,
    OutOfMemory,
    NetworkError
};

struct Configuration
{
    std::string consumer_key;
    std::string consumer_secret;
    std::string oauth1_token;
    std::string oauth1_token_secret;
};

struct ApiResponse
{
    Json json;
    ErrorCodes error;
};

}  // namespace splitwisecpp

#endif  // SPLITWISECPP_H_
