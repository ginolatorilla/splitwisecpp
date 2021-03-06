// Copyright (c) 2020 Gino Latorilla.

#ifndef SPLITWISECPP_HTTP_REQUEST_BUILDER_H_
#define SPLITWISECPP_HTTP_REQUEST_BUILDER_H_

#include "curlwrapper.hpp"
#include "splitwisecpp/types.h"
#include <memory>
#include <string>

namespace splitwisecpp
{
struct HttpGetRequestBuilder;
struct HttpPostRequestBuilder;
class Context;

enum class HttpMethods
{
    Get,
    Post
};

template <HttpMethods M> struct builder
{
    // DO NOT ALLOW UNSPECIALISED TYPE!
};

template <> struct builder<HttpMethods::Get>
{
    using type = HttpGetRequestBuilder;
};

template <> struct builder<HttpMethods::Post>
{
    using type = HttpPostRequestBuilder;
};

template <HttpMethods M>
typename builder<M>::type build_http_request(Context* context)
{
    return typename builder<M>::type(context);
}

struct HttpGetRequestBuilder  // TODO: add URL encoding on string inputs
{
    explicit HttpGetRequestBuilder(Context* ctx);
    virtual ~HttpGetRequestBuilder();

    HttpGetRequestBuilder& with_uri(const std::string& uri);

    template <typename T>  // TODO: will not work for non-arithmetics
    HttpGetRequestBuilder& with_param(const T& value)
    {
        static_assert(std::is_arithmetic<T>::value,
                      "T must be an arithmetic type.");
        param = std::to_string(value);
        return *this;
    }

    template <typename T>  // TODO: will not work for non-arithmetics
    HttpGetRequestBuilder& with_query_param(const std::string& name,
                                            const T& value)
    {
        static_assert(std::is_arithmetic<T>::value,
                      "T must be an arithmetic type.");
        query_params += (query_params.empty() ? "" : "&") + name + '=' +
                        std::to_string(value);
        return *this;
    }

    ApiResponse send();

    Context* context = nullptr;
    std::string url;
    std::string param;

protected:
    virtual ErrorCodes authenticate();
    ErrorCodes error_code;

private:
    void assemble_curl_query();
    detail::JsonReaderContext reader_context;
    std::shared_ptr<::Json::CharReader> json_c_reader;
    Json response;
    std::string query_params;
};

struct HttpPostRequestBuilder : HttpGetRequestBuilder
{
    explicit HttpPostRequestBuilder(Context* ctx);
    HttpPostRequestBuilder& with_json_payload(const Json& payload);

protected:
    ErrorCodes authenticate() override;

private:
    Json payload;
};

}  // namespace splitwisecpp

#endif  // SPLITWISECPP_HTTP_REQUEST_BUILDER_H_
