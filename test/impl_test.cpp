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
TEST_F(splitwisecpp_api_tests, respond_with_json_string)
{
    expect_for_http_get_api_request("get_current_user");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl))
        .Times(1)
        .WillOnce(HttpResponse(R"({"user":{"last_name":"yeet"}})",
                               captured_write_callback,
                               captured_write_callback_arg));

    auto user = splitwise->get_current_user();
    ASSERT_STREQ(user.json["user"]["last_name"].asCString(), "yeet");
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, cannot_find_server)
{
    expect_for_http_get_api_request("get_current_user");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl))
        .Times(1)
        .WillOnce(Return(CURLE_COULDNT_RESOLVE_HOST));

    auto user = splitwise->get_current_user();
    ASSERT_EQ(splitwisecpp::ErrorCodes::NetworkError, user.error);
}

TEST_F(splitwisecpp_api_tests, out_of_memory)
{
    EXPECT_CALL(mock_curl(), curl_easy_setopt_voidp(dummy_curl, CURLOPT_URL, _))
        .Times(1)
        .WillOnce(Return(CURLE_OUT_OF_MEMORY));
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_voidp(dummy_curl, CURLOPT_WRITEDATA, _))
        .Times(1);
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_voidp(dummy_curl, CURLOPT_WRITEFUNCTION, _))
        .Times(1);
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(0);

    auto user = splitwise->get_current_user();
    ASSERT_EQ(splitwisecpp::ErrorCodes::OutOfMemory, user.error);
}

TEST_F(splitwisecpp_api_tests, http_get_without_parameters)
{
    expect_for_http_get_api_request("get_current_user");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1);
    auto user = splitwise->get_current_user();
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, http_get_with_parameter)
{
    expect_for_http_get_api_request("get_user/12345");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl))
        .Times(1)
        .WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_user(12345);
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, http_get_with_query_parameters)
{
    expect_for_http_get_api_request("get_comments?expense_id=12345");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl))
        .Times(1)
        .WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_comments(12345);
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, http_post_with_payload_and_without_parameter)
{
    expect_for_http_post_api_request_with_payload("create_group");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl))
        .Times(1)
        .WillOnce(Return(CURLE_OK));
    auto user = splitwise->create_group(Json::Value(0));
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, http_post_without_payload_and_with_parameter)
{
    expect_for_http_post_api_request("delete_group/12345");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl))
        .Times(1)
        .WillOnce(Return(CURLE_OK));
    auto user = splitwise->delete_group(12345);
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}
}  // namespace testing
