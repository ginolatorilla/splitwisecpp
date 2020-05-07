#include "actions.hpp"
#include <curl/curl.h>

namespace testing
{
Action<::CURLcode(::CURL*)> HttpResponse(const std::string& json,
                                         void*& write_callback,
                                         void*& write_callback_arg)
{
    // 'json' here has to be copied in the closure to preserve it
    return WithoutArgs([json, &write_callback, &write_callback_arg]() {
        (*(curl_write_callback)write_callback)((char*)json.c_str(),
                                               sizeof(json[0]),
                                               json.size(),
                                               write_callback_arg);
        return CURLE_OK;
    });
}
}  // namespace testing