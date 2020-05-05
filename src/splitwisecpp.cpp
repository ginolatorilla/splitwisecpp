// Copyright (c) 2020 Gino Latorilla.

#include "splitwisecpp/splitwisecpp.h"
#include "curlwrapper.hpp"
#include "api_traits.hpp"
#include <oauth.h>
#include <array>
#include <algorithm>
#include <json/json.h>
#include <memory>

#define AS_CONTEXT(__context__) (reinterpret_cast<splitwisecpp::Context*>(__context__))

namespace splitwisecpp
{

static const std::string BASEURL = "https://www.splitwise.com/api/v3.0/";

struct Context
{
    Curl curl;
    std::array<char*, 1> signed_urls;
};

Splitwise::Splitwise(const Configuration& config)
{
    _context = new Context();
    AS_CONTEXT(_context)->signed_urls[static_cast<uint8_t>(api_traits<ApiMethods::get_current_user>::id)] = 
        ::oauth_sign_url2((BASEURL + api_traits<ApiMethods::get_current_user>::c_str).c_str(),
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
    ::Json::Value parsed;
    ::Json::CharReaderBuilder rb;
    std::unique_ptr<::Json::CharReader> json_c_reader(rb.newCharReader());
    detail::JsonReaderContext context;
    context.json = &parsed;
    context.reader = json_c_reader.get();

    AS_CONTEXT(_context)->curl.set_write_to_json(&context);
    AS_CONTEXT(_context)->curl.set_url(
        AS_CONTEXT(_context)->signed_urls[static_cast<uint8_t>(api_traits<ApiMethods::get_current_user>::id)]
    );
    AS_CONTEXT(_context)->curl.perform();

    return parsed;
}


}  // namespace splitwisecpp
