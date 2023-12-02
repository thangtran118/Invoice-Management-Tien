#include "DateUtility.h"
#include <sstream>
#include <iostream>
#include <chrono>



bool DateUtility::isValidDate(const std::string& date) {
    int day, month, year;
    if (!parseDate(date, day, month, year)) {
        return false;
    }

    // Get the current date
    auto now = std::chrono::system_clock::now();
    std::time_t t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now = *std::localtime(&t_now);

    // Check if the entered date is greater than the current date
    if (year > (tm_now.tm_year + 1900) || 
        (year == (tm_now.tm_year + 1900) && month > (tm_now.tm_mon + 1)) || 
        (year == (tm_now.tm_year + 1900) && month == (tm_now.tm_mon + 1) && day > tm_now.tm_mday)) {
        return false;
    }

    return true;
}

int DateUtility::compareDates(const std::string& date1, const std::string& date2) {
    int day1, month1, year1;
    int day2, month2, year2;

    if (!parseDate(date1, day1, month1, year1) || !parseDate(date2, day2, month2, year2)) {
        std::cerr << "Invalid date format.\n";
        return 0;
    }

    if (year1 < year2 || (year1 == year2 && (month1 < month2 || (month1 == month2 && day1 < day2)))) {
        return -1; // date1 is earlier
    } else if (year1 == year2 && month1 == month2 && day1 == day2) {
        return 0; // dates are equal
    } else {
        return 1; // date1 is later
    }
}

bool DateUtility::parseDate(const std::string& date, int& day, int& month, int& year) {
    char delim1, delim2;
    std::istringstream dateStream(date);
    dateStream >> day >> delim1 >> month >> delim2 >> year;

    if (dateStream.fail() || delim1 != '/' || delim2 != '/') {
        return false;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12) {
        return false;
    }

    return true;
}
