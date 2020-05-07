// Copyright (c) 2020 Gino Latorilla.

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
    void* raw_writer = nullptr;
    void* raw_writer_arg = nullptr;
    // Sequence s;

    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_voidp(
                    dummy_curl, CURLOPT_URL, SignedHttp("get_current_user")))
        .Times(1);
    EXPECT_CALL(mock_curl(),
                curl_easy_setopt_long(dummy_curl, CURLOPT_HTTPGET, 1L))
        .Times(1);
    EXPECT_CALL(
        mock_curl(),
        curl_easy_setopt_voidp(dummy_curl, CURLOPT_WRITEFUNCTION, NotNull()))
        .Times(1)
        .WillOnce(DoAll(SaveArg<2>(&raw_writer), Return(CURLE_OK)));
    EXPECT_CALL(
        mock_curl(),
        curl_easy_setopt_voidp(dummy_curl, CURLOPT_WRITEDATA, NotNull()))
        .Times(1)
        .WillOnce(DoAll(SaveArg<2>(&raw_writer_arg), Return(CURLE_OK)));
    EXPECT_CALL(mock_curl(), curl_easy_perform(dummy_curl))
        .Times(1)
        .WillOnce(
            WithoutArgs([&]() {
            char raw_json[] = "{\"user\":{\"last_name\":\"yeet\"}}";
            (*(curl_write_callback)raw_writer)(raw_json,
                                               sizeof(raw_json[0]),
                                               ::strlen(raw_json),
                                               raw_writer_arg);
            return CURLE_OK;
        }));

    auto user = splitwise->get_current_user();
    ASSERT_STREQ(user.json["user"]["last_name"].asCString(), "yeet");
}

}  // namespace testing
