#ifndef SHOWTIME_MANAGEMENT_H
#define SHOWTIME_MANAGEMENT_H

#include "DB_Helper.h"
#include "LinkedList.h"
#include "../Model/Showtime.h"
#include "Ticket_Management.h"
#include "Movie_Management.h"
#include "Room_Management.h"
#include "../Model/DateTime.h"

class Ticket_Management;
class Movie_Management;
class Room_Management;
class Showtime_Management : public DB_Helper
{
public:
    LinkedList<Showtime> showtimes;
    bool isValid(Movie_Management *mm, string idMovie, string idRoom, string onSreenDateTime);

    Showtime_Management(const string &file_path);
    void extract_all_lines() override;
    void add(const Showtime &showtime);
    void update(const Showtime &showtime);
    void remove(const string &id);
    string viewAll(Movie_Management &mm, Room_Management &rm);
    Showtime *getByIdShowtime(string id);

    Showtime *find_by_id(string id);
    string nextId(string current_highest);
    void add(string idMovie, string idRoom, string onScreenDateTime);
    void update(string idShowtime, string idMovie, string idRoom, string onScreenDateTime);

    // Relationship 1 Showtime - many Ticket
    vector<Ticket *> getTickets(Ticket_Management *src, Showtime *sho);

    // Relationship many Showtime - 1 Movie
    Movie *getMovie(Movie_Management *src, Showtime *sho);

    // Relationship many Showtime - 1 Room
    Room *getRoom(Room_Management *src, Showtime *sho);
};

#endif // SHOWTIME_MANAGEMENT_H
