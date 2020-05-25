// Copyright (c) 2020 Gino Latorilla.

#ifndef SPLITWISECPP_CONTEXT_H_
#define SPLITWISECPP_CONTEXT_H_

#include "curlwrapper.hpp"
#include "liboauthcpp/liboauthcpp.h"
#include "splitwisecpp/types.h"
#include <memory>

namespace splitwisecpp
{

class Context
{
public:
    Context(const Configuration* config_);
    ~Context();

    static inline Context* cast(UnspecifiedPtr opaque)
    {
        return reinterpret_cast<Context*>(opaque);
    }

    std::unique_ptr<OAuth::Client> oauth_client;
    Curl curl;

private:
    OAuth::Consumer oauth_consumer;
    OAuth::Token oauth_token;
};

}  // namespace splitwisecpp

#endif  // SPLITWISECPP_CONTEXT_H_
