#ifndef ROOM_MANAGEMENT_H
#define ROOM_MANAGEMENT_H

#include "DB_Helper.h"
#include "LinkedList.h"
#include "../Model/Room.h"
#include "Showtime_Management.h"
#include "Seat_Management.h"

class Seat_Management;
class Showtime_Management;
class Room_Management : public DB_Helper
{
public:
    LinkedList<Room> rooms;

    Room_Management(const string &file_path);
    void extract_all_lines() override;
    void add(const Room &room);
    void update(const Room &room);
    void remove(const string &id);
    // void view() const;
    Room *getByIdRoom(string id);

    // Relationship 1 Room - many Showtime
    vector<Showtime *> getAllShowtimes(Showtime_Management *src, Room *roo);

    // Relationship 1 Room - many Seat
    vector<Seat *> getAllSeats(Seat_Management *src, Room *roo);
};

#endif // ROOM_MANAGEMENT_H
