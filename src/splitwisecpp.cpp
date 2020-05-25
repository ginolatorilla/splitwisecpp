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

ApiResponse Splitwise::get_current_user()
{
    return Context::cast(_context)->api_request_as_json<ApiMethods::get_current_user>();
}

ApiResponse Splitwise::get_user(IdType id)
{
    return Context::cast(_context)->api_request_as_json<ApiMethods::get_user>(id);
}

ApiResponse Splitwise::get_groups()
{
    return Context::cast(_context)->api_request_as_json<ApiMethods::get_groups>();
}

ApiResponse Splitwise::create_group(const Json& group)
{
    return Context::cast(_context)->api_request_as_json<ApiMethods::create_group>(group);
}

ApiResponse Splitwise::delete_group(IdType id)
{
    return Context::cast(_context)->api_request_as_json<ApiMethods::delete_group>(id);
}

}  // namespace splitwisecpp

// DO NOT EDIT BY HAND!
// 'tools/generate_cpp_api_from_descriptor' created me on 2020-05-25T22:24:38.317598 from descriptor version 0.9
