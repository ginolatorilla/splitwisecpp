#include <memory>
#include <oauth.h>
#include "splitwisecpp/splitwisecpp.h"
#include "curlwrapper.hpp"
#include "api_traits.hpp"

namespace splitwisecpp
{

extern const std::string BASEURL;

struct Context
{
    Curl curl;
    std::array<char*, 1> signed_urls;
    const Configuration* config;

    Context(const Configuration* config_);
    ~Context();

    static inline Context* cast(UnspecifiedPtr opaque)
    {
        return reinterpret_cast<Context*>(opaque);
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

}  // namespace spliwisecpp
