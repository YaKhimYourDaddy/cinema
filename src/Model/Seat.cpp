#include "Seat.h"
#include <sstream>

Seat::Seat() : idSeat(""), column(""), row(""), idRoom("") {}

Seat::Seat(const string &idSeat, const string &column, const string &row, const string &idRoom) : idSeat(idSeat), column(column), row(row), idRoom(idRoom) {}

string Seat::getIdSeat() const { return idSeat; }
void Seat::setIdSeat(const string &value) { idSeat = value; }
string Seat::getColumn() const { return column; }
void Seat::setColumn(const string &value) { column = value; }
string Seat::getRow() const { return row; }
void Seat::setRow(const string &value) { row = value; }
string Seat::getIdRoom() const { return idRoom; }
void Seat::setIdRoom(const string &value) { idRoom = value; }

string Seat::database() const
{
    ostringstream oss;
    oss << idSeat;
    oss << "|" << idRoom;
    oss << "|" << column;
    oss << "|" << row;
    return oss.str();
}

bool Seat::isMatch(string keyword)
{
    return idSeat == keyword;
}

bool Seat::operator==(const Seat &other) const
{
    return idSeat == other.idSeat;
}

bool Seat::operator<(const Seat &other) const
{
    return idSeat < other.idSeat;
}

bool Seat::operator<=(const Seat &other) const
{
    return *this < other || *this == other;
}

bool Seat::operator>(const Seat &other) const
{
    return !(*this <= other);
}

bool Seat::operator>=(const Seat &other) const
{
    return !(*this < other);
}

bool Seat::operator!=(const Seat &other) const
{
    return !(*this == other);
}

ostream &operator<<(ostream &os, const Seat &obj)
{
    os << "Seat {";
    os << " idSeat: " << obj.idSeat << ",";
    os << " idRoom: " << obj.idRoom << ",";
    os << " column: " << obj.column << ",";
    os << " row: " << obj.row;
    os << "}";
    return os;
}

istream &operator>>(istream &is, Seat &obj)
{
    string line;
    if (getline(is, line))
    {
        istringstream iss(line);
        string token;
        getline(iss, token, '|');
        obj.idSeat = token;
        getline(iss, token, '|');
        obj.idRoom = token;
        getline(iss, token, '|');
        obj.column = token;
        getline(iss, token);
        obj.row = token;
    }
    return is;
}
