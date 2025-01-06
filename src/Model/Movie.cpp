#include "Movie.h"
#include <sstream>

Movie::Movie() : idMovie(""), name(""), duration("") {}

Movie::Movie(const string &idMovie, const string &name, const string &duration) : idMovie(idMovie), name(name), duration(duration) {}

string Movie::getIdMovie() const { return idMovie; }
void Movie::setIdMovie(const string &value) { idMovie = value; }
string Movie::getName() const { return name; }
void Movie::setName(const string &value) { name = value; }
string Movie::getDuration() const { return duration; }
void Movie::setDuration(const string &value) { duration = value; }

string Movie::database() const
{
    ostringstream oss;
    oss << idMovie;
    oss << "|" << name;
    oss << "|" << duration;
    return oss.str();
}

bool Movie::isMatch(string keyword)
{
    return idMovie == keyword;
}

bool Movie::operator==(const Movie &other) const
{
    return idMovie == other.idMovie;
}

bool Movie::operator<(const Movie &other) const
{
    return idMovie < other.idMovie;
}

bool Movie::operator<=(const Movie &other) const
{
    return *this < other || *this == other;
}

bool Movie::operator>(const Movie &other) const
{
    return !(*this <= other);
}

bool Movie::operator>=(const Movie &other) const
{
    return !(*this < other);
}

bool Movie::operator!=(const Movie &other) const
{
    return !(*this == other);
}

ostream &operator<<(ostream &os, const Movie &obj)
{
    os << "Movie {";
    os << " idMovie: " << obj.idMovie << ",";
    os << " name: " << obj.name << ",";
    os << " duration: " << obj.duration << ",";
    os << "}";
    return os;
}

istream &operator>>(istream &is, Movie &obj)
{
    string line;
    if (getline(is, line))
    {
        istringstream iss(line);
        string token;
        getline(iss, token, '|');
        obj.idMovie = token;
        getline(iss, token, '|');
        obj.name = token;
        getline(iss, token, '|');
        obj.duration = token;
    }
    return is;
}
