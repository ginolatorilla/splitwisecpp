#ifndef SPLITWISE_TESTING_MATCHERS_HPP_
#define SPLITWISE_TESTING_MATCHERS_HPP_

#include <gmock/gmock-matchers.h>

namespace testing
{
namespace detail
{
    template <class MatcherType>
    inline std::string describe(const MatcherType matcher, bool negation)
    {
        std::stringstream stream;
        if (negation)
            matcher.impl().DescribeNegationTo(&stream);
        else
            matcher.impl().DescribeTo(&stream);
        return stream.str();
    }
}  // namespace detail

MATCHER_P(VoidPtrToCString, matcher, detail::describe(matcher, negation))
{
    *result_listener << "\"" << (const char*)arg << "\"";
    return matcher.impl().MatchAndExplain((const char*)arg, result_listener);
}
}  // namespace testing

#endif  // SPLITWISE_TESTING_MATCHERS_HPP_
