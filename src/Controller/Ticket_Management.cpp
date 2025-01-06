#include "Ticket_Management.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

Ticket_Management::Ticket_Management(const string &file_path) : DB_Helper(file_path)
{
    extract_all_lines();
}

void Ticket_Management::extract_all_lines()
{
    tickets.clear();
    ifstream file(file_path);
    string line;
    getline(file, line); // skip headers

    while (getline(file, line))
    {
        istringstream iss(line);
        Ticket obj;
        iss >> obj;
        tickets.push_back(obj);
    }
}

void Ticket_Management::add(const Ticket &obj)
{
    tickets.push_back(obj);
    append(obj.database());
}

void Ticket_Management::update(const Ticket &obj)
{
    int index = find_line_starting_with(obj.getIdTicket());
    if (index != -1)
    {
        update_line(index, obj.database());
        extract_all_lines();
    }
}

void Ticket_Management::remove(const string &id)
{
    Ticket temp;
    temp.setIdTicket(id);
    if (tickets.remove(temp))
    {
        int index = find_line_starting_with(id);
        if (index != -1)
        {
            delete_line(index);
        }
    }
}

Account *Ticket_Management::getAccount(Account_Management *src, Ticket *tic)
{
    return src->getByUsername(tic->getIdAccount());
}

Showtime *Ticket_Management::getShowtime(Showtime_Management *src, Ticket *tic)
{
    return src->getByIdShowtime(tic->getIdShowTime());
}

Seat *Ticket_Management::getSeat(Seat_Management *src, Ticket *tic)
{
    return src->getByIdSeat(tic->getIdSeat());
}

void Ticket_Management::add(string idShowtime, string idSeat, string username, string orderDatetime)
{
    Ticket *item = new Ticket(nextId(tickets.getLast()->getIdTicket()), idShowtime, idSeat, username, orderDatetime);
    add(*item);
}

string Ticket_Management::nextId(string current_highest)
{
    string prefix = current_highest.substr(0, 8);  // "idTicket"
    string number_str = current_highest.substr(8); // The number part (e.g., "00000000001")
    int number = stoi(number_str);
    number++;
    ostringstream oss;
    oss << prefix << setw(9) << setfill('0') << number;
    return oss.str();
}
