#include "Room.h"
#include <sstream>

Room::Room() : idRoom(""), name("") {}

Room::Room(const string &idRoom, const string &name) : idRoom(idRoom), name(name) {}

string Room::getIdRoom() const { return idRoom; }
void Room::setIdRoom(const string &value) { idRoom = value; }
string Room::getName() const { return name; }
void Room::setName(const string &value) { name = value; }

string Room::database() const
{
    ostringstream oss;
    oss << idRoom;
    oss << "|" << name;
    return oss.str();
}

bool Room::isMatch(string keyword)
{
    return idRoom == keyword;
}

bool Room::operator==(const Room &other) const
{
    return idRoom == other.idRoom;
}

bool Room::operator<(const Room &other) const
{
    return idRoom < other.idRoom;
}

bool Room::operator<=(const Room &other) const
{
    return *this < other || *this == other;
}

bool Room::operator>(const Room &other) const
{
    return !(*this <= other);
}

bool Room::operator>=(const Room &other) const
{
    return !(*this < other);
}

bool Room::operator!=(const Room &other) const
{
    return !(*this == other);
}

ostream &operator<<(ostream &os, const Room &obj)
{
    os << "Room {";
    os << " idRoom: " << obj.idRoom << ",";
    os << " name: " << obj.name << ",";
    os << "}";
    return os;
}

istream &operator>>(istream &is, Room &obj)
{
    string line;
    if (getline(is, line))
    {
        istringstream iss(line);
        string token;
        getline(iss, token, '|');
        obj.idRoom = token;
        getline(iss, token, '|');
        obj.name = token;
    }
    return is;
}
