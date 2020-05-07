#include "fixture.hpp"
#include "matchers.hpp"
#include <gmock/gmock-more-actions.h>
#include <splitwisecpp/splitwisecpp.h>

namespace testing
{
const char* const BASEURL = "https://secure.splitwise.com/api/v3.0";

splitwisecpp_api_tests::splitwisecpp_api_tests()
{
    test_config.consumer_key = "__the_consumer_key__";
    test_config.consumer_secret = "__the_consumer_secret__";
    test_config.oauth1_token = "__the_token__";
    test_config.oauth1_token_secret = "__the_token_secret__";

    EXPECT_CALL(mock_curl(), curl_easy_init())
        .Times(1)
        .WillOnce(Return(dummy_curl));
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_long(dummy_curl, CURLOPT_FOLLOWLOCATION, 1L))
        .Times(1);
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_voidp(dummy_curl,
                                       CURLOPT_DEFAULT_PROTOCOL,
                                       VoidPtrToCString(StrEq("https"))))
        .Times(1);
    splitwise.reset(new decltype(splitwise)::element_type(test_config));
}

splitwisecpp_api_tests::~splitwisecpp_api_tests()
{
    EXPECT_CALL(mock_curl(), curl_easy_cleanup(dummy_curl)).Times(1);
    splitwise.reset(nullptr);
}

Matcher<void*> splitwisecpp_api_tests::SignedHttp(
    const std::string& method) const
{
    return AllOf(
        VoidPtrToCString(StartsWith(std::string(BASEURL) + "/" + method + "?")),
        VoidPtrToCString(HasSubstr("oauth_signature_method=HMAC-SHA1")),
        VoidPtrToCString(HasSubstr("oauth_version=1.0")),
#ifdef GTEST_USES_POSIX_RE
        VoidPtrToCString(ContainsRegex("oauth_signature=[A-Za-z0-9%]+")),
        VoidPtrToCString(ContainsRegex("oauth_nonce=[a-f0-9]+.*")),
        VoidPtrToCString(ContainsRegex("oauth_timestamp=[0-9]+")),
#else  // Windows, see
       // https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#regular-expression-syntax
        VoidPtrToCString(ContainsRegex("oauth_signature=.+")),
        VoidPtrToCString(ContainsRegex("oauth_nonce=.+")),
        VoidPtrToCString(ContainsRegex("oauth_timestamp=\\d+")),
#endif
        VoidPtrToCString(HasSubstr(std::string("oauth_consumer_key=") +
                                   test_config.consumer_key)),
        VoidPtrToCString(
            HasSubstr(std::string("oauth_token=") + test_config.oauth1_token)));
}

void splitwisecpp_api_tests::expect_for_http_get_api_request(
    const std::string& method)
{
    EXPECT_CALL(
        mock_curl(),
        curl_easy_setopt_voidp(dummy_curl, CURLOPT_URL, SignedHttp(method)))
        .Times(1);
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_long(dummy_curl, CURLOPT_HTTPGET, 1L))
        .Times(1);
    EXPECT_CALL(
        mock_curl(),
        curl_easy_setopt_voidp(dummy_curl, CURLOPT_WRITEFUNCTION, NotNull()))
        .Times(1)
        .WillOnce(
            DoAll(SaveArg<2>(&captured_write_callback), Return(CURLE_OK)));
    EXPECT_CALL(
        mock_curl(),
        curl_easy_setopt_voidp(dummy_curl, CURLOPT_WRITEDATA, NotNull()))
        .Times(1)
        .WillOnce(
            DoAll(SaveArg<2>(&captured_write_callback_arg), Return(CURLE_OK)));
}
}  // namespace testing
