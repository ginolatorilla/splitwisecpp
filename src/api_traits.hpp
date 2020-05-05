#include <cstdint>

namespace splitwisecpp
{

enum class ApiMethods : std::uint32_t
{
    get_current_user,
    get_user,
    get_groups,
    _count // Trick for counting number of enumerators
};

template<ApiMethods M>
struct api_traits
{};

#define API_TRAITS_ENTRY(NAME) \
    template<> struct api_traits<ApiMethods::NAME> \
    { \
        static constexpr const char* const c_str = #NAME; \
    }

API_TRAITS_ENTRY(get_current_user);
API_TRAITS_ENTRY(get_user);
API_TRAITS_ENTRY(get_groups);

#undef API_TRAITS_ENTRY

}  // splitwisecpp
