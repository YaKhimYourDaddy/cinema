#ifndef ROOM_H
#define ROOM_H

#include <iostream>
using namespace std;
#include "Comparable.h"

class Room : public Comparable
{
private:
    string idRoom;
    string name;

public:
    Room();
    Room(const string &idRoom, const string &name);

    // Getters and setters
    string getIdRoom() const;
    void setIdRoom(const string &idRoom);
    string getName() const;
    void setName(const string &name);

    // Database string representation
    string database() const;

    // Comparable implementation
    bool isMatch(string keyword) override;

    // Operator overloads
    bool operator==(const Room &other) const;
    bool operator<(const Room &other) const;
    bool operator<=(const Room &other) const;
    bool operator>(const Room &other) const;
    bool operator>=(const Room &other) const;
    bool operator!=(const Room &other) const;

    friend ostream &operator<<(ostream &os, const Room &room);
    friend istream &operator>>(istream &is, Room &room);
};

#endif // ROOM_H
