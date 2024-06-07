#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "event.h"

TEST(EventTest, EventPrintsCorrectly)
{
    std::tm startEvent = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent = make_tm(2024, 6, 5, 12, 0);
    Event event("Meeting", startEvent, endEvent, "Conference Room", {"Alice", "Bob"});

    std::ostringstream output;
    event.print();
    std::string expectedOutput = "Meeting             2024-06-05 10:00    2024-06-05 12:00    Conference Room     Alice, Bob, \n";
    testing::internal::CaptureStdout();
    event.print();
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

TEST(EventTest, get)
{
    std::tm startEvent = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent = make_tm(2024, 6, 5, 12, 0);
    std::vector<std::string> r({"Alice", "Bob"});
    Event event("Meeting", startEvent, endEvent, "Conference Room", {"Alice", "Bob"});
    ASSERT_EQ(event.getName(), "Meeting");
    ASSERT_EQ(event.getLocation(), "Conference Room");
    ASSERT_EQ(event.getAttendees(), r);
}

TEST(EventTest, GetDates)
{
    std::tm startEvent = make_tm(2024, 6, 5, 10, 3);
    std::tm endEvent = make_tm(2025, 6, 5, 12, 0);
    std::vector<std::string> r({"Alice", "Bob"});
    Event event("Meeting", startEvent, endEvent, "Conference Room", {"Alice", "Bob"});
    ASSERT_EQ(event.getStart().tm_year, 124);
    ASSERT_EQ(event.getEnd().tm_year, 125);
    ASSERT_EQ(event.getStart().tm_mon, 5);
    ASSERT_EQ(event.getEnd().tm_mon, 5);
    ASSERT_EQ(event.getStart().tm_mday, 5);
    ASSERT_EQ(event.getEnd().tm_mday, 5);
    ASSERT_EQ(event.getStart().tm_hour, 10);
    ASSERT_EQ(event.getEnd().tm_hour, 12);
    ASSERT_EQ(event.getStart().tm_min, 3);
    ASSERT_EQ(event.getEnd().tm_min, 0);
}

TEST(EventTest, set)
{
    std::tm startEvent = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent = make_tm(2024, 6, 5, 12, 0);
    std::vector<std::string> r({"Alice", "Bob"});
    std::vector<std::string> r2({"Alice", "Bob", "Dylan"});
    Event event("Meeting", startEvent, endEvent, "Conference Room", {"Alice", "Bob"});
    ASSERT_EQ(event.getName(), "Meeting");
    ASSERT_EQ(event.getLocation(), "Conference Room");
    ASSERT_EQ(event.getAttendees(), r);
    event.setAttendees(r2);
    ASSERT_EQ(event.getAttendees(), r2);
    event.setLocation("Office");
    ASSERT_EQ(event.getLocation(), "Office");
    event.setName("Task");
    ASSERT_EQ(event.getName(), "Task");
}

TEST(EventTest, ConstructorAndAccessors)
{
    std::tm start = {};
    start.tm_year = 2023 - 1900;
    start.tm_mon = 5 - 1;
    start.tm_mday = 10;
    start.tm_hour = 10;
    start.tm_min = 30;

    std::tm end = start;
    end.tm_hour = 12;

    std::vector<std::string> attendees = {"John Doe", "Jane Smith"};

    Event event("Meeting", start, end, "Conference Room", attendees);

    EXPECT_EQ(event.getName(), "Meeting");
    EXPECT_EQ(event.getStart().tm_year, 2023 - 1900);
    EXPECT_EQ(event.getStart().tm_mon, 5 - 1);
    EXPECT_EQ(event.getStart().tm_mday, 10);
    EXPECT_EQ(event.getStart().tm_hour, 10);
    EXPECT_EQ(event.getStart().tm_min, 30);
    EXPECT_EQ(event.getEnd().tm_hour, 12);
    EXPECT_EQ(event.getLocation(), "Conference Room");
    EXPECT_EQ(event.getAttendees(), attendees);
}

TEST(EventTest, SetAndGetStart)
{
    std::tm start = {};
    std::tm newStart = {};
    start.tm_year = 2023 - 1900;
    std::vector<std::string> attendees = {};

    Event event("Meeting", start, start, "Conference Room", attendees);

    newStart.tm_year = 2024 - 1900;
    event.setStart(newStart);
    EXPECT_EQ(event.getStart().tm_year, 2024 - 1900);
}

TEST(EventTest, SetAndGetEnd)
{
    std::tm end = {};
    std::tm newEnd = {};
    end.tm_year = 2023 - 1900;
    std::vector<std::string> attendees = {};

    Event event("Meeting", end, end, "Conference Room", attendees);

    newEnd.tm_year = 2024 - 1900;
    event.setEnd(newEnd);
    EXPECT_EQ(event.getEnd().tm_year, 2024 - 1900);
}

TEST(EventTest, SetAndGetLocation)
{
    std::tm start = {};
    std::tm end = {};
    std::vector<std::string> attendees = {};

    Event event("Meeting", start, end, "Old Location", attendees);

    event.setLocation("New Location");
    EXPECT_EQ(event.getLocation(), "New Location");
}

TEST(EventTest, SetAndGetAttendees)
{
    std::tm start = {};
    std::tm end = {};
    std::vector<std::string> attendees = {"John Doe", "Jane Smith"};

    Event event("Meeting", start, end, "Conference Room", attendees);

    std::vector<std::string> newAttendees = {"Alice", "Bob"};
    event.setAttendees(newAttendees);
    EXPECT_EQ(event.getAttendees(), newAttendees);
}
