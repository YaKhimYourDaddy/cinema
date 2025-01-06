#include "Movie_Management.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

void Movie_Management::add(string name, string duration)
{
    Movie *item = new Movie(nextId(movies.getLast()->getIdMovie()), name, duration);
    add(*item);
}

void Movie_Management::update(string idMovie, string name, string duration)
{
    Movie item(idMovie, name, duration);
    update(item);
}

Movie_Management::Movie_Management(const string &file_path) : DB_Helper(file_path)
{
    extract_all_lines();
}

void Movie_Management::extract_all_lines()
{
    movies.clear();
    ifstream file(file_path);
    string line;
    getline(file, line); // skip headers
    while (getline(file, line))
    {
        istringstream iss(line);
        Movie obj;
        iss >> obj;
        movies.push_back(obj);
    }
}

Movie *Movie_Management::find_by_id(string id)
{
    for (auto it = movies.begin(); it != movies.end(); ++it)
    {
        if ((*it).getIdMovie() == id)
        {
            return &(*it);
        }
    }
    return nullptr;
}

void Movie_Management::add(const Movie &obj)
{
    movies.push_back(obj);
    append(obj.database());
}

void Movie_Management::update(const Movie &obj)
{
    int index = find_line_starting_with(obj.getIdMovie());
    if (index != -1)
    {
        update_line(index, obj.database());
        extract_all_lines();
    }
}

void Movie_Management::remove(const string &id)
{
    Movie temp;
    temp.setIdMovie(id);
    if (movies.remove(temp))
    {
        int index = find_line_starting_with(id);
        if (index != -1)
        {
            delete_line(index);
        }
    }
}

string Movie_Management::nextId(string current_highest)
{
    string prefix = current_highest.substr(0, 7);  // "idMovie"
    string number_str = current_highest.substr(7); // The number part (e.g., "00001")
    int number = stoi(number_str);
    number++;
    ostringstream oss;
    oss << prefix << setw(4) << setfill('0') << number;
    return oss.str();
}

Movie *Movie_Management::getByIdMovie(string id)
{
    return movies.find(id);
}

vector<Showtime *> Movie_Management::getShowtimes(Showtime_Management *src, Movie *mov)
{
    vector<Showtime *> result;

    // Validate input parameters
    if (!src || mov->getIdMovie().empty())
    {
        return result;
    }

    // Get all orders from the Order_Management system
    const vector<Showtime *> &allShowtimes = src->showtimes.toVector();

    // Filter orders for the specific account
    for (Showtime *showtime : allShowtimes)
    {
        if (showtime && showtime->getIdMovie() == mov->getIdMovie())
        {
            result.push_back(showtime);
        }
    }

    return result;
}

string Movie_Management::viewAll()
{
    ostringstream oss;
    oss << setw(12) << left << "idMovie"
        << setw(30) << "name"
        << setw(9) << "duration" << endl;
    vector<Movie *> all = movies.toVector();
    for (Movie *mov : all)
    {
        oss << setw(12) << left << mov->getIdMovie()
            << setw(30) << mov->getName()
            << setw(9) << mov->getDuration() << endl;
    }
    return oss.str();
}
