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

#define API_REQUEST(__method__) \
    (Context::cast(_context)->api_request_as_json<ApiMethods::__method__>())
#define API_REQUEST_1(__method__, _1) \
    (Context::cast(_context)->api_request_as_json<ApiMethods::__method__>(_1))

Splitwise::ApiResponse Splitwise::get_current_user()
{
    return API_REQUEST(get_current_user);
}

Splitwise::ApiResponse Splitwise::get_user(UserId id)
{
    return API_REQUEST_1(get_user, id);
}

Splitwise::ApiResponse Splitwise::get_groups()
{
    return API_REQUEST(get_groups);
}

#undef API_REQUEST
#undef API_REQUEST_1


}  // namespace splitwisecpp
