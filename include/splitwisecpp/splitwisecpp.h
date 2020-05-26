// Copyright (c) 2020 Gino Latorilla.

#ifndef SPLITWISECPP_H_
#define SPLITWISECPP_H_

#include "types.h"

namespace splitwisecpp
{

class Splitwise
{
public:
    explicit Splitwise(const Configuration& config);
    ~Splitwise();

    ApiResponse get_current_user();
    ApiResponse get_user(IdType id);
    ApiResponse update_user(IdType id, const Json& payload);
    ApiResponse get_groups();
    ApiResponse create_group(const Json& payload);
    ApiResponse delete_group(IdType id);
    ApiResponse undelete_group(IdType id);
    ApiResponse add_user_to_group(const Json& payload);
    ApiResponse remove_user_from_group(const Json& payload);
    ApiResponse get_friends();
    ApiResponse get_friend(IdType id);
    ApiResponse create_friend(const Json& payload);
    ApiResponse create_friends(const Json& payload);
    ApiResponse delete_friend(IdType id);
    ApiResponse get_expenses();
    ApiResponse get_expense(IdType id);
    ApiResponse create_expenses(const Json& payload);
    ApiResponse update_expense(IdType id, const Json& payload);
    ApiResponse delete_expense(IdType id);
    ApiResponse undelete_expense(IdType id);
    ApiResponse get_comments(IdType expense_id);
    ApiResponse create_comment(const Json& payload);
    ApiResponse delete_comment(IdType id);
    ApiResponse get_notifications();
    ApiResponse get_currencies();
    ApiResponse get_categories();
    ApiResponse parse_sentence(const Json& payload);

private:
    UnspecifiedPtr _context;
};

}  // namespace splitwisecpp

#endif  // SPLITWISECPP_H_

// DO NOT EDIT BY HAND!
// 'tools/generate_cpp_api_from_descriptor' created me on 2020-05-26T14:06:27.658579 from descriptor version 0.9
