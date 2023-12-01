#ifndef DATE_UTILITY_H
#define DATE_UTILITY_H

#include <string>

/**
 * @class DateUtility
 * @brief Provides utilities for handling and validating dates in DD/MM/YYYY format.
 */
class DateUtility {
public:
    /**
     * @brief Checks if a given date string is in the correct DD/MM/YYYY format and not in the future.
     *
     * @param date The date string to validate, expected in DD/MM/YYYY format.
     * @return true if the date is in the correct format and not in the future, false otherwise.
     */
    static bool isValidDate(const std::string& date);

    /**
     * @brief Compares two dates.
     * 
     * @param date1 The first date string to compare.
     * @param date2 The second date string to compare.
     * @return int Returns -1 if date1 is earlier, 1 if date1 is later, and 0 if equal.
     */
    static int compareDates(const std::string& date1, const std::string& date2);

private:
    /**
     * @brief Parses a date string into day, month, and year integers.
     * 
     * @param date The date string to parse.
     * @param day Output parameter for the day.
     * @param month Output parameter for the month.
     * @param year Output parameter for the year.
     * @return true if the date is successfully parsed, false otherwise.
     */
    static bool parseDate(const std::string& date, int& day, int& month, int& year);
};

#endif // DATE_UTILITY_H
