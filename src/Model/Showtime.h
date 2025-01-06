#ifndef SHOWTIME_H
#define SHOWTIME_H

#include <iostream>
using namespace std;
#include "Comparable.h"

class Showtime : public Comparable {
private:
    string idShowtime;
    string idMovie;
    string idRoom;
    string onScreenDateTime;

public:
    Showtime();
    Showtime(const string& idShowtime, const string& idMovie, const string& idRoom, const string& onScreenDateTime);
    
    // Getters and setters
    string getIdShowtime() const;
    void setIdShowtime(const string& idShowtime);
    string getIdMovie() const;
    void setIdMovie(const string& idMovie);
    string getIdRoom() const;
    void setIdRoom(const string& idRoom);
    string getOnScreenDateTime() const;
    void setOnScreenDateTime(const string& onScreenDateTime);
    
    // Database string representation
    string database() const;
    
    // Comparable implementation
    bool isMatch(string keyword) override;
    
    // Operator overloads
    bool operator==(const Showtime& other) const;
    bool operator<(const Showtime& other) const;
    bool operator<=(const Showtime& other) const;
    bool operator>(const Showtime& other) const;
    bool operator>=(const Showtime& other) const;
    bool operator!=(const Showtime& other) const;
    
    friend ostream& operator<<(ostream& os, const Showtime& showtime);
    friend istream& operator>>(istream& is, Showtime& showtime);
};

#endif // SHOWTIME_H
