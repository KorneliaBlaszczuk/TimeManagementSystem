#include "functions.h"

std::time_t tm_to_time_t(const std::tm &t)
{
    std::tm temp = t;
    return mktime(&temp);
}

std::tm getCurrentDate()
{
    std::time_t t = std::time(nullptr);
    std::tm currentTime = *std::localtime(&t);
    currentTime.tm_hour = 0;
    currentTime.tm_min = 0;
    currentTime.tm_sec = 0;
    return currentTime;
}

// Function to get start and end date of the current week
void getCurrentWeekRange(std::tm &weekStart, std::tm &weekEnd)
{
    std::tm today = getCurrentDate();
    int wday = today.tm_wday; // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    if (wday == 0)
        wday = 7; // Adjust Sunday to be the 7th day of the week

    weekStart = today;
    weekStart.tm_mday -= (wday - 1);
    mktime(&weekStart);

    weekEnd = weekStart;
    weekEnd.tm_mday += 6;
    mktime(&weekEnd);
}

// Function to get start and end date of the current month
void getCurrentMonthRange(std::tm &monthStart, std::tm &monthEnd)
{
    std::tm today = getCurrentDate();

    monthStart = today;
    monthStart.tm_mday = 1;
    mktime(&monthStart);

    monthEnd = today;
    monthEnd.tm_mon += 1;
    monthEnd.tm_mday = 0;
    mktime(&monthEnd);
}

std::tm make_tm(int year, int month, int day, int hour, int minute)
{
    std::tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = 0;
    return t;
};

bool isOlderThanAMonth(const std::tm& date)
{
    // Current time
    std::time_t t_now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&t_now);

    // Convert the input date to time_t
    std::time_t t_date = std::mktime(const_cast<std::tm*>(&date));

    double seconds_diff = std::difftime(t_now, t_date);

    // Calculate the number of seconds in a month (assuming 30 days in a month)
    const double seconds_in_a_month = 30 * 24 * 60 * 60;

    return seconds_diff > seconds_in_a_month;
}