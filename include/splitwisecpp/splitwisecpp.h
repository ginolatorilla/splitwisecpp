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
