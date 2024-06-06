#include "event.h"
#include <iomanip>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

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

void Event::saveToFile(std::ofstream &outFile) const
{
    outFile << "Event Name: " << name << "\n";
    outFile << "Start Date: " << std::put_time(&start, "%Y-%m-%d %H:%M") << "\n";
    outFile << "End Date: " << std::put_time(&end, "%Y-%m-%d %H:%M") << "\n";
    outFile << "Location: " << location << "\n";
    outFile << "Attendees: ";
    for (const auto &attendee : attendees)
    {
        outFile << attendee << ",";
    }
    outFile << "\n";
}

bool Event::loadFromFile(std::ifstream &inFile, Event &event)
{
    std::string line;
    if (!std::getline(inFile, line) || !startsWith(line, "Event Name:"))
    {
        return false;
    }

    std::string name, startDateStr, endDateStr, location, attendeesStr;
    std::vector<std::string> attendees;

    name = line.substr(11);
    std::getline(inFile, line);
    startDateStr = line.substr(12);
    std::getline(inFile, line);
    endDateStr = line.substr(10);
    std::getline(inFile, line);
    location = line.substr(10);

    int startYear, startMonth, startDay, startHour, startMinute;
    std::sscanf(startDateStr.c_str(), "%d-%d-%d %d:%d", &startYear, &startMonth, &startDay, &startHour, &startMinute);
    std::tm startDate = make_tm(startYear, startMonth, startDay, startHour, startMinute);

    // Parse end date
    int endYear, endMonth, endDay, endHour, endMinute;
    std::sscanf(endDateStr.c_str(), "%d-%d-%d %d:%d", &endYear, &endMonth, &endDay, &endHour, &endMinute);
    std::tm endDate = make_tm(endYear, endMonth, endDay, endHour, endMinute);

    std::getline(inFile, line);
    attendeesStr = line.substr(11);
    if (attendeesStr.empty())
    {
        event = Event(name, startDate, endDate, location, attendees);
        return true;
    }
    std::cout << attendeesStr;
    std::stringstream attendeesStream(attendeesStr);
    std::string attendee;
    while (attendeesStream.good())
    {
        std::string substr;
        getline(attendeesStream, substr, ',');
        attendees.push_back(substr);
    }

    event = Event(name, startDate, endDate, location, attendees);
    return true;
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