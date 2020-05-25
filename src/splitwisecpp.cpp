// Copyright (c) 2020 Gino Latorilla.

#include "splitwisecpp/splitwisecpp.h"
#include "context.hpp"
#include "http_request_builder.hpp"
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
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_current_user")
                .send();
}

ApiResponse Splitwise::get_user(IdType id)
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_user")
                .with_param(id)
                .send();
}

ApiResponse Splitwise::get_groups()
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_groups")
                .send();
}

ApiResponse Splitwise::create_group(const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("create_group")
                .send();
}

ApiResponse Splitwise::delete_group(IdType id)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_uri("delete_group")
                .with_param(id)
                .send();
}

}  // namespace splitwisecpp

// DO NOT EDIT BY HAND!
// 'tools/generate_cpp_api_from_descriptor' created me on 2020-05-26T02:43:52.977574 from descriptor version 0.9
