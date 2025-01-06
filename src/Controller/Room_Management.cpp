#include "Room_Management.h"
#include <fstream>
#include <iostream>
#include <sstream>

Room_Management::Room_Management(const string &file_path) : DB_Helper(file_path)
{
    extract_all_lines();
}

void Room_Management::extract_all_lines()
{
    rooms.clear();
    ifstream file(file_path);
    string line;
    getline(file, line); // skip headers

    while (getline(file, line))
    {
        istringstream iss(line);
        Room obj;
        iss >> obj;
        rooms.push_back(obj);
    }
}

void Room_Management::add(const Room &obj)
{
    rooms.push_back(obj);
    ofstream file(file_path, ios::app);
    file << obj.database() << '\n';
}

void Room_Management::update(const Room &obj)
{
    int index = find_line_starting_with(obj.getIdRoom());
    if (index != -1)
    {
        update_line(index, obj.database());
        extract_all_lines();
    }
}

void Room_Management::remove(const string &id)
{
    Room temp;
    temp.setIdRoom(id);
    if (rooms.remove(temp))
    {
        int index = find_line_starting_with(id);
        if (index != -1)
        {
            delete_line(index);
        }
    }
}

/* void Room_Management::view() const {
    for (const auto& obj : rooms) {
        cout << obj << '\n';
    }
} */

Room *Room_Management::getByIdRoom(string id)
{
    return rooms.find(id);
}

vector<Showtime *> Room_Management::getAllShowtimes(Showtime_Management *src, Room *roo)
{
    vector<Showtime *> result;

    // Validate input parameters
    if (!src || roo->getIdRoom().empty())
    {
        return result;
    }

    // Get all orders from the Order_Management system
    const vector<Showtime *> &allShowtimes = src->showtimes.toVector();

    // Filter orders for the specific account
    for (Showtime *showtime : allShowtimes)
    {
        if (showtime && showtime->getIdRoom() == roo->getIdRoom())
        {
            result.push_back(showtime);
        }
    }

    return result;
}

vector<Seat *> Room_Management::getAllSeats(Seat_Management *src, Room *roo)
{
    vector<Seat *> result;

    // Validate input parameters
    if (!src || roo->getIdRoom().empty())
    {
        return result;
    }

    // Get all orders from the Order_Management system
    const vector<Seat *> &allSeats = src->seats.toVector();

    // Filter orders for the specific account
    for (Seat *seat : allSeats)
    {
        if (seat && seat->getIdRoom() == roo->getIdRoom())
        {
            result.push_back(seat);
        }
    }

    return result;
}
