// Copyright (c) 2020 Gino Latorilla.

#ifndef SPLITWISECPP_API_TRAITS_H_
#define SPLITWISECPP_API_TRAITS_H_

#include <cstdint>

namespace splitwisecpp
{

enum class ApiMethods : std::uint32_t
{
    get_current_user,
    get_user,
    get_groups,
    create_group,
    delete_group
};

enum class HttpMethods
{
    Get,
    Post
};

template<ApiMethods M>
struct api_traits
{};

template<> struct api_traits<ApiMethods::get_current_user>
{
    static constexpr const char* const c_str = "get_current_user";
    static constexpr HttpMethods http_method = HttpMethods::Get;
};

template<> struct api_traits<ApiMethods::get_user>
{
    static constexpr const char* const c_str = "get_user";
    static constexpr HttpMethods http_method = HttpMethods::Get;
};

template<> struct api_traits<ApiMethods::get_groups>
{
    static constexpr const char* const c_str = "get_groups";
    static constexpr HttpMethods http_method = HttpMethods::Get;
};

template<> struct api_traits<ApiMethods::create_group>
{
    static constexpr const char* const c_str = "create_group";
    static constexpr HttpMethods http_method = HttpMethods::Post;
};

template<> struct api_traits<ApiMethods::delete_group>
{
    static constexpr const char* const c_str = "delete_group";
    static constexpr HttpMethods http_method = HttpMethods::Post;
};

}  // namespace splitwisecpp

#endif  // SPLITWISECPP_API_TRAITS_H_

// DO NOT EDIT BY HAND!
// 'tools/generate_cpp_api_from_descriptor' created me on 2020-05-26T02:01:24.390832 from descriptor version 0.9
