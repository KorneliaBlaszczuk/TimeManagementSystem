#pragma once
#include "user.h"
#include <ctime>
#include <string>

// Helper function o create std::tm from year, month, day, hour, and minute
std::tm make_tm(int year, int month, int day, int hour = 0, int minute = 0);

// Helper function to convert std::tm to std::time_t
std::time_t tm_to_time_t(const std::tm &t);

// Function to get current date
std::tm getCurrentDate();

std::tm getDateFromUser();
std::string getNameFromUser();

// Function to get start and end date of the current week
void getCurrentWeekRange(std::tm &weekStart, std::tm &weekEnd);

// Function to get start and end date of the current month
void getCurrentMonthRange(std::tm &monthStart, std::tm &monthEnd);

bool isOlderThanAMonth(const std::tm& date);

bool compareTm(const std::tm &tm1, const std::tm &tm2);

void saveToFile(std::ofstream &outFile, User &user);
bool loadFromFile(std::ifstream &inFile, User& user);