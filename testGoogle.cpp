#include <gtest/gtest.h>
#include "calendar_v_3.h"

// Helper function to compare two tm structs
bool compare_tm(const std::tm& tm1, const std::tm& tm2) {
    return std::mktime(const_cast<std::tm*>(&tm1)) == std::mktime(const_cast<std::tm*>(&tm2));
}

// Test case for getCurrentDate function
TEST(CalendarTest, GetCurrentDate) {
    std::tm expected = getCurrentDate();
    std::time_t t = std::time(nullptr);
    std::tm* currentTime = std::localtime(&t);
    EXPECT_TRUE(compare_tm(expected, *currentTime));
}

// Test case for getCurrentWeekRange function
TEST(CalendarTest, GetCurrentWeekRange) {
    std::tm weekStart, weekEnd;
    getCurrentWeekRange(weekStart, weekEnd);

    // Check if weekStart is a Monday and weekEnd is a Sunday
    EXPECT_EQ(weekStart.tm_wday, 1); // Monday
    EXPECT_EQ(weekEnd.tm_wday, 0);   // Sunday

    // Check if weekEnd is exactly 6 days after weekStart
    EXPECT_EQ(std::difftime(std::mktime(&weekEnd), std::mktime(&weekStart)), 6 * 24 * 60 * 60);

    // Check if weekStart and weekEnd are in the same week
    EXPECT_EQ(weekStart.tm_yday / 7, weekEnd.tm_yday / 7);
}

// Test case for getCurrentMonthRange function
TEST(CalendarTest, GetCurrentMonthRange) {
    std::tm monthStart, monthEnd;
    getCurrentMonthRange(monthStart, monthEnd);

    // Check if monthStart is the first day of the month and monthEnd is the last day of the month
    EXPECT_EQ(monthStart.tm_mday, 1);
    EXPECT_EQ(monthEnd.tm_mday, 0);

    // Check if monthEnd is exactly one month after monthStart
    EXPECT_EQ(monthStart.tm_mon + 1, monthEnd.tm_mon);

    // Check if monthStart and monthEnd are in the same month
    EXPECT_EQ(monthStart.tm_mon, monthEnd.tm_mon);
}

// Test case for adding an event
TEST(CalendarTest, AddEvent) {
    Calendar calendar;
    Interface interface;
    std::tm start = make_tm(2024, 6, 5, 10, 0); // June 5, 2024, 10:00 AM
    std::tm end = make_tm(2024, 6, 5, 12, 0);   // June 5, 2024, 12:00 PM
    std::vector<std::string> attendees = {"John", "Alice"};
    Event event("Meeting", start, end, "Office", attendees);
    calendar.addEvent(event);

    // Check if the event was added to the calendar
    EXPECT_EQ(calendar.events.size(), 1);
    EXPECT_EQ(calendar.events[0].getName(), "Meeting");
    EXPECT_TRUE(compare_tm(calendar.events[0].start, start));
    EXPECT_TRUE(compare_tm(calendar.events[0].end, end));
    EXPECT_EQ(calendar.events[0].location, "Office");
    EXPECT_EQ(calendar.events[0].attendees.size(), 2);
    EXPECT_EQ(calendar.events[0].attendees[0], "John");
    EXPECT_EQ(calendar.events[0].attendees[1], "Alice");
}

// Test case for adding a task
TEST(CalendarTest, AddTask) {
    Calendar calendar;
    Interface interface;
    std::tm date = make_tm(2024, 6, 5); // June 5, 2024
    Task task("Study", date, true, "Finish Chapter 5", Task::PENDING);
    calendar.addTask(task);

    // Check if the task was added to the calendar
    EXPECT_EQ(calendar.tasks.size(), 1);
    EXPECT_EQ(calendar.tasks[0].getName(), "Study");
    EXPECT_TRUE(compare_tm(calendar.tasks[0].getDate(), date));
    EXPECT_EQ(calendar.tasks[0].important, true);
    EXPECT_EQ(calendar.tasks[0].progressNote, "Finish Chapter 5");
    EXPECT_EQ(calendar.tasks[0].progressStatus, Task::PENDING);
}

// Test case for editing an event
TEST(CalendarTest, EditEvent) {
    Calendar calendar;
    Interface interface;
    std::tm start = make_tm(2024, 6, 5, 10, 0); // June 5, 2024, 10:00 AM
    std::tm end = make_tm(2024, 6, 5, 12, 0);   // June 5, 2024, 12:00 PM
    std::vector<std::string> attendees = {"John", "Alice"};
    Event event("Meeting", start, end, "Office", attendees);
    calendar.addEvent(event);

    // Edit the event
    interface.editEvent(calendar);

    // Check if the event was edited successfully
    EXPECT_EQ(calendar.events.size(), 1);
    EXPECT_EQ(calendar.events[0].getName(), "Edited Meeting");
    // Check other attributes as well
}

// Test case for editing a task
TEST(CalendarTest, EditTask) {
    Calendar calendar;
    Interface interface;
    std::tm date = make_tm(2024, 6, 5); // June 5, 2024
    Task task("Study", date, true, "Finish Chapter 5", Task::PENDING);
    calendar.addTask(task);

    // Edit the task
    interface.editTask(calendar);

    // Check if the task was edited successfully
    EXPECT_EQ(calendar.tasks.size(), 1);
    EXPECT_EQ(calendar.tasks[0].getName(), "Edited Study");
    // Check other attributes as well
}

// Test case for filtering events
TEST(CalendarTest, FilterEvents) {
    Calendar calendar;
    Interface interface;
    std::tm start = make_tm(2024, 6, 1); // June 1, 2024
    std::tm end = make_tm(2024, 6, 30);  // June 30, 2024
    // Add events to the calendar
    // ...
    // Filter events for June 2024
    auto filteredEvents = calendar.filterEvents(start, end);

    // Check if the filtered events are correct
    // ...
}

// Test case for filtering tasks
TEST(CalendarTest, FilterTasks) {
    Calendar calendar;
    Interface interface;
    std::tm start = make_tm(2024, 6, 1); // June 1, 2024
    std::tm end = make_tm(2024, 6, 30);  // June 30, 2024
    // Add tasks to the calendar
    // ...
    // Filter tasks for June 2024
    auto filteredTasks = calendar.filterTasks(start, end);

    // Check if the filtered tasks are correct
    // ...
}

// Test case for selecting month and displaying events
TEST(CalendarTest, SelectMonthAndDisplayEvents) {
    Calendar calendar;
    Interface interface;
    // Add events to the calendar
    // ...
    // Call selectMonthAndDisplayEvents
    interface.selectMonthAndDisplayEvents(calendar);
}
