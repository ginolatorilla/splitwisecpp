#include "http_request_builder.hpp"
#include "context.hpp"

namespace splitwisecpp
{

const std::string BASEURL = "https://secure.splitwise.com/api/v3.0/";

HttpGetRequestBuilder::HttpGetRequestBuilder(Context* ctx) : context(ctx)
{
    ::Json::CharReaderBuilder rb;
    json_c_reader.reset(rb.newCharReader());

    reader_context.json = &response;
    reader_context.reader = json_c_reader.get();
    context->curl.set_write_to_json(&reader_context);
}

HttpGetRequestBuilder::~HttpGetRequestBuilder() = default;

HttpGetRequestBuilder& HttpGetRequestBuilder::with_uri(const std::string& uri)
{
    url = BASEURL + uri;
    return *this;
}

ApiResponse HttpGetRequestBuilder::send()
{
    assemble_curl_query();
    if (error_code != ErrorCodes::NoError)
    {
        return {response, error_code};
    }

    if (context->curl.perform() != CURLE_OK)
    {
        error_code = ErrorCodes::NetworkError;
    }
    return {response, error_code};
}

void HttpGetRequestBuilder::assemble_curl_query()
{
    error_code = authenticate();
    if (error_code != ErrorCodes::NoError)
    {
        return;
    }
}

ErrorCodes HttpGetRequestBuilder::authenticate()
{
    auto raw_url = url + (param.empty()? "" : "/" + param);
    raw_url += query_params.empty()? "" : "?" + query_params;
    auto signed_url =
        raw_url + "?" +
        context->oauth_client->getURLQueryString(OAuth::Http::Get, raw_url);
    if (context->curl.set_url(signed_url.c_str()) == CURLE_OUT_OF_MEMORY)
    {
        return ErrorCodes::OutOfMemory;
    }
    else
    {
        context->curl.set_to_GET();
        return ErrorCodes::NoError;
    }
}

HttpPostRequestBuilder::HttpPostRequestBuilder(Context* ctx)
    : HttpGetRequestBuilder(ctx)
{
}

HttpPostRequestBuilder& HttpPostRequestBuilder::with_json_payload(
    const Json& value)
{
    payload = value;
    return *this;
}

ErrorCodes HttpPostRequestBuilder::authenticate()
{
    auto raw_url = url + (param.size() > 0 ? "/" + param : "");
    auto signed_url =
        raw_url + "?" +
        context->oauth_client->getURLQueryString(OAuth::Http::Get, raw_url);
    if (context->curl.set_url(raw_url.c_str()) == CURLE_OUT_OF_MEMORY)
    {
        return ErrorCodes::OutOfMemory;
    }
    context->curl.set_to_POST(
        context->oauth_client
            ->getFormattedHttpHeader(OAuth::Http::Post, signed_url)
            .c_str(),
        payload.empty() ? nullptr : &payload);
    return ErrorCodes::NoError;
}

}  // namespace splitwisecpp
