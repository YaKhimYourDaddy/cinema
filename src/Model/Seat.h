#ifndef SEAT_H
#define SEAT_H

#include <iostream>
using namespace std;
#include "Comparable.h"

class Seat : public Comparable {
private:
    string idSeat;
    string column;
    string row;
    string idRoom;

public:
    Seat();
    Seat(const string& idSeat, const string& column, const string& row, const string& idRoom);
    
    // Getters and setters
    string getIdSeat() const;
    void setIdSeat(const string& idSeat);
    string getColumn() const;
    void setColumn(const string& column);
    string getRow() const;
    void setRow(const string& row);
    string getIdRoom() const;
    void setIdRoom(const string& idRoom);
    
    // Database string representation
    string database() const;
    
    // Comparable implementation
    bool isMatch(string keyword) override;
    
    // Operator overloads
    bool operator==(const Seat& other) const;
    bool operator<(const Seat& other) const;
    bool operator<=(const Seat& other) const;
    bool operator>(const Seat& other) const;
    bool operator>=(const Seat& other) const;
    bool operator!=(const Seat& other) const;
    
    friend ostream& operator<<(ostream& os, const Seat& seat);
    friend istream& operator>>(istream& is, Seat& seat);
};

#endif // SEAT_H
