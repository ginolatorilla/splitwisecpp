#include <iosfwd>

namespace splitwisecpp
{

namespace detail
{

inline void stream_insert_v(std::ostream&)
{
    // Tail call, do nothing.
}

template<class Param>
inline void stream_insert_v(std::ostream& stream, Param arg)
{
    stream << '/' << arg;
}

template<class Param, class... Params>
inline void stream_insert_v(std::ostream& stream, Param arg, Params... args)
{
    stream << '/' << arg;
    stream_insert_v(stream, args...);
}

}  // namespace detail

template<class... Params> 
inline std::string join_as_path_str(Params... args)
{
    std::stringstream stream;
    detail::stream_insert_v(stream, args...);
    return stream.str();
}

}  // namespace splitwisecpp
