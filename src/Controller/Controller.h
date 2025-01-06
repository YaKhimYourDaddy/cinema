// Controller.h
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
using namespace std;

#include "Messages.cpp"
#include "Admin.h"
#include "Account_Management.h"
#include "Movie_Management.h"
#include "Room_Management.h"
#include "Seat_Management.h"
#include "Showtime_Management.h"
#include "Ticket_Management.h"
#include "../src/Model/DateTime.h"

class Controller
{
private:
    Account_Management *accountManagement;
    Room_Management *roomManagement;
    Seat_Management *seatManagement;
    Showtime_Management *showtimeManagement;
    Ticket_Management *ticketManagement;
    Movie_Management *movieManagement;
    Admin *admin;

public:
    Controller();
    bool isValidUsernameOrPassword(string str);
    string adminCheckPassword(string input);
    string customer_sign_in_request(string username, string password);
    string customer_sign_up_request(string username, string password, string name = "");

    string viewAllMovie();
    string addMovie(string name, string duration);
    string updateMovie(string idMovie, string name, string duration);
    string removeMovie(string idMovie);

    string viewAllShowtime();
    string addShowtime(string idMovie, string idRoom, string onScreenDateTime);
    string updateShowtime(string idShowtime, string idMovie, string idRoom, string onScreenDateTime);
    string removeShowtime(string idShowtime);

    string viewMyInfo(string username);
    string viewMyTicket(string username);
    string updateMyInfo(string username, string password, string name);

    string viewDatetimeFor(string idMovie);
    string viewSeatMapFor(string idShowtime);
    string bookTicket(string username, string idShowtime, string row, string col);
};

#endif // CONTROLLER_H
