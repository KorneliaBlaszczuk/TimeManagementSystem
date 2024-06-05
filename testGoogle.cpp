#include <gtest/gtest.h>
#include <sstream>
#include "calendar_v_3.h"

TEST(EventTest, EventPrintsCorrectly) {
    std::tm startEvent = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent = make_tm(2024, 6, 5, 12, 0);
    Event event("Meeting", startEvent, endEvent, "Conference Room", {"Alice", "Bob"});

    std::ostringstream output;
    event.print();
    std::string expectedOutput = "Meeting             2024-06-05 10:00    2024-06-05 12:00    Conference Room     Attendees: Alice Bob \n";
    testing::internal::CaptureStdout();
    event.print();
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

// Testy dla klasy Task
TEST(TaskTest, TaskPrintsCorrectly) {
    std::tm taskDate = make_tm(2024, 6, 5);
    Task task("Finish Report", taskDate, true, "Work in progress", Task::PENDING);

    std::ostringstream output;
    task.print();
    std::string expectedOutput = "2024-06-05          Finish Report       Important           Pending             Work in progress\n";
    testing::internal::CaptureStdout();
    task.print();
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}

// Testy dla klasy Calendar - dodawanie i filtrowanie wydarzeń
TEST(CalendarTest, AddingAndFilteringEvents) {
    Calendar calendar;

    std::tm startEvent1 = make_tm(2024, 6, 5, 10, 0);
    std::tm endEvent1 = make_tm(2024, 6, 5, 12, 0);
    Event event1("Meeting", startEvent1, endEvent1, "Conference Room", {"Alice", "Bob"});

    std::tm startEvent2 = make_tm(2024, 6, 7, 14, 0);
    std::tm endEvent2 = make_tm(2024, 6, 7, 16, 0);
    Event event2("Presentation", startEvent2, endEvent2, "Auditorium", {"Charlie", "David"});

    calendar.addEvent(event1);
    calendar.addEvent(event2);

    std::ostringstream output;
    for(const auto& event : calendar.filterEvents(make_tm(2024, 6, 5), make_tm(2024, 6, 6))) {
        event.print();
    }
    std::string expectedOutput = "Meeting             2024-06-05 10:00    2024-06-05 12:00    Conference Room     Attendees: Alice Bob \n";
    testing::internal::CaptureStdout();
    std::string outputStr = "";
    for(const auto& event : calendar.filterEvents(make_tm(2024, 6, 5), make_tm(2024, 6, 6))) {
        event.print();
        outputStr += testing::internal::GetCapturedStdout();
    }

    ASSERT_EQ(outputStr, expectedOutput);
}

// Testy dla klasy Calendar - dodawanie i filtrowanie zadań
TEST(CalendarTest, AddingAndFilteringTasks) {
    Calendar calendar;

    std::tm taskDate1 = make_tm(2024, 6, 5);
    Task task1("Finish Report", taskDate1, true, "Work in progress", Task::PENDING);

    std::tm taskDate2 = make_tm(2024, 6, 7);
    Task task2("Prepare Presentation", taskDate2, false, "Not started yet", Task::PENDING);

    calendar.addTask(task1);
    calendar.addTask(task2);

    std::ostringstream output;
    for(const auto& task : calendar.filterTasks(make_tm(2024, 6, 5), make_tm(2024, 6, 6))) {
        task.print();
    }
    std::string expectedOutput = "2024-06-05          Finish Report       Important           Pending             Work in progress\n";
    testing::internal::CaptureStdout();
    for(const auto& task : calendar.filterTasks(make_tm(2024, 6, 5), make_tm(2024, 6, 6))) {
        task.print();
    }
    std::string outputStr = testing::internal::GetCapturedStdout();
    ASSERT_EQ(outputStr, expectedOutput);
}
