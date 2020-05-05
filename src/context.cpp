#include "context.hpp"

namespace splitwisecpp
{

const std::string BASEURL = "https://www.splitwise.com/api/v3.0/";

Context::Context(const Configuration* config_) : config(config_)
{
}

Context::~Context() = default;

}  // namespace spliwisecpp
