#include "Showtime_Management.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

bool Showtime_Management::isValid(Movie_Management *mm, string idMovie, string idRoom, string onSreenDateTime)
{
    // vector<Showtime *> conflict;
    vector<Showtime *> allSho = showtimes.toVector();
    Movie *addingMov = mm->getByIdMovie(idMovie);
    if (addingMov == nullptr)
        return false;
    int addingDuration = stoi(addingMov->getDuration());
    DateTime adding;
    if (adding.setDateTime(onSreenDateTime) == false)
        return false;
    for (Showtime *sho : allSho)
    {
        Movie *mov = getMovie(mm, sho);
        int addedDuration = stoi(mov->getDuration());
        DateTime added;
        if (added.setDateTime(sho->getOnScreenDateTime()) == false)
            continue;
        if (sho->getIdRoom() != idRoom)
            continue;
        if (added.isInMiddle(adding, addingDuration) || adding.isInMiddle(added, addedDuration))
        {
            return false;
        }
    }
    return true;
}

Showtime *Showtime_Management::find_by_id(string id)
{
    for (auto it = showtimes.begin(); it != showtimes.end(); ++it)
    {
        if ((*it).getIdShowtime() == id)
        {
            return &(*it);
        }
    }
    return nullptr;
}

string Showtime_Management::nextId(string current_highest)
{
    string prefix = current_highest.substr(0, 10);  // "idShowtime"
    string number_str = current_highest.substr(10); // The number part (e.g., "0000001")
    int number = stoi(number_str);
    number++;
    ostringstream oss;
    oss << prefix << setw(7) << setfill('0') << number;
    return oss.str();
}

void Showtime_Management::add(string idMovie, string idRoom, string onScreenDateTime)
{
    Showtime *item = new Showtime(nextId(showtimes.getLast()->getIdShowtime()), idMovie, idRoom, onScreenDateTime);
    add(*item);
}

void Showtime_Management::update(string idShowtime, string idMovie, string idRoom, string onScreenDateTime)
{
    Showtime item(idShowtime, idMovie, idRoom, onScreenDateTime);
    update(item);
}

Showtime_Management::Showtime_Management(const string &file_path) : DB_Helper(file_path)
{
    extract_all_lines();
}

string Showtime_Management::viewAll(Movie_Management &mm, Room_Management &rm)
{
    ostringstream oss;
    oss << setw(20) << left << "idShowtime" << "|"
        << setw(12) << "idMovie" << setw(30) << "Movie" << setw(9) << "duration" << "|"
        << setw(10) << "idRoom" << setw(8) << "Room"
        << setw(20) << "onScreenDateTime" << endl;
    vector<Showtime *> all = showtimes.toVector();
    for (Showtime *sho : all)
    {
        Movie *mov = getMovie(&mm, sho);
        Room *roo = getRoom(&rm, sho);
        oss << setw(20) << left << sho->getIdShowtime() << "|"
            << setw(12) << mov->getIdMovie() << setw(30) << mov->getName() << setw(9) << mov->getDuration() << "|"
            << setw(10) << roo->getIdRoom() << setw(8) << roo->getName() << "|"
            << setw(20) << sho->getOnScreenDateTime() << endl;
    }
    return oss.str();
}

void Showtime_Management::extract_all_lines()
{
    showtimes.clear();
    ifstream file(file_path);
    string line;
    getline(file, line); // skip headers

    while (getline(file, line))
    {
        istringstream iss(line);
        Showtime obj;
        iss >> obj;
        showtimes.push_back(obj);
    }
}

void Showtime_Management::add(const Showtime &obj)
{
    showtimes.push_back(obj);
    append(obj.database());
}

void Showtime_Management::update(const Showtime &obj)
{
    int index = find_line_starting_with(obj.getIdShowtime());
    if (index != -1)
    {
        update_line(index, obj.database());
        extract_all_lines();
    }
}

void Showtime_Management::remove(const string &id)
{
    Showtime temp;
    temp.setIdShowtime(id);
    if (showtimes.remove(temp))
    {
        int index = find_line_starting_with(id);
        if (index != -1)
        {
            delete_line(index);
        }
    }
}

Showtime *Showtime_Management::getByIdShowtime(string id)
{
    return showtimes.find(id);
}

vector<Ticket *> Showtime_Management::getTickets(Ticket_Management *src, Showtime *sho)
{
    vector<Ticket *> result;

    // Validate input parameters
    if (!src || sho->getIdShowtime().empty())
    {
        return result;
    }

    // Get all orders from the Order_Management system
    const vector<Ticket *> &allTickets = src->tickets.toVector();

    // Filter orders for the specific account
    for (Ticket *ticket : allTickets)
    {
        if (ticket && ticket->getIdShowTime() == sho->getIdShowtime())
        {
            result.push_back(ticket);
        }
    }

    return result;
}

Movie *Showtime_Management::getMovie(Movie_Management *src, Showtime *sho)
{
    return src->getByIdMovie(sho->getIdMovie());
}

Room *Showtime_Management::getRoom(Room_Management *src, Showtime *sho)
{
    return src->getByIdRoom(sho->getIdRoom());
}
