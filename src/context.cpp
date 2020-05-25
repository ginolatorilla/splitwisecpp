#include "context.hpp"
#include <cassert>
#include <cstddef>
#include <json/writer.h>

namespace splitwisecpp
{

Context::Context(const Configuration* config_)
    : oauth_consumer(config_->consumer_key, config_->consumer_secret),
      oauth_token(config_->oauth1_token, config_->oauth1_token_secret)
{
    oauth_client.reset(new decltype(oauth_client)::element_type(&oauth_consumer,
                                                                &oauth_token));
}

Context::~Context() = default;

}  // namespace splitwisecpp
