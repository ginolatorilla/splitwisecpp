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
    ApiResponse get_groups();
    ApiResponse create_group(const Json& group);
    ApiResponse delete_group(IdType id);

private:
    UnspecifiedPtr _context;
};

}  // namespace splitwisecpp

#endif  // SPLITWISECPP_H_

// DO NOT EDIT BY HAND!
// 'tools/generate_cpp_api_from_descriptor' created me on 2020-05-25T22:18:47.190784 from descriptor version 0.9
