#include <cstddef>
#include <cassert>
#include <json/writer.h>
#include "context.hpp"

namespace splitwisecpp
{

const std::string BASEURL = "https://secure.splitwise.com/api/v3.0/";

Context::Context(const Configuration* config_) :
    config(config_),
    oauth_consumer(config_->consumer_key, config_->consumer_secret),
    oauth_token(config_->oauth1_token, config_->oauth1_token_secret)
{
    oauth_client.reset(
        new decltype(oauth_client)::element_type(&oauth_consumer, &oauth_token)
    );
}

Context::~Context() = default;

std::string Context::create_signed_api_url(const char* method, const std::string& fused_args)
{
    auto raw_url = BASEURL + method + fused_args;
    return raw_url + "?" + oauth_client->getURLQueryString(OAuth::Http::Get, raw_url);
}

ApiResponse Context::api_request_as_json(const std::string& signed_url, HttpMethods http_method, const Json* post_data)
{
    ::Json::Value parsed;
    ::Json::CharReaderBuilder rb;
    std::unique_ptr<::Json::CharReader> json_c_reader(rb.newCharReader());
    detail::JsonReaderContext context;
    context.json = &parsed;
    context.reader = json_c_reader.get();

    curl.set_write_to_json(&context);
    if (curl.set_url(signed_url.c_str()) == CURLE_OUT_OF_MEMORY)
    {
        return {parsed, ErrorCodes::OutOfMemory};
    }

    switch (http_method)
    {
        case HttpMethods::Get:
        {
            curl.set_to_GET();
            break;
        }
        case HttpMethods::Post:
        {
            assert(post_data != nullptr);
            curl.set_to_POST(oauth_client->getFormattedHttpHeader(OAuth::Http::Post, signed_url).c_str(), *post_data);
            break;        
        }
    }
    
    if (curl.perform() != CURLE_OK) // Could be CURLE_COULDNT_RESOLVE_HOST
    {
        return {parsed, ErrorCodes::NetworkError};
    }
    
    return {parsed, ErrorCodes::NoError};
}

}  // namespace spliwisecpp
