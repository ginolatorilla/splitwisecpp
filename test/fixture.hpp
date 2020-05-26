#ifndef SPLITWISE_TESTING_FIXTURE_HPP_
#define SPLITWISE_TESTING_FIXTURE_HPP_

#include "MockCurl.hpp"
#include <curl/curl.h>
#include <gtest/gtest.h>
#include <memory>
#include <splitwisecpp/types.h>

namespace splitwisecpp
{
class Splitwise;
}

namespace testing
{
class splitwisecpp_api_tests : public ::testing::Test
{
public:
    splitwisecpp_api_tests();
    ~splitwisecpp_api_tests();

protected:
    MockCurl& mock_curl()
    {
        return scoped_mock.mock;
    }

    Matcher<void*> SignedHttp(const std::string& method) const;

    void expect_for_http_get_api_request(const std::string& method);
    void expect_for_http_post_api_request(const std::string& method);
    void expect_for_http_post_api_request_with_payload(const std::string& method);

    splitwisecpp::Configuration test_config;
    std::unique_ptr<splitwisecpp::Splitwise> splitwise;
    ScopedMockCurl scoped_mock;
    CURL* dummy_curl = (CURL*)0x77777777c0c0fefe;

    void* captured_write_callback = nullptr;
    void* captured_write_callback_arg = nullptr;
};
}  // namespace testing

#endif  // SPLITWISE_TESTING_FIXTURE_HPP_
