#include "DateUtility.h"
#include <sstream>
#include <iostream>


bool DateUtility::isValidDate(const std::string& date) {
    int day, month, year;
    return parseDate(date, day, month, year);
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
