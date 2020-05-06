// Copyright (c) 2020 Gino Latorilla.

#ifndef SPLITWISECPP_CONTEXT_H_
#define SPLITWISECPP_CONTEXT_H_

#include <memory>
#include <type_traits>
#include "splitwisecpp/types.h"
#include "curlwrapper.hpp"
#include "liboauthcpp/liboauthcpp.h"
#include "api_traits.hpp"
#include "metaprogramming.hpp"

namespace splitwisecpp
{

extern const std::string BASEURL;

class Context
{
public:
    Context(const Configuration* config_);
    ~Context();

    static inline Context* cast(UnspecifiedPtr opaque)
    {
        return reinterpret_cast<Context*>(opaque);
    }

    template<ApiMethods M>
    ApiResponse api_request_as_json()
    {
        auto signed_urls = create_signed_api_url<M>();
        return api_request_as_json(signed_urls, api_traits<M>::http_method);
    }
    
    template<ApiMethods M>
    ApiResponse api_request_as_json(const Json& data)
    {
        auto signed_urls = create_signed_api_url<M>();
        return api_request_as_json(signed_urls, api_traits<M>::http_method, &data);
    }

    template<ApiMethods M, class P1>
    ApiResponse api_request_as_json(P1 param1)
    {
        auto signed_urls = create_signed_api_url<M>(param1);
        return api_request_as_json(signed_urls, api_traits<M>::http_method);
    }

private:
    using OAuthUrlType = std::unique_ptr<char, decltype(&::free)>;
    using OAuthPostargsType = std::unique_ptr<char, decltype(&::free)>;

    std::string create_signed_api_url(const char* method, const std::string& fused_args);
    ApiResponse api_request_as_json(const std::string& signed_url, HttpMethods http_method, const Json* post_data = nullptr);

    template<ApiMethods Method, class... Param>
    std::string create_signed_api_url(Param... args)
    {
        // TODO: Add C++14-equivalent (C++17 only)
        static_assert(
            std::conjunction<
                std::disjunction<std::is_arithmetic<Param>, std::is_convertible<Param, std::string>>...
            >::value, "All arguments must be valid for std::to_string."
        );

        return create_signed_api_url(api_traits<Method>::c_str, join_as_path_str(args...));
    }

    const Configuration* config;
    Curl curl;
    OAuth::Consumer oauth_consumer;
    OAuth::Token oauth_token;
    std::unique_ptr<OAuth::Client> oauth_client;
};

}  // namespace spliwisecpp

#endif  // SPLITWISECPP_CONTEXT_H_
