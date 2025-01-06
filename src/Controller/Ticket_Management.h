#ifndef TICKET_MANAGEMENT_H
#define TICKET_MANAGEMENT_H

#include "DB_Helper.h"
#include "LinkedList.h"
#include "../Model/Ticket.h"
#include "Showtime_Management.h"
#include "Seat_Management.h"
#include "Account_Management.h"

class Showtime_Management;
class Account_Management;
class Showtime_Management;
class Ticket_Management : public DB_Helper
{
public:
    LinkedList<Ticket> tickets;

    Ticket_Management(const string &file_path);
    void extract_all_lines() override;
    void add(const Ticket &ticket);
    void update(const Ticket &ticket);
    void remove(const string &id);
    string nextId(string current_highest);
    void add(string idShowtime, string idSeat, string username, string orderDatetime);

    // Relationship 1 Account - many Ticket
    Account *getAccount(Account_Management *src, Ticket *tic);

    // Relationship 1 Showtime - many Ticket
    Showtime *getShowtime(Showtime_Management *src, Ticket *tic);

    // Relationship 1 Seat - many Ticket
    Seat *getSeat(Seat_Management *src, Ticket *tic);
};

#endif // TICKET_MANAGEMENT_H
