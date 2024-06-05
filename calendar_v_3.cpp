#include "calendar_v_3.h"

// Helper function to create std::tm from year, month, day, hour, and minute
std::tm make_tm(int year, int month, int day, int hour = 0, int minute = 0) {
    std::tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = 0;
    return t;
}

// Helper function to convert std::tm to std::time_t
std::time_t tm_to_time_t(const std::tm& t) {
    std::tm temp = t;
    return mktime(&temp);
}

// Function to get current date
std::tm getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm currentTime = *std::localtime(&t);
    currentTime.tm_hour = 0;
    currentTime.tm_min = 0;
    currentTime.tm_sec = 0;
    return currentTime;
}

std::string Plan::getName() const
{
    return name;
}

std::tm Plan::getDate() const
{
    return date;
}

void Plan::setName(const std::string& newName)
{
    if (newName != "")
    name = newName;
}

void Plan::setDate(const std::tm& newDate)
{
    date = newDate;
}

void Event::print() const
{
    char startBuffer[20];
    char endBuffer[20];
    strftime(startBuffer, 20, "%Y-%m-%d %H:%M", &start);
    strftime(endBuffer, 20, "%Y-%m-%d %H:%M", &end);

    std::cout << std::left << std::setw(20) << name<<std::setw(20)<<startBuffer
                << std::setw(20) << endBuffer
                << std::setw(20) << location
                << "Attendees: ";
    for (const auto& attendee : attendees) {
        std::cout << attendee << " ";
    }
    std::cout << std::endl;
}

std::tm Event::getStart() const
{
    return start;
}
void Event::setStart(const std::tm& newDate)
{
    start = newDate;
}
std::tm Event::getEnd() const
{
    return end;
}
void Event::setEnd(const std::tm& newDate)
{
    end = newDate;
}
std::string Event::getLocation() const
{
    return location;
}
void Event::setLocation(const std::string& newLoc)
{
    if (newLoc != "")
    location = newLoc;
}
std::vector<std::string> Event::getAttendees() const
{
    return attendees;
}
void Event::setAttendees(const std::vector<std::string>& newAttendees)
{
    attendees = newAttendees;
}
