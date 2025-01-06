#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
using namespace std;

class DateTime
{
private:
    int day, month, year, hour, minute;

    bool isValidDate(int d, int m, int y) const;
    bool isLeapYear(int year) const;
    int daysInMonth(int m, int y) const;

public:
    DateTime();
    DateTime(int d, int m, int y, int h = 0, int min = 0);

    // Getters and setters
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getHour() const;
    int getMinute() const;

    bool setDateTime(string s);
    void setDateTime(int d, int m, int y, int h, int min);

    // Operator overloads
    friend ostream &operator<<(ostream &os, const DateTime &dt);
    friend istream &operator>>(istream &is, DateTime &dt);

    DateTime &operator=(const DateTime &dt);

    bool operator==(const DateTime &dt) const;
    bool operator!=(const DateTime &dt) const;
    bool operator<(const DateTime &dt) const;
    bool operator<=(const DateTime &dt) const;
    bool operator>(const DateTime &dt) const;
    bool operator>=(const DateTime &dt) const;

    // DateTime operator+(int minutes) const;
    // DateTime operator-(int minutes) const;
    bool isInMiddle(const DateTime &start, int duration);

    void normalizeDateTime();
    string toString();
};

#endif // DATETIME_H
