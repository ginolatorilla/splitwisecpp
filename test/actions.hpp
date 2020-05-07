#ifndef SPLITWISE_TESTING_ACTIONS_HPP_
#define SPLITWISE_TESTING_ACTIONS_HPP_

#include <curl/curl.h>
#include <gmock/gmock-actions.h>

namespace testing
{
Action<::CURLcode(::CURL*)> HttpResponse(const std::string& json,
                                         void*& write_callback,
                                         void*& write_callback_arg);


}  // namespace testing

#endif  // SPLITWISE_TESTING_ACTIONS_HPP_
