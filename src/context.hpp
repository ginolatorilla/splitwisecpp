#include <memory>
#include <oauth.h>
#include <type_traits>
#include "splitwisecpp/splitwisecpp.h"
#include "curlwrapper.hpp"
#include "api_traits.hpp"
#include "metaprogramming.hpp"

namespace splitwisecpp
{

extern const std::string BASEURL;

struct Context
{
    Curl curl;
    const Configuration* config;

    Context(const Configuration* config_);
    ~Context();

    static inline Context* cast(UnspecifiedPtr opaque)
    {
        return reinterpret_cast<Context*>(opaque);
    }

    template<class T>
    using unique_cptr = std::unique_ptr<T, decltype(&::free)>;

    template<ApiMethods Method, class... Param>
    unique_cptr<char> create_signed_api_url(Param... args)
    {
        // TODO: Add C++14-equivalent (C++17 only)
        static_assert(
            std::conjunction<
                std::disjunction<std::is_arithmetic<Param>, std::is_convertible<Param, std::string>>...
            >::value, "All arguments must be valid for std::to_string."
        );
    
        return unique_cptr<char>(::oauth_sign_url2(
                (BASEURL + api_traits<Method>::c_str + join_as_path_str(args...)).c_str(),
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
        auto signed_url = create_signed_api_url<M>();
        curl.set_url(signed_url.get());
        curl.perform();

        return parsed;
    }

    template<ApiMethods M, class P1>
    Json api_request_as_json(P1 param1)
    {
        ::Json::Value parsed;
        ::Json::CharReaderBuilder rb;
        std::unique_ptr<::Json::CharReader> json_c_reader(rb.newCharReader());
        detail::JsonReaderContext context;
        context.json = &parsed;
        context.reader = json_c_reader.get();

        curl.set_write_to_json(&context);
        auto signed_url = create_signed_api_url<M>(param1);
        curl.set_url(signed_url.get());
        curl.perform();

        return parsed;
    }
};

}  // namespace spliwisecpp
