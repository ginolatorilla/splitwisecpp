// Copyright (c) 2020 Gino Latorilla.

#include "splitwisecpp/splitwisecpp.h"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <oauth.h>
#include <array>
#include <algorithm>
#include <json/json.h>

#define AS_CONTEXT(__context__) (reinterpret_cast<splitwisecpp::Context*>(__context__))

namespace splitwisecpp
{

static const std::string BASEURL = "https://www.splitwise.com/api/v3.0/";

enum class Methods : uint8_t
{
    get_current_user
};

struct Context
{
    curlpp::Cleanup curlpp_cleanup;
    curlpp::Easy curlpp;

    std::array<char*, 1> signed_urls;
};

Splitwise::Splitwise(const Splitwise::Configuration& config)
{
    _context = new Context();
    AS_CONTEXT(_context)->curlpp.setOpt(curlpp::Options::FollowLocation(true));
    AS_CONTEXT(_context)->signed_urls[static_cast<uint8_t>(Methods::get_current_user)] = 
        ::oauth_sign_url2((BASEURL + "get_current_user").c_str(),
                          nullptr, // unused
                          ::OA_HMAC,
                          nullptr, // HTTP GET
                          config.consumer_key.c_str(),
                          config.consumer_secret.c_str(),
                          config.oauth1_token.c_str(),
                          config.oauth1_token_secret.c_str());
}

Splitwise::~Splitwise()
{
    for (auto*& url : AS_CONTEXT(_context)->signed_urls)
    {
        ::free(url);
        url = nullptr;
    }
    delete AS_CONTEXT(_context);
}

Json Splitwise::get_current_user()
{
    std::stringstream response_sink;
    AS_CONTEXT(_context)->curlpp.setOpt(curlpp::Options::WriteStream(&response_sink));
    AS_CONTEXT(_context)->curlpp.setOpt(curlpp::Options::Url(
        AS_CONTEXT(_context)->signed_urls[static_cast<uint8_t>(Methods::get_current_user)]
    ));
    AS_CONTEXT(_context)->curlpp.perform();

    ::Json::CharReaderBuilder rb;
    ::Json::Value parsed;
    std::string _unused;
    ::Json::parseFromStream(rb, response_sink, &parsed, &_unused);
    return parsed;
}


}  // namespace splitwisecpp
