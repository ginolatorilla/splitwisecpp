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

class Context
{
public:
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
    Splitwise::ApiResponse api_request_as_json()
    {
        auto signed_url = create_signed_api_url<M>();
        return api_request_as_json(signed_url.get());
    }

    template<ApiMethods M, class P1>
    Splitwise::ApiResponse api_request_as_json(P1 param1)
    {
        auto signed_url = create_signed_api_url<M>(param1);
        return api_request_as_json(signed_url.get());
    }

private:
    Splitwise::ApiResponse api_request_as_json(char* signed_url);
};

}  // namespace spliwisecpp
