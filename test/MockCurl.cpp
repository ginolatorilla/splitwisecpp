#include "MockCurl.hpp"
#include <cstdarg>

namespace testing
{
MockCurl* MockCurl::mocker = nullptr;
MockCurl::MockCurl() = default;
MockCurl::~MockCurl() = default;
}  // namespace testing

::CURLcode curl_easy_perform(::CURL* curl)
{
    return testing::MockCurl::get().curl_easy_perform(curl);
}

::CURL* curl_easy_init()
{
    return testing::MockCurl::get().curl_easy_init();
}

::curl_slist* curl_slist_append(::curl_slist* slist, const char* item)
{
    return testing::MockCurl::get().curl_slist_append(slist, item);
}

void curl_easy_cleanup(::CURL* curl)
{
    testing::MockCurl::get().curl_easy_cleanup(curl);
}

void curl_slist_free_all(::curl_slist* slist)
{
    testing::MockCurl::get().curl_slist_free_all(slist);
}

::CURLcode curl_easy_setopt(::CURL* curl, ::CURLoption option, ...)
{
    va_list args;
    va_start(args, option);

    if (option < CURLOPTTYPE_OBJECTPOINT)
    {
        va_end(args);
        return testing::MockCurl::get().curl_easy_setopt_long(
            curl, option, va_arg(args, long));
    }
    else if (option < CURLOPTTYPE_OFF_T)
    {
        va_end(args);
        return testing::MockCurl::get().curl_easy_setopt_voidp(
            curl, option, va_arg(args, void*));
    }
    else
    {
        assert(0 && "No handler");
        return CURLE_FUNCTION_NOT_FOUND;
    }
}
