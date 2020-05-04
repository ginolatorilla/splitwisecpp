// Copyright (c) 2020 Gino Latorilla.

#ifndef SPLITWISECPP_H_
#define SPLITWISECPP_H_

#include <string>
#include <json/value.h>

namespace splitwisecpp
{

using UnspecifiedPtr = void*;
using Json = ::Json::Value;

class Splitwise
{
public:
    struct Configuration
    {
        std::string consumer_key;
        std::string consumer_secret;
        std::string oauth1_token;
        std::string oauth1_token_secret;
    };

    explicit Splitwise(const Splitwise::Configuration& config);
    ~Splitwise();

    Json get_current_user();


private:
    UnspecifiedPtr _context;
};

}  // namespace splitwisecpp

#endif  // SPLITWISECPP_H_
