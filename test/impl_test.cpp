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
TEST_F(splitwisecpp_api_tests, generic_respond_with_json_string)
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

TEST_F(splitwisecpp_api_tests, generic_cannot_find_server)
{
    expect_for_http_get_api_request("get_current_user");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl))
        .Times(1)
        .WillOnce(Return(CURLE_COULDNT_RESOLVE_HOST));

    auto user = splitwise->get_current_user();
    ASSERT_EQ(splitwisecpp::ErrorCodes::NetworkError, user.error);
}

TEST_F(splitwisecpp_api_tests, DISABLED_generic_out_of_memory)
{
    EXPECT_CALL(mock_curl(), curl_easy_setopt_voidp(dummy_curl, CURLOPT_URL, _))
        .Times(1)
        .WillOnce(Return(CURLE_OUT_OF_MEMORY));

    auto user = splitwise->get_current_user();
    ASSERT_EQ(splitwisecpp::ErrorCodes::OutOfMemory, user.error);
}

TEST_F(splitwisecpp_api_tests, get_current_user)
{
    expect_for_http_get_api_request("get_current_user");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1);
    auto user = splitwise->get_current_user();
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_user)
{
    expect_for_http_get_api_request("get_user/12345");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1);
    auto user = splitwise->get_user(12345);
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, get_groups)
{
    expect_for_http_get_api_request("get_groups");
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1);
    auto user = splitwise->get_groups();
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}

TEST_F(splitwisecpp_api_tests, create_group)
{
    ::curl_slist* dummy_slist = (::curl_slist*)0x5050ffffecec0a0a;

    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_voidp(
                    dummy_curl,
                    CURLOPT_URL,
                    VoidPtrToCString(StrEq(
                        "https://secure.splitwise.com/api/v3.0/create_group"))))
        .Times(1);
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_voidp(dummy_curl,
                                       CURLOPT_CUSTOMREQUEST,
                                       VoidPtrToCString(StrEq("POST"))))
        .Times(1);
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_long(dummy_curl, CURLOPT_VERBOSE, 1L)) // TODO: Remove in code
        .Times(1);
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_voidp(
                    dummy_curl, CURLOPT_WRITEDATA, _))  // TODO: Remove in code
        .Times(1);
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_voidp(dummy_curl,
                                       CURLOPT_WRITEFUNCTION,
                                       _))  // TODO: Remove in code
        .Times(1);
    EXPECT_CALL(mock_curl(),
                curl_slist_append(IsNull(), StartsWith("Authorization: OAuth")))
        .Times(1)
        .WillOnce(Return(dummy_slist));
    EXPECT_CALL(mock_curl(),
                curl_slist_append(dummy_slist,
                                  StartsWith("Content-Type: application/json")))
        .Times(1)
        .WillOnce(Return(dummy_slist));
    EXPECT_CALL(
        mock_curl(),
        curl_easy_setopt_voidp(dummy_curl, CURLOPT_HTTPHEADER, dummy_slist))
        .Times(1);
    EXPECT_CALL(
        mock_curl(),
        curl_easy_setopt_voidp(dummy_curl, CURLOPT_POSTFIELDS, AsJson([] {
                                   splitwisecpp::Json request;
                                   request["name"] = "Groupy McGroupface";
                                   request["users_0_user_id"] = 12345;
                                   return request;
                               }())))
        .Times(1);
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl)).Times(1);
    EXPECT_CALL(mock_curl(), curl_slist_free_all(dummy_slist)).Times(1);
    auto user = splitwise->create_group([] {
        splitwisecpp::Json request;
        request["name"] = "Groupy McGroupface";
        request["users_0_user_id"] = 12345;
        return request;
    }());
    ASSERT_EQ(splitwisecpp::ErrorCodes::NoError, user.error);
}
}  // namespace testing
