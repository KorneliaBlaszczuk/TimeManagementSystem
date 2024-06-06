#include <gtest/gtest.h>
#include "reminder.h"

TEST(reminder_test, ctor)
{
    std::tm date = make_tm(2024, 6, 5, 10, 0);
    Reminder rm("abc", date, "details", Reminder::EVERYDAY);
    ASSERT_EQ(rm.getName(), "abc");
    ASSERT_EQ(rm.getDate().tm_year, 2024 - 1900);
    ASSERT_EQ(rm.getDate().tm_mon, 5);
    ASSERT_EQ(rm.getDate().tm_mday, 5);
    ASSERT_EQ(rm.getDate().tm_hour, 10);
    ASSERT_EQ(rm.getDate().tm_min, 0);
    ASSERT_EQ(rm.getDetails(), "details");
    ASSERT_EQ(rm.getRepetitions(), "Everyday.");
}

TEST(reminder_test, repeat_enum)
{
    std::tm date = make_tm(2024, 6, 5, 10, 0);
    Reminder rm("abc", date, "details", Reminder::EVERYDAY);
    ASSERT_EQ(rm.getRepetitions(), "Everyday.");
    rm.setRepetition(Reminder::EVERY_WEEK);
    ASSERT_EQ(rm.getRepetitions(), "Every week.");
    rm.setRepetition(Reminder::EVERY_MONTH);
    ASSERT_EQ(rm.getRepetitions(), "Every month.");
    rm.setRepetition(Reminder::NO);
    ASSERT_EQ(rm.getRepetitions(), "No repetition.");
}

TEST(reminder_test, ctor_error)
{
    ASSERT_THROW(Reminder("", {}, "", Reminder::NO), std::invalid_argument);
}

TEST(reminder_test, setDescription)
{
    std::tm date = make_tm(2024, 6, 5, 10, 0);
    Reminder rm("abc", date, "old details", Reminder::EVERYDAY);
    ASSERT_EQ(rm.getDetails(), "old details");
    rm.setDescription("");
    ASSERT_EQ(rm.getDetails(), "old details");
    rm.setDescription("new details");
    ASSERT_EQ(rm.getDetails(), "new details");
}
