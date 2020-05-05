// Copyright (c) 2020 Gino Latorilla.

#ifndef SPLITWISECPP_H_
#define SPLITWISECPP_H_

#include <string>
#include <json/value.h>

namespace splitwisecpp
{

using UnspecifiedPtr = void*;
using Json = ::Json::Value;
using UserId = std::uint32_t;

struct Configuration
{
    std::string consumer_key;
    std::string consumer_secret;
    std::string oauth1_token;
    std::string oauth1_token_secret;
};

class Splitwise
{
public:
    explicit Splitwise(const Configuration& config);
    ~Splitwise();

    Json get_current_user();
    Json get_user(UserId id);
    Json get_groups();

private:
    UnspecifiedPtr _context;
};

}  // namespace splitwisecpp

#endif  // SPLITWISECPP_H_
