#include <cstddef>
#include <oauth.h>
#include "context.hpp"

namespace splitwisecpp
{

const std::string BASEURL = "https://www.splitwise.com/api/v3.0/";

Context::Context(const Configuration* config_) : config(config_)
{
}

Context::~Context() = default;

Context::OAuthUrlType Context::create_signed_api_url(const char* method, const std::string& fused_args)
{
    return OAuthUrlType(::oauth_sign_url2(
            (BASEURL + method + fused_args).c_str(),
            nullptr, // unused
            ::OA_HMAC,
            nullptr, // HTTP GET
            config->consumer_key.c_str(),
            config->consumer_secret.c_str(),
            config->oauth1_token.c_str(),
            config->oauth1_token_secret.c_str()
        ), &::free
    );
}

ApiResponse Context::api_request_as_json(char* signed_url)
{
    ::Json::Value parsed;
    ::Json::CharReaderBuilder rb;
    std::unique_ptr<::Json::CharReader> json_c_reader(rb.newCharReader());
    detail::JsonReaderContext context;
    context.json = &parsed;
    context.reader = json_c_reader.get();

    curl.set_write_to_json(&context);
    if (curl.set_url(signed_url) == CURLE_OUT_OF_MEMORY)
    {
        return {parsed, ErrorCodes::OutOfMemory};
    }
    
    if (curl.perform() != CURLE_OK) // Could be CURLE_COULDNT_RESOLVE_HOST
    {
        return {parsed, ErrorCodes::NetworkError};
    }
    
    return {parsed, ErrorCodes::NoError};
}

}  // namespace spliwisecpp
