#include "Seat_Management.h"
#include <fstream>
#include <iostream>
#include <sstream>

Seat_Management::Seat_Management(const string &file_path) : DB_Helper(file_path)
{
    extract_all_lines();
}

void Seat_Management::extract_all_lines()
{
    seats.clear();
    ifstream file(file_path);
    string line;
    getline(file, line); // skip headers

    while (getline(file, line))
    {
        istringstream iss(line);
        Seat obj;
        iss >> obj;
        seats.push_back(obj);
    }
}

void Seat_Management::add(const Seat &obj)
{
    seats.push_back(obj);
    ofstream file(file_path, ios::app);
    file << obj.database() << '\n';
}

void Seat_Management::update(const Seat &obj)
{
    int index = find_line_starting_with(obj.getIdSeat());
    if (index != -1)
    {
        update_line(index, obj.database());
        extract_all_lines();
    }
}

void Seat_Management::remove(const string &id)
{
    Seat temp;
    temp.setIdSeat(id);
    if (seats.remove(temp))
    {
        int index = find_line_starting_with(id);
        if (index != -1)
        {
            delete_line(index);
        }
    }
}

Seat *Seat_Management::getByIdSeat(string id)
{
    return seats.find(id);
}

vector<Ticket *> Seat_Management::getAllTickets(Ticket_Management *src, Seat *sea)
{
    vector<Ticket *> result;

    // Validate input parameters
    if (!src || sea->getIdSeat().empty())
    {
        return result;
    }

    // Get all orders from the Order_Management system
    const vector<Ticket *> &allTickets = src->tickets.toVector();

    // Filter orders for the specific account
    for (Ticket *ticket : allTickets)
    {
        if (ticket && ticket->getIdSeat() == sea->getIdSeat())
        {
            result.push_back(ticket);
        }
    }

    return result;
}

Room *Seat_Management::getRoom(Room_Management *src, Seat *sea)
{
    return src->getByIdRoom(sea->getIdRoom());
}
