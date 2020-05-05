#include "context.hpp"

namespace splitwisecpp
{

const std::string BASEURL = "https://www.splitwise.com/api/v3.0/";

Context::Context(const Configuration* config_) : config(config_)
{
    assemble_signed_url<ApiMethods::get_current_user>();
}

Context::~Context()
{
    for (auto*& url : signed_urls)
    {
        ::free(url);
        url = nullptr;
    }
}

}  // namespace spliwisecpp
