// Copyright (c) 2020 Gino Latorilla.

#include "actions.hpp"
#include "fixture.hpp"
#include "matchers.hpp"
#include "splitwisecpp/splitwisecpp.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <json/writer.h>  // TODO: Mention in FAQ if operator<< doesn't work

namespace testing
{
TEST_F(splitwisecpp_api_tests, get_current_user)
{
    expect_for_http_get_api_request("get_current_user");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl))
        .Times(1)
        .WillOnce(HttpResponse(R"({"user":{"last_name":"yeet"}})",
                               captured_write_callback,
                               captured_write_callback_arg));

    auto user = splitwise->get_current_user();
    ASSERT_STREQ(user.json["user"]["last_name"].asCString(), "yeet");
}

}  // namespace testing
