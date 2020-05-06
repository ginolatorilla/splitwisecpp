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
};

enum class HttpMethods
{
    Get,
    Post
};

template<ApiMethods M>
struct api_traits
{};

#define API_TRAITS_ENTRY(NAME, HTTPMETHOD) \
    template<> struct api_traits<ApiMethods::NAME> \
    { \
        static constexpr const char* const c_str = #NAME; \
        static constexpr HttpMethods http_method = HTTPMETHOD; \
    }

API_TRAITS_ENTRY(get_current_user, HttpMethods::Get);
API_TRAITS_ENTRY(get_user, HttpMethods::Get);
API_TRAITS_ENTRY(get_groups, HttpMethods::Get);
API_TRAITS_ENTRY(create_group, HttpMethods::Post);

#undef API_TRAITS_ENTRY

}  // splitwisecpp

#endif  // SPLITWISECPP_API_TRAITS_H_