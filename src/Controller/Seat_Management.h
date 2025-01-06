#ifndef SEAT_MANAGEMENT_H
#define SEAT_MANAGEMENT_H

#include "DB_Helper.h"
#include "LinkedList.h"
#include "../Model/Seat.h"
#include "Ticket_Management.h"
#include "Room_Management.h"

class Room_Management;
class Ticket_Management;
class Seat_Management : public DB_Helper
{
public:
    LinkedList<Seat> seats;

    Seat_Management(const string &file_path);
    void extract_all_lines() override;
    void add(const Seat &seat);
    void update(const Seat &seat);
    void remove(const string &id);
    // void view() const;
    Seat *getByIdSeat(string id);

    // Relationship 1 Seat - many Ticket
    vector<Ticket *> getAllTickets(Ticket_Management *src, Seat *sea);

    // Relationship many Seat - 1 Room
    Room *getRoom(Room_Management *src, Seat *sea);
};

#endif // SEAT_MANAGEMENT_H
