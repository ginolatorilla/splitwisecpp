#include "context.hpp"

namespace splitwisecpp
{

const std::string BASEURL = "https://www.splitwise.com/api/v3.0/";

Context::Context(const Configuration* config_) : config(config_)
{
}

Context::~Context() = default;

Splitwise::ApiResponse Context::api_request_as_json(char* signed_url)
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
