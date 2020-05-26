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
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_current_user();
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_user)
{
    expect_for_http_get_api_request("get_user/12345");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_user(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, update_user)
{
    expect_for_http_post_api_request_with_payload("update_user");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->update_user(12345,::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_groups)
{
    expect_for_http_get_api_request("get_groups");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_groups();
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, create_group)
{
    expect_for_http_post_api_request_with_payload("create_group");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->create_group(::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, delete_group)
{
    expect_for_http_post_api_request("delete_group");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->delete_group(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, undelete_group)
{
    expect_for_http_post_api_request("undelete_group");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->undelete_group(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, add_user_to_group)
{
    expect_for_http_post_api_request_with_payload("add_user_to_group");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->add_user_to_group(::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, remove_user_from_group)
{
    expect_for_http_post_api_request_with_payload("remove_user_from_group");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->remove_user_from_group(::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_friends)
{
    expect_for_http_get_api_request("get_friends");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_friends();
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_friend)
{
    expect_for_http_get_api_request("get_friend/12345");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_friend(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, create_friend)
{
    expect_for_http_post_api_request_with_payload("create_friend");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->create_friend(::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, create_friends)
{
    expect_for_http_post_api_request_with_payload("create_friends");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->create_friends(::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, delete_friend)
{
    expect_for_http_post_api_request("delete_friend");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->delete_friend(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_expenses)
{
    expect_for_http_get_api_request("get_expenses");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_expenses();
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_expense)
{
    expect_for_http_get_api_request("get_expense/12345");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_expense(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, create_expenses)
{
    expect_for_http_post_api_request_with_payload("create_expenses");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->create_expenses(::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, update_expense)
{
    expect_for_http_post_api_request_with_payload("update_expense");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->update_expense(12345,::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, delete_expense)
{
    expect_for_http_post_api_request("delete_expense");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->delete_expense(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, undelete_expense)
{
    expect_for_http_post_api_request("undelete_expense");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->undelete_expense(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_comments)
{
    expect_for_http_get_api_request("get_comments?expense_id=12345");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_comments(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, create_comment)
{
    expect_for_http_post_api_request_with_payload("create_comment");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->create_comment(::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, delete_comment)
{
    expect_for_http_post_api_request("delete_comment");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->delete_comment(12345);
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_notifications)
{
    expect_for_http_get_api_request("get_notifications");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_notifications();
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_currencies)
{
    expect_for_http_get_api_request("get_currencies");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_currencies();
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_categories)
{
    expect_for_http_get_api_request("get_categories");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->get_categories();
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, parse_sentence)
{
    expect_for_http_post_api_request_with_payload("parse_sentence");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1).WillOnce(Return(CURLE_OK));
    auto user = splitwise->parse_sentence(::Json::Value(0xDEADBEEF));
    EXPECT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

}  // namespace testing

// DO NOT EDIT BY HAND!
// 'tools/generate_cpp_api_from_descriptor' created me on 2020-05-26T16:29:21.668097 from descriptor version 0.9
