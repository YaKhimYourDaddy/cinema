// Controller.cpp
#include "Controller.h"

#include <sstream>
#include <iomanip>
#include <ctime>
#include <map>

string Controller::viewDatetimeFor(string movieId)
{
    Movie *mov = movieManagement->find_by_id(movieId);
    if (mov == nullptr)
        return WRONG_ID;

    vector<Showtime *> showtimesOfMovie = movieManagement->getShowtimes(showtimeManagement, mov);
    if (showtimesOfMovie.empty())
        return "No showtimes available for this movie.";

    ostringstream oss;
    oss << "Showtimes for movie: " << mov->getName() << endl;
    oss << setw(10) << left << "idShowtime"
        << setw(20) << "Date-Time" << endl;

    for (Showtime *sho : showtimesOfMovie)
    {
        oss << setw(10) << sho->getIdShowtime()
            << setw(20) << sho->getOnScreenDateTime() << endl;
    }
    return oss.str();
}

string Controller::bookTicket(string username, string idShowtime, string row, string column)
{
    // Validate user
    Account *acc = accountManagement->find_by_username(username);
    if (acc == nullptr)
        return WRONG_USERNAME;

    // Validate showtime
    Showtime *sho = showtimeManagement->find_by_id(idShowtime);
    if (sho == nullptr)
        return WRONG_ID;

    // Get room for this showtime
    Room *room = showtimeManagement->getRoom(roomManagement, sho);
    if (room == nullptr)
        return "Invalid room.";

    // Find the specific seat in the room by row and column
    vector<Seat *> roomSeats = roomManagement->getAllSeats(seatManagement, room);
    Seat *selectedSeat = nullptr;
    for (Seat *seat : roomSeats)
    {
        if (seat->getRow() == row && seat->getColumn() == column)
        {
            selectedSeat = seat;
            break;
        }
    }
    if (selectedSeat == nullptr)
        return "Invalid seat selection.";

    // Check if seat is already booked for this showtime
    vector<Ticket *> existingTickets = showtimeManagement->getTickets(ticketManagement, sho);
    for (Ticket *ticket : existingTickets)
    {
        if (ticket->getIdSeat() == selectedSeat->getIdSeat())
        {
            return "Seat is already booked.";
        }
    }

    // Create new ticket with current datetime
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);
    int year = 1900 + localTime->tm_year; // tm_year is years since 1900
    int month = 1 + localTime->tm_mon;    // tm_mon is months since January (0-11)
    int day = localTime->tm_mday;
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    DateTime dateTimeOrder(day, month, year, hour, minute);
    string orderDateTime = dateTimeOrder.toString();
    ticketManagement->add(idShowtime, selectedSeat->getIdSeat(), username, orderDateTime);

    return "Ticket booked successfully!";
}

string Controller::viewSeatMapFor(string showtimeId)
{
    Showtime *sho = showtimeManagement->find_by_id(showtimeId);
    if (sho == nullptr)
        return WRONG_ID;

    Room *roo = showtimeManagement->getRoom(roomManagement, sho);
    if (roo == nullptr)
        return "Invalid room data.";

    // Get all seats for the room
    vector<Seat *> roomSeats = roomManagement->getAllSeats(seatManagement, roo);

    // Get all booked tickets for this showtime
    vector<Ticket *> bookedTickets = showtimeManagement->getTickets(ticketManagement, sho);

    ostringstream oss;
    oss << "Seat Map for Showtime: " << sho->getOnScreenDateTime()
        << " in Room: " << roo->getName() << endl;

    // Create a map of booked seats
    map<string, bool> isBooked;
    for (Ticket *ticket : bookedTickets)
    {
        isBooked[ticket->getIdSeat()] = true;
    }

    // Find dimensions of the room
    int maxRow = 10, maxCol = 10;

    // Display column headers
    oss << "   ";
    for (int c = 0; c < maxCol; ++c)
        oss << setw(3) << c;
    oss << endl;

    // Display seat map
    for (int r = 0; r < maxRow; ++r)
    {
        oss << setw(3) << r;
        for (int c = 0; c < maxCol; ++c)
        {
            bool seatExists = false;
            bool isSeatBooked = false;

            // Find if seat exists and is booked
            for (Seat *seat : roomSeats)
            {
                if (seat->getRow() == to_string(r) && seat->getColumn() == to_string(c))
                {
                    seatExists = true;
                    isSeatBooked = isBooked[seat->getIdSeat()];
                    break;
                }
            }

            if (!seatExists)
            {
                oss << setw(3) << " ";
            }
            else
            {
                oss << setw(3) << (isSeatBooked ? "X" : "O");
            }
        }
        oss << endl;
    }
    return oss.str();
}

string Controller::updateMyInfo(string username, string password, string name)
{
    Account *found = accountManagement->find_by_username(username);
    if (found == nullptr)
        return WRONG_ID;
    if (name == NO_CHANGE)
        name = found->getName();
    if (password == NO_CHANGE)
        password = found->getPassword();
    Account changed(username, password, name);
    accountManagement->update(changed);
    return CRUD_SUCCESSFULLY;
}

string Controller::viewMyTicket(string username)
{
    Account *acc = accountManagement->find_by_username(username);
    if (acc == nullptr)
        return WRONG_USERNAME;

    vector<Ticket *> myTickets = accountManagement->getTickets(ticketManagement, acc);

    ostringstream oss;
    oss << setw(50) << left << "Movie"
        << setw(10) << "Room"
        << setw(20) << "Date-time"
        << setw(5) << "Row"
        << setw(10) << "Column" << endl;

    for (Ticket *tic : myTickets)
    {
        Showtime *sho = ticketManagement->getShowtime(showtimeManagement, tic);
        Movie *mov = showtimeManagement->getMovie(movieManagement, sho);
        Room *roo = showtimeManagement->getRoom(roomManagement, sho);
        Seat *sea = ticketManagement->getSeat(seatManagement, tic);

        oss << setw(50) << left << mov->getName()
            << setw(10) << roo->getName()
            << setw(20) << sho->getOnScreenDateTime()
            << setw(5) << sea->getRow()
            << setw(10) << sea->getColumn() << endl;
    }
    return oss.str();
}

