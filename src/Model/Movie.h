#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
using namespace std;
#include "Comparable.h"

class Movie : public Comparable
{
private:
    string idMovie;
    string name;
    string duration;

public:
    Movie();
    Movie(const string &idMovie, const string &name, const string &duration);

    // Getters and setters
    string getIdMovie() const;
    void setIdMovie(const string &idMovie);
    string getName() const;
    void setName(const string &name);
    string getDuration() const;
    void setDuration(const string &duration);

    // Database string representation
    string database() const;

    // Comparable implementation
    bool isMatch(string keyword) override;

    // Operator overloads
    bool operator==(const Movie &other) const;
    bool operator<(const Movie &other) const;
    bool operator<=(const Movie &other) const;
    bool operator>(const Movie &other) const;
    bool operator>=(const Movie &other) const;
    bool operator!=(const Movie &other) const;

    friend ostream &operator<<(ostream &os, const Movie &movie);
    friend istream &operator>>(istream &is, Movie &movie);
};

#endif // MOVIE_H
