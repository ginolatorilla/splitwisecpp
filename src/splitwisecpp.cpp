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
    const Configuration* config;

    Context(const Configuration* config_) : config(config_)
    {
        assemble_signed_url<ApiMethods::get_current_user>();
    }

    ~Context()
    {
        for (auto*& url : signed_urls)
        {
            ::free(url);
            url = nullptr;
        }
    }

    template<ApiMethods M>
    Json api_request_as_json()
    {
        ::Json::Value parsed;
        ::Json::CharReaderBuilder rb;
        std::unique_ptr<::Json::CharReader> json_c_reader(rb.newCharReader());
        detail::JsonReaderContext context;
        context.json = &parsed;
        context.reader = json_c_reader.get();

        curl.set_write_to_json(&context);
        curl.set_url(signed_urls[static_cast<uint8_t>(api_traits<M>::id)]);
        curl.perform();

        return parsed;
    }

    template<ApiMethods M>
    void assemble_signed_url()
    {
        signed_urls[api_traits<M>::id] = ::oauth_sign_url2(
            (BASEURL + api_traits<M>::c_str).c_str(),
            nullptr, // unused
            ::OA_HMAC,
            nullptr, // HTTP GET
            config->consumer_key.c_str(),
            config->consumer_secret.c_str(),
            config->oauth1_token.c_str(),
            config->oauth1_token_secret.c_str()
        );
    }
};

Splitwise::Splitwise(const Configuration& config)
{
    _context = new Context(&config);
}

Splitwise::~Splitwise()
{
    delete AS_CONTEXT(_context);
}

#define API_REQUEST_AS_JSON(__method__) (AS_CONTEXT(_context)->api_request_as_json<ApiMethods::__method__>())

Json Splitwise::get_current_user()
{
    return API_REQUEST_AS_JSON(get_current_user);
}

#undef API_REQUEST_AS_JSON


}  // namespace splitwisecpp
