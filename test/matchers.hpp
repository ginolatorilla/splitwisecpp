#ifndef SPLITWISE_TESTING_MATCHERS_HPP_
#define SPLITWISE_TESTING_MATCHERS_HPP_

#include <gmock/gmock-matchers.h>
#include <json/json.h>

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

MATCHER_P(AsJson, expected, "")
{
    std::string arg_str = reinterpret_cast<char*>(arg);
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    Json::Value actual;
    reader->parse(arg_str.c_str(), arg_str.c_str() + arg_str.size(), &actual, nullptr);
    *result_listener << actual;
    return expected == actual;
}
}  // namespace testing

#endif  // SPLITWISE_TESTING_MATCHERS_HPP_
