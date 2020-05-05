// Copyright (c) 2020 Gino Latorilla.

#include "splitwisecpp/splitwisecpp.h"
#include "context.hpp"
#include <array>

namespace splitwisecpp
{

Splitwise::Splitwise(const Configuration& config)
{
    _context = new Context(&config);
}

Splitwise::~Splitwise()
{
    delete Context::cast(_context);
}

#define API_REQUEST_AS_JSON(__method__) (Context::cast(_context)->api_request_as_json<ApiMethods::__method__>())

Json Splitwise::get_current_user()
{
    return API_REQUEST_AS_JSON(get_current_user);
}

#undef API_REQUEST_AS_JSON


}  // namespace splitwisecpp
