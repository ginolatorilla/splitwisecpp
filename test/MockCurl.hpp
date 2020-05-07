#ifndef SPLITWISE_TESTING_CURL_STUB_HPP_
#define SPLITWISE_TESTING_CURL_STUB_HPP_

#include <curl/curl.h>
#include <gmock/gmock-function-mocker.h>

namespace testing
{
class MockCurl
{
public:
    MockCurl();
    ~MockCurl();

    MOCK_METHOD(::CURLcode, curl_easy_perform, (::CURL*));
    MOCK_METHOD(::CURL*, curl_easy_init, ());
    MOCK_METHOD(::curl_slist*, curl_slist_append, (::curl_slist*, const char*));
    MOCK_METHOD(void, curl_easy_cleanup, (::CURL*));
    MOCK_METHOD(void, curl_slist_free_all, (::curl_slist*));
    MOCK_METHOD(::CURLcode,
                curl_easy_setopt_long,
                (::CURL*, ::CURLoption, long));
    MOCK_METHOD(::CURLcode,
                curl_easy_setopt_voidp,
                (::CURL*, ::CURLoption, void*));

    static MockCurl& get()
    {
        assert(mocker != nullptr);
        return *mocker;
    }

    static void hook(MockCurl& subscriber)
    {
        mocker = &subscriber;
    }

    static MockCurl* release()
    {
        auto* released = mocker;
        mocker = nullptr;
        return released;
    }

private:
    static MockCurl* mocker;
};

struct ScopedMockCurl
{
    ScopedMockCurl()
    {
        MockCurl::hook(mock);
    }

    ~ScopedMockCurl()
    {
        [this] { ASSERT_EQ(&mock, MockCurl::release()); }();
    }

    MockCurl mock;
};
}  // namespace testing

#endif  // SPLITWISE_TESTING_CURL_STUB_HPP_
