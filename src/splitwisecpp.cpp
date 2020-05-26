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

ApiResponse Splitwise::update_user(IdType id, const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("update_user")
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

ApiResponse Splitwise::undelete_group(IdType id)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_uri("undelete_group")
                .with_param(id)
                .send();
}

ApiResponse Splitwise::add_user_to_group(const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("add_user_to_group")
                .send();
}

ApiResponse Splitwise::remove_user_from_group(const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("remove_user_from_group")
                .send();
}

ApiResponse Splitwise::get_friends()
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_friends")
                .send();
}

ApiResponse Splitwise::get_friend(IdType id)
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_friend")
                .with_param(id)
                .send();
}

ApiResponse Splitwise::create_friend(const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("create_friend")
                .send();
}

ApiResponse Splitwise::create_friends(const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("create_friends")
                .send();
}

ApiResponse Splitwise::delete_friend(IdType id)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_uri("delete_friend")
                .with_param(id)
                .send();
}

ApiResponse Splitwise::get_expenses()
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_expenses")
                .send();
}

ApiResponse Splitwise::get_expense(IdType id)
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_expense")
                .with_param(id)
                .send();
}

ApiResponse Splitwise::create_expenses(const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("create_expenses")
                .send();
}

ApiResponse Splitwise::update_expense(IdType id, const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("update_expense")
                .with_param(id)
                .send();
}

ApiResponse Splitwise::delete_expense(IdType id)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_uri("delete_expense")
                .with_param(id)
                .send();
}

ApiResponse Splitwise::undelete_expense(IdType id)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_uri("undelete_expense")
                .with_param(id)
                .send();
}

ApiResponse Splitwise::get_comments(IdType expense_id)
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_comments")
                .with_query_param("expense_id", expense_id)
                .send();
}

ApiResponse Splitwise::create_comment(const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("create_comment")
                .send();
}

ApiResponse Splitwise::delete_comment(IdType id)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_uri("delete_comment")
                .with_param(id)
                .send();
}

ApiResponse Splitwise::get_notifications()
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_notifications")
                .send();
}

ApiResponse Splitwise::get_currencies()
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_currencies")
                .send();
}

ApiResponse Splitwise::get_categories()
{
    return build_http_request<HttpMethods::Get>(Context::cast(_context))
                .with_uri("get_categories")
                .send();
}

ApiResponse Splitwise::parse_sentence(const Json& payload)
{
    return build_http_request<HttpMethods::Post>(Context::cast(_context))
                .with_json_payload(payload)
                .with_uri("parse_sentence")
                .send();
}

}  // namespace splitwisecpp

// DO NOT EDIT BY HAND!
// 'tools/generate_cpp_api_from_descriptor' created me on 2020-05-26T14:06:27.658579 from descriptor version 0.9
