#include <gtest/gtest.h>
#include "user.h"
#include "modes.h"

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

TEST(testUser, getFiles)
{
    User user("abc");
    ASSERT_EQ(user.getEventsFile(), "build/usersData/abc_events.txt");
    ASSERT_EQ(user.getTaskFile(), "build/usersData/abc_tasks.txt");
    ASSERT_EQ(user.getCompTaskFile(), "build/usersData/abc_task_comp.txt");
    ASSERT_EQ(user.getReminderFile(), "build/usersData/abc_reminders.txt");
}

TEST(testUser, print)
{
    User user("abc");

    std::ostringstream oss;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(oss.rdbuf());

    user.print();

    std::cout.rdbuf(oldCoutBuffer);

    EXPECT_EQ(oss.str(), "abc\n");
}
TEST(testUser, GetUser) {
    std::stringstream input("korni\n");

    std::streambuf* orig_cin = std::cin.rdbuf(input.rdbuf());
    User user = getUser("testUsers.txt"); // made while compiling
    std::cin.rdbuf(orig_cin);

    EXPECT_EQ(user.getName(), "korni");
}