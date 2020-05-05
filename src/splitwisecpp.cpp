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
#define API_REQUEST_AS_JSON_1(__method__, _1) (Context::cast(_context)->api_request_as_json<ApiMethods::__method__>(_1))

Json Splitwise::get_current_user()
{
    return API_REQUEST_AS_JSON(get_current_user);
}

Json Splitwise::get_user(UserId id)
{
    return API_REQUEST_AS_JSON_1(get_user, id);
}

#undef API_REQUEST_AS_JSON


}  // namespace splitwisecpp
