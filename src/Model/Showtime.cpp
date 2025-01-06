#include "Showtime.h"
#include <sstream>

Showtime::Showtime() : idShowtime(""), idMovie(""), idRoom(""), onScreenDateTime("") {}

Showtime::Showtime(const string &idShowtime, const string &idMovie, const string &idRoom, const string &onScreenDateTime) : idShowtime(idShowtime), idMovie(idMovie), idRoom(idRoom), onScreenDateTime(onScreenDateTime) {}

string Showtime::getIdShowtime() const { return idShowtime; }
void Showtime::setIdShowtime(const string &value) { idShowtime = value; }
string Showtime::getIdMovie() const { return idMovie; }
void Showtime::setIdMovie(const string &value) { idMovie = value; }
string Showtime::getIdRoom() const { return idRoom; }
void Showtime::setIdRoom(const string &value) { idRoom = value; }
string Showtime::getOnScreenDateTime() const { return onScreenDateTime; }
void Showtime::setOnScreenDateTime(const string &value) { onScreenDateTime = value; }

string Showtime::database() const
{
    ostringstream oss;
    oss << idShowtime;
    oss << "|" << idMovie;
    oss << "|" << idRoom;
    oss << "|" << onScreenDateTime;
    return oss.str();
}

bool Showtime::isMatch(string keyword)
{
    return idShowtime == keyword;
}

bool Showtime::operator==(const Showtime &other) const
{
    return idShowtime == other.idShowtime;
}

bool Showtime::operator<(const Showtime &other) const
{
    return idShowtime < other.idShowtime;
}

bool Showtime::operator<=(const Showtime &other) const
{
    return *this < other || *this == other;
}

bool Showtime::operator>(const Showtime &other) const
{
    return !(*this <= other);
}

bool Showtime::operator>=(const Showtime &other) const
{
    return !(*this < other);
}

bool Showtime::operator!=(const Showtime &other) const
{
    return !(*this == other);
}

ostream &operator<<(ostream &os, const Showtime &obj)
{
    os << "Showtime {";
    os << " idShowtime: " << obj.idShowtime << ",";
    os << " idMovie: " << obj.idMovie << ",";
    os << " idRoom: " << obj.idRoom << ",";
    os << " onScreenDateTime: " << obj.onScreenDateTime << ",";
    os << "}";
    return os;
}

istream &operator>>(istream &is, Showtime &obj)
{
    string line;
    if (getline(is, line))
    {
        istringstream iss(line);
        string token;
        getline(iss, token, '|');
        obj.idShowtime = token;
        getline(iss, token, '|');
        obj.idMovie = token;
        getline(iss, token, '|');
        obj.idRoom = token;
        getline(iss, token, '|');
        obj.onScreenDateTime = token;
    }
    return is;
}