string Controller::viewMyInfo(string username)
{
    Account *found = accountManagement->find_by_username(username);
    if (found == nullptr)
        return WRONG_USERNAME;
    ostringstream oss;
    oss << setw(15) << left << "username: " << setw(20) << found->getUsername() << endl
        << setw(15) << "password: " << setw(20) << found->getPassword() << endl
        << setw(15) << "name" << setw(20) << found->getName() << endl;
    return oss.str();
}

string Controller::viewAllMovie()
{
    return movieManagement->viewAll();
}

string Controller::addMovie(string name, string duration)
{
    movieManagement->add(name, duration);
    return CRUD_SUCCESSFULLY;
}

string Controller::updateMovie(string idMovie, string name, string duration)
{
    Movie *found = movieManagement->find_by_id(idMovie);
    if (found == nullptr)
        return WRONG_ID;
    if (name == NO_CHANGE)
        name = found->getName();
    if (duration == NO_CHANGE)
        duration = found->getDuration();
    movieManagement->update(idMovie, name, duration);
    return CRUD_SUCCESSFULLY;
}

string Controller::removeMovie(string idMovie)
{
    Movie *mov = movieManagement->find_by_id(idMovie);
    if (mov == nullptr)
        return WRONG_ID;
    vector<Showtime *> allSho = movieManagement->getShowtimes(showtimeManagement, mov);
    for (Showtime *sho : allSho)
    {
        vector<Ticket *> allTic = showtimeManagement->getTickets(ticketManagement, sho);
        for (Ticket *tic : allTic)
        {
            ticketManagement->remove(tic->getIdTicket());
        }
        showtimeManagement->remove(sho->getIdShowtime());
    }
    movieManagement->remove(idMovie);
    return CRUD_SUCCESSFULLY;
}

string Controller::viewAllShowtime()
{
    return showtimeManagement->viewAll(*movieManagement, *roomManagement);
}

string Controller::addShowtime(string idMovie, string idRoom, string onScreenDateTime)
{
    showtimeManagement->add(idMovie, idRoom, onScreenDateTime);
    return CRUD_SUCCESSFULLY;
}

string Controller::updateShowtime(string idShowtime, string idMovie, string idRoom, string onScreenDateTime)
{
    Showtime *found = showtimeManagement->find_by_id(idShowtime);
    if (found == nullptr)
        return WRONG_ID;
    if (idMovie == NO_CHANGE)
        idMovie = found->getIdMovie();
    if (idRoom == NO_CHANGE)
        idRoom = found->getIdRoom();
    if (onScreenDateTime == NO_CHANGE)
        onScreenDateTime = found->getOnScreenDateTime();
    showtimeManagement->update(idShowtime, idMovie, idRoom, onScreenDateTime);
    return CRUD_SUCCESSFULLY;
}

string Controller::removeShowtime(string idShowtime)
{
    Showtime *sho = showtimeManagement->find_by_id(idShowtime);
    if (sho == nullptr)
        return WRONG_ID;
    vector<Ticket *> allTic = showtimeManagement->getTickets(ticketManagement, sho);
    for (Ticket *tic : allTic)
    {
        ticketManagement->remove(tic->getIdTicket());
    }
    showtimeManagement->remove(sho->getIdShowtime());
    return CRUD_SUCCESSFULLY;
}

Controller::Controller()
    : accountManagement(new Account_Management("../src/Database/Account.txt")),
      roomManagement(new Room_Management("../src/Database/Room.txt")),
      seatManagement(new Seat_Management("../src/Database/Seat.txt")),
      showtimeManagement(new Showtime_Management("../src/Database/Showtime.txt")),
      ticketManagement(new Ticket_Management("../src/Database/Ticket.txt")),
      movieManagement(new Movie_Management("../src/Database/Movie.txt")),
      admin(new Admin())
{
}

string Controller::adminCheckPassword(string input)
{
    return input == admin->getPassword() ? SIGNED_IN_SUCCESSFULLY : WRONG_PASSWORD;
}

string Controller::customer_sign_in_request(string username, string password)
{
    if (!isValidUsernameOrPassword(username))
        return INVALID_USERNAME;
    if (!isValidUsernameOrPassword(password))
        return INVALID_PASSWORD;

    Account *found_account = accountManagement->find_by_username(username);
    if (found_account == nullptr)
        return WRONG_USERNAME;
    if (found_account->getPassword() != password)
        return WRONG_PASSWORD;

    return SIGNED_IN_SUCCESSFULLY;
}

bool Controller::isValidUsernameOrPassword(string str)
{
    for (char c : str)
    { // Iterate through each character in the string
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
        {
            return false; // Return false if a whitespace character is found
        }
    }
    return true; // Return true if no whitespace is found
}

string Controller::customer_sign_up_request(string username, string password, string name)
{
    if (!isValidUsernameOrPassword(username))
        return INVALID_USERNAME;
    if (!isValidUsernameOrPassword(password))
        return INVALID_PASSWORD;
    if (name == "")
        return INVALID_CUSTOMER_NAME;

    Account *found_account = accountManagement->find_by_username(username);
    if (found_account != nullptr)
        return INPUT_USERNAME_IS_AREADY_EXISTED;

    accountManagement->add(username, password, name);
    return SIGNED_UP_SUCCESSFULLY;
}
