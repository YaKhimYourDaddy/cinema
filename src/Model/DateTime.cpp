#include "DateTime.h"
#include <iomanip>
#include <stdexcept>

// Helper methods
bool DateTime::isValidDate(int d, int m, int y) const
{
    if (y < 0 || m < 1 || m > 12 || d < 1 || d > daysInMonth(m, y))
    {
        return false;
    }
    return true;
}

bool DateTime::isLeapYear(int year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DateTime::daysInMonth(int m, int y) const
{
    static const int daysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeapYear(y))
    {
        return 29;
    }
    return daysInMonths[m - 1];
}

// Constructors
DateTime::DateTime() : day(1), month(1), year(2000), hour(0), minute(0) {}

DateTime::DateTime(int d, int m, int y, int h, int min)
{
    if (!isValidDate(d, m, y) || h < 0 || h >= 24 || min < 0 || min >= 60)
    {
        throw invalid_argument("Invalid DateTime values");
    }
    day = d;
    month = m;
    year = y;
    hour = h;
    minute = min;
}

bool DateTime::setDateTime(string s)
{
    // Check format length
    if (s.length() != 16)
    {
        return false;
    }

    // Extract parts of the string
    try
    {
        int d = stoi(s.substr(0, 2));    // Day
        int m = stoi(s.substr(3, 2));    // Month
        int y = stoi(s.substr(6, 4));    // Year
        int h = stoi(s.substr(11, 2));   // Hour
        int min = stoi(s.substr(14, 2)); // Minute

        // Check separators
        if (s[2] != '/' || s[5] != '/' || s[10] != '-' || s[13] != ':')
        {
            return false;
        }

        // Validate date and time values
        if (!isValidDate(d, m, y) || h < 0 || h >= 24 || min < 0 || min >= 60)
        {
            return false;
        }

        // Set the values
        day = d;
        month = m;
        year = y;
        hour = h;
        minute = min;

        return true;
    }
    catch (const exception &)
    {
        return false;
    }
}

// Getters
int DateTime::getDay() const { return day; }
int DateTime::getMonth() const { return month; }
int DateTime::getYear() const { return year; }
int DateTime::getHour() const { return hour; }
int DateTime::getMinute() const { return minute; }

// Setters
void DateTime::setDateTime(int d, int m, int y, int h, int min)
{
    if (!isValidDate(d, m, y) || h < 0 || h >= 24 || min < 0 || min >= 60)
    {
        throw invalid_argument("Invalid DateTime values");
    }
    day = d;
    month = m;
    year = y;
    hour = h;
    minute = min;
}

// Operator overloads
ostream &operator<<(ostream &os, const DateTime &dt)
{
    os << setw(2) << setfill('0') << dt.day << "/"
       << setw(2) << setfill('0') << dt.month << "/"
       << dt.year << "-"
       << setw(2) << setfill('0') << dt.hour << ":"
       << setw(2) << setfill('0') << dt.minute;
    return os;
}

istream &operator>>(istream &is, DateTime &dt)
{
    char slash1, slash2, dash, colon;
    int d, m, y, h, min;
    is >> d >> slash1 >> m >> slash2 >> y >> dash >> h >> colon >> min;
    if (!dt.isValidDate(d, m, y) || h < 0 || h >= 24 || min < 0 || min >= 60)
    {
        throw invalid_argument("Invalid DateTime format");
    }
    dt.day = d;
    dt.month = m;
    dt.year = y;
    dt.hour = h;
    dt.minute = min;
    return is;
}

DateTime &DateTime::operator=(const DateTime &dt)
{
    if (this != &dt)
    {
        day = dt.day;
        month = dt.month;
        year = dt.year;
        hour = dt.hour;
        minute = dt.minute;
    }
    return *this;
}

// Comparison operators
bool DateTime::operator==(const DateTime &dt) const
{
    return day == dt.day && month == dt.month && year == dt.year &&
           hour == dt.hour && minute == dt.minute;
}

bool DateTime::operator!=(const DateTime &dt) const
{
    return !(*this == dt);
}

bool DateTime::operator<(const DateTime &dt) const
{
    if (year != dt.year)
        return year < dt.year;
    if (month != dt.month)
        return month < dt.month;
    if (day != dt.day)
        return day < dt.day;
    if (hour != dt.hour)
        return hour < dt.hour;
    return minute < dt.minute;
}

bool DateTime::operator<=(const DateTime &dt) const { return *this < dt || *this == dt; }
bool DateTime::operator>(const DateTime &dt) const { return !(*this <= dt); }
bool DateTime::operator>=(const DateTime &dt) const { return !(*this < dt); }

// // Arithmetic operators
// DateTime DateTime::operator+(int minutes) const
// {
//     DateTime result = *this;
//     result.minute += minutes;
//     result.normalizeDateTime();
//     return result;
// }

// DateTime DateTime::operator-(int minutes) const
// {
//     DateTime result = *this;
//     result.minute -= minutes;
//     result.normalizeDateTime();
//     return result;
// }

bool DateTime::isInMiddle(const DateTime &start, int duration)
{
    DateTime end(start.day, start.month, start.year, start.hour, start.minute);
    end.minute += duration;
    end.normalizeDateTime();
    return (*this > start) && (*this < end);
}

// Normalize DateTime
void DateTime::normalizeDateTime()
{
    hour += minute / 60;
    minute %= 60;
    if (minute < 0)
    {
        minute += 60;
        hour--;
    }

    day += hour / 24;
    hour %= 24;
    if (hour < 0)
    {
        hour += 24;
        day--;
    }

    while (day > daysInMonth(month, year))
    {
        day -= daysInMonth(month, year);
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }

    while (day <= 0)
    {
        month--;
        if (month <= 0)
        {
            month = 12;
            year--;
        }
        day += daysInMonth(month, year);
    }
}

string DateTime::toString()
{
    ostringstream oss;
    oss << setw(2) << setfill('0') << day << "/"
        << setw(2) << setfill('0') << month << "/"
        << year << "-"
        << setw(2) << setfill('0') << hour << ":"
        << setw(2) << setfill('0') << minute;
    return oss.str();
}