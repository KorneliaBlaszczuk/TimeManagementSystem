#include <gtest/gtest.h>
#include "user.h"

TEST(testUser, ctor_user)
{
    User user("abc");
    ASSERT_EQ(user.getName(), "abc");
}

TEST(testUser, ctor_user_error)
{
    ASSERT_THROW(User(""), std::invalid_argument);
}

TEST(testUser, setName_user)
{
    User user("abc");
    ASSERT_EQ(user.getName(), "abc");
    user.setName("");
    ASSERT_EQ(user.getName(), "abc");
    user.setName("bcd1");
    ASSERT_EQ(user.getName(), "bcd1");
}