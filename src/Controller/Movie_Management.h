#ifndef MOVIE_MANAGEMENT_H
#define MOVIE_MANAGEMENT_H

#include "DB_Helper.h"
#include "LinkedList.h"
#include "../Model/Movie.h"
#include "Showtime_Management.h"
class Showtime_Management;
class Movie_Management : public DB_Helper
{
public:
    LinkedList<Movie> movies;
    Movie_Management(const string &file_path);
    void extract_all_lines() override;
    void add(const Movie &movie);
    void update(const Movie &movie);
    void remove(const string &id);
    string viewAll();
    Movie *find_by_id(string id);
    Movie *getByIdMovie(string id);
    string nextId(string current_highest);

    void add(string name, string duration);
    void update(string idMovie, string name, string duration);

    // Relationship 1 Movie - many Showtime
    vector<Showtime *> getShowtimes(Showtime_Management *src, Movie *mov);
};

#endif // MOVIE_MANAGEMENT_H
