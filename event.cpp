#include "event.h"
#include <iomanip>
#include <ctime>
#include <iostream>

void Event::print() const
{
    char startBuffer[20];
    char endBuffer[20];
    strftime(startBuffer, 20, "%Y-%m-%d %H:%M", &start);
    strftime(endBuffer, 20, "%Y-%m-%d %H:%M", &end);

    std::cout << std::left << std::setw(20) << name << std::setw(20) << startBuffer
              << std::setw(20) << endBuffer
              << std::setw(20) << location
              << "Attendees: ";
    for (const auto &attendee : attendees)
    {
        std::cout << attendee << " ";
    }
    std::cout << std::endl;
}

std::tm Event::getStart() const
{
    return start;
}

void Event::setStart(const std::tm &newDate)
{
    start = newDate;
}

std::tm Event::getEnd() const
{
    return end;
}

void Event::setEnd(const std::tm &newDate)
{
    end = newDate;
}

std::string Event::getLocation() const
{
    return location;
}

void Event::setLocation(const std::string &newLoc)
{
    if (newLoc != "")
        location = newLoc;
}

std::vector<std::string> Event::getAttendees() const
{
    return attendees;
}

void Event::setAttendees(const std::vector<std::string> &newAttendees)
{
    attendees = newAttendees;
}