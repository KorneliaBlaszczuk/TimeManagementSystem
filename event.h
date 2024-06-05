#pragma once
#include "plan.h"
#include <vector>
#include <string>
#include <ctime>

// Event class
class Event : public Plan
{
    std::tm start;
    std::tm end;
    std::string location;
    std::vector<std::string> attendees;

public:
    Event(std::string const &name, std::tm const &start, std::tm const &end, std::string const &location, std::vector<std::string> const &attendees)
        : Plan(name, start), start(start), end(end), location(location), attendees(attendees) {}

    void print() const;

    std::tm getStart() const;
    void setStart(const std::tm &newDate);
    std::tm getEnd() const;
    void setEnd(const std::tm &newDate);
    std::string getLocation() const;
    void setLocation(const std::string &newLoc);
    std::vector<std::string> getAttendees() const;
    void setAttendees(const std::vector<std::string> &newAttendees);
};