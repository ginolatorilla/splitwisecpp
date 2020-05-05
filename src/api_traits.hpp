#include <cstdint>

namespace splitwisecpp
{

enum class ApiMethods : std::uint32_t
{
    get_current_user,
    _count // Trick for counting number of enumerators
};

template<ApiMethods M>
struct api_traits
{};

#define API_TRAITS_ENTRY(NAME) \
    template<> struct api_traits<ApiMethods::NAME> \
    { \
        static constexpr std::uint32_t id = static_cast<std::uint32_t>(ApiMethods::NAME); \
        static constexpr const char* const c_str = #NAME; \
    }

API_TRAITS_ENTRY(get_current_user);

}  // splitwisecpp