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

TEST(reminder_test, updatingReminders_no)
{
    std::tm time_new = make_tm(2024, 6, 7, 12, 0);
    std::tm date = make_tm(2024, 6, 5, 10, 0);
    Reminder rm("abc", date, "old details", Reminder::NO);
    rm.changeDate(time_new);
    ASSERT_EQ(rm.getDate().tm_year, 124);
    ASSERT_EQ(rm.getDate().tm_mon, 5);
    ASSERT_EQ(rm.getDate().tm_mday, 5);
    ASSERT_EQ(rm.getDate().tm_hour, 10);
    ASSERT_EQ(rm.getDate().tm_min, 0);
}

TEST(reminder_test, updatingReminders_everyday)
{
    std::tm time_new = make_tm(2024, 6, 7, 12, 0);
    std::tm date = make_tm(2024, 6, 5, 10, 0);
    Reminder rm("abc", date, "old details", Reminder::EVERYDAY);
    rm.changeDate(time_new);
    ASSERT_EQ(rm.getDate().tm_year, 124);
    ASSERT_EQ(rm.getDate().tm_mon, 5);
    ASSERT_EQ(rm.getDate().tm_mday, 8);
    ASSERT_EQ(rm.getDate().tm_hour, 10);
    ASSERT_EQ(rm.getDate().tm_min, 0);
}

TEST(reminder_test, updatingReminders_everyday_diff_month)
{
    std::tm time_new = make_tm(2024, 5, 31, 12, 0);
    std::tm date = make_tm(2024, 5, 31, 10, 0);
    Reminder rm("abc", date, "old details", Reminder::EVERYDAY);
    rm.changeDate(time_new);
    ASSERT_EQ(rm.getDate().tm_year, 124);
    ASSERT_EQ(rm.getDate().tm_mon, 5);
    ASSERT_EQ(rm.getDate().tm_mday, 1);
    ASSERT_EQ(rm.getDate().tm_hour, 10);
    ASSERT_EQ(rm.getDate().tm_min, 0);
}

TEST(reminder_test, updatingReminders_everyweek)
{
    std::tm time_new = make_tm(2024, 6, 7, 12, 0);
    std::tm date = make_tm(2024, 6, 5, 10, 0);
    Reminder rm("abc", date, "old details", Reminder::EVERY_WEEK);
    rm.changeDate(time_new);
    ASSERT_EQ(rm.getDate().tm_year, 124);
    ASSERT_EQ(rm.getDate().tm_mon, 5);
    ASSERT_EQ(rm.getDate().tm_mday, 12);
    ASSERT_EQ(rm.getDate().tm_hour, 10);
    ASSERT_EQ(rm.getDate().tm_min, 0);
}

TEST(reminder_test, updatingReminders_everyweek_diff_mon)
{
    std::tm time_new = make_tm(2024, 6, 5, 12, 0);
    std::tm date = make_tm(2024, 5, 30, 10, 0);
    Reminder rm("abc", date, "old details", Reminder::EVERY_WEEK);
    rm.changeDate(time_new);
    ASSERT_EQ(rm.getDate().tm_year, 124);
    ASSERT_EQ(rm.getDate().tm_mon, 5);
    ASSERT_EQ(rm.getDate().tm_mday, 6);
    ASSERT_EQ(rm.getDate().tm_hour, 10);
    ASSERT_EQ(rm.getDate().tm_min, 0);
}

TEST(reminder_test, updateReminders_everyMon)
{
    std::tm time_new = make_tm(2024, 6, 7, 12, 0);
    std::tm date = make_tm(2024, 6, 5, 10, 0);
    Reminder rm("abc", date, "old details", Reminder::EVERY_MONTH);
    rm.changeDate(time_new);
    ASSERT_EQ(rm.getDate().tm_year, 124);
    ASSERT_EQ(rm.getDate().tm_mon, 6);
    ASSERT_EQ(rm.getDate().tm_mday, 5);
    ASSERT_EQ(rm.getDate().tm_hour, 10);
    ASSERT_EQ(rm.getDate().tm_min, 0);
}

TEST(reminder_test, updateReminders_everyMon_diff_year)
{
    std::tm time_new = make_tm(2024, 12, 17, 12, 0);
    std::tm date = make_tm(2024, 12, 5, 10, 0);
    Reminder rm("abc", date, "old details", Reminder::EVERY_MONTH);
    rm.changeDate(time_new);
    ASSERT_EQ(rm.getDate().tm_year, 125);
    ASSERT_EQ(rm.getDate().tm_mon, 0);
    ASSERT_EQ(rm.getDate().tm_mday, 5);
    ASSERT_EQ(rm.getDate().tm_hour, 10);
    ASSERT_EQ(rm.getDate().tm_min, 0);
}

TEST(reminder_test, printReminder)
{
    std::tm reminderDate1 = make_tm(2024, 6, 5);
    Reminder rm1("Finish Report", reminderDate1, "Work in progress", Reminder::NO);
    std::ostringstream output;
    rm1.print();
    std::string expectedOutput = "2024-06-05          Finish Report       Work in progress                        No repetition.      \n";
    testing::internal::CaptureStdout();
    rm1.print();
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}