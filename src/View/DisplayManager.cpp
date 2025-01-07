// DisplayManager.cpp
#include "DisplayManager.h"
#include <limits> // Include for std::numeric_limits
#include <iostream>
#ifdef _WIN32
#include <stdlib.h>
#else
#include <unistd.h>
#endif

using namespace std;

const string DisplayManager::divider = "=====================================================================================================================";
const string DisplayManager::inputYourChoiceHere = "Input your choice here: ";
const string DisplayManager::chooseAnOption = "Choose an option: ";
DisplayManager::DisplayManager() : ctl(new Controller), current_customer(NOT_SIGNED_IN_YET) {}

// <windows.h> got too many errors that I can't fix
// void DisplayManager::setColor(int color)
// {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleTextAttribute(hConsole, color);
// }

// void DisplayManager::printMsg(string msg)
// {
//     setColor(14);
//     cout << msg << endl;
//     setColor(7);
// }

void DisplayManager::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void DisplayManager::run()
{
    home();
}

int DisplayManager::getOption()
{
    int option;
    cout << "\nEnter your choice: ";
    // cin.ignore();
    cin >> option;
    return option;
}

string DisplayManager::getInput(const string &prompt)
{
    string input;
    cout << prompt;

    // Clear any leftover newline from previous input
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // if (cin.rdbuf()->in_avail() > 0)
    // {
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //     // cin.ignore(1000, '\n');
    // }

    // cin.ignore();
    // getline(cin, input);
    cin >> input;
    return input;
}

bool DisplayManager::isBackOption(const string &input)
{
    return input == "0";
}

bool DisplayManager::getUpdateChoice(const string &fieldName)
{
    cout << "Do you want to update " << fieldName << "? (Enter '1' for yes, '0' for no): ";
    string input;
    cin >> input;
    return input == "1";
}

void DisplayManager::home(string msg)
{
    current_customer = NOT_SIGNED_IN_YET;
    clearScreen();
    cout << divider << endl;
    cout << "                                PBL2: XÂY DỰNG CHƯƠNG TRÌNH ĐẶT VÉ XEM PHIM VÀ" << endl;
    cout << "                            QUẢN LÝ HỆ THỐNG HOẠT ĐỘNG KINH DOANH CỦA RẠP CHIẾU PHIM" << endl;
    cout << "                                GIẢNG VIÊN HƯỚNG DẪN: Thầy Nguyễn Năng Hùng Vân" << endl;
    cout << "                                    SINH VIÊN THỰC HIỆN: Trần Đinh Gia Khiêm" << endl;
    cout << "                                LỚP 20TCLC_NHAT1    NHÓM 2      MSSV: 102200308" << endl;
    cout << divider << endl;
    cout << chooseAnOption << endl;
    cout << "0. Sign in as an Admin\n";
    cout << "1. Sign in as a Customer\n";
    cout << "2. Sign up as a Customer\n";
    switch (getOption())
    {
    case 0:
        fillAdminSignIn();
        break;
    case 1:
        fillCustomerSignIn();
        break;
    case 2:
        fillCustomerSignUp();
        break;
    default:
        home();
        break;
    }
}

void DisplayManager::fillAdminSignIn(string msg)
{
    clearScreen();
    cout << "=== Admin Sign In ===\n";
    cout << msg << endl;
    cout << "Enter password (or '0' to return):\n";

    string inp = getInput("Password: ");
    if (isBackOption(inp))
        home();

    if (ctl->adminCheckPassword(inp) == SIGNED_IN_SUCCESSFULLY)
    {
        signedInAdmin();
    }
    else
    {
        fillAdminSignIn();
    }
}

void DisplayManager::fillCustomerSignIn(string msg)
{
    clearScreen();
    cout << "=== Customer Sign In ===\n";
    cout << msg << endl;
    cout << "Enter credentials (or '0' to return):\n";

    string username = getInput("Username: ");
    if (isBackOption(username))
        home();

    string password = getInput("Password: ");
    if (isBackOption(password))
        home();

    string response = ctl->customer_sign_in_request(username, password);
    if (response == SIGNED_IN_SUCCESSFULLY)
    {
        current_customer = username;
        signedInCustomer(response);
    }
    else
    {
        fillCustomerSignIn(response);
    }
}

void DisplayManager::fillCustomerSignUp(string msg)
{
    clearScreen();
    cout << "=== Customer Sign Up ===\n";
    cout << msg << endl;
    cout << "Enter your information (or '0' to return):\n";

    string username = getInput("Username: ");
    if (isBackOption(username))
        home();

    string password = getInput("Password: ");
    if (isBackOption(password))
        home();

    string name = getInput("Name: ");
    if (isBackOption(name))
        home();

    string response = ctl->customer_sign_up_request(username, password, name);
    if (response == SIGNED_UP_SUCCESSFULLY)
    {
        current_customer = username;
        signedInCustomer(response);
    }
    else
    {
        fillCustomerSignUp(response);
    }
}

void DisplayManager::signedInAdmin(string msg)
{
    clearScreen();
    cout << "=== Admin Menu ===\n";
    cout << msg << endl;
    cout << "0. Sign out\n";
    cout << "1. Manage Movie\n";
    cout << "2. Manage Showtime\n";

    switch (getOption())
    {
    case 0:
        home();
        break;
    case 1:
        manageMovie();
        break;
    case 2:
        manageShowtime();
        break;
    default:
        signedInAdmin();
        break;
    }
}

void DisplayManager::signedInCustomer(string msg)
{
    clearScreen();
    cout << "=== Customer Menu ===\n";
    cout << msg << endl;
    cout << "0. Sign out\n";
    cout << "1. View my info\n";
    cout << "2. Update my info\n";
    cout << "3. View my Tickets\n";
    cout << "4. Buy Ticket\n";

    switch (getOption())
    {
    case 0:
        home();
        break;
    case 1:
        viewMyInfo(ctl->viewMyInfo(current_customer));
        break;
    case 2:
        updateMyInfo();
        break;
    case 3:
        viewMyTicket(ctl->viewMyTicket(current_customer));
        break;
    case 4:
        buyTicket(ctl->viewAllMovie());
        break;
    default:
        signedInCustomer();
        break;
    }
}

void DisplayManager::manageMovie(string msg)
{
    clearScreen();
    cout << "=== Manage Movie ===\n";
    cout << msg << endl;
    cout << chooseAnOption << endl;
    cout << "0. Back\n";
    cout << "1. View all Movie\n";
    cout << "2. Add Movie\n";
    cout << "3. Update Movie\n";
    cout << "4. Remove Movie\n";

    switch (getOption())
    {
    case 0:
        signedInAdmin();
        break;
    case 1:
        viewAllMovie(ctl->viewAllMovie());
        break;
    case 2:
        addMovie(ctl->viewAllMovie());
        break;
    case 3:
        updateMovie(ctl->viewAllMovie());
        break;
    case 4:
        removeMovie(ctl->viewAllMovie());
        break;
    default:
        manageMovie();
        break;
    }
}

void DisplayManager::viewAllMovie(string msg)
{
    clearScreen();
    cout << "=== View All Movies ===\n";
    cout << msg << endl;
    cout << chooseAnOption << endl;
    cout << "0. Back\n";

    if (getOption() == 0)
        manageMovie();
    else
        viewAllMovie(ctl->viewAllMovie());
}

void DisplayManager::addMovie(string msg)
{
    clearScreen();
    cout << "=== Add Movie ===\n";
    cout << msg << endl;
    cout << "Enter movie details (or '0' to return):\n";

    string name;
    cout << "Movie name: ";
    cin.ignore();
    getline(cin, name);
    if (isBackOption(name))
        manageMovie();

    string duration = getInput("Duration (minutes): ");
    if (isBackOption(duration))
        manageMovie();

    string response = ctl->addMovie(name, duration);
    manageMovie(response);
}

void DisplayManager::updateMovie(string msg)
{
    clearScreen();
    cout << "=== Update Movie ===\n";
    cout << msg << endl;
    cout << "Enter movie details (or '0' to return):\n";

    string name = NO_CHANGE;
    int durationInt = -1;
    string durationStr = NO_CHANGE;
    string idMovie = getInput("Movie ID to update: ");
    if (isBackOption(idMovie))
        manageMovie();
    if (getUpdateChoice("name"))
    {
        cout << "New name: ";
        cin.ignore();
        getline(cin, name);
        if (isBackOption(name))
            manageMovie();
    }

    if (getUpdateChoice("duration"))
    {
        cout << "New duration (minutes): ";
        cin >> durationInt;
        durationStr = to_string(durationInt);
        if (isBackOption(durationStr))
            manageMovie();
    }

    string response = ctl->updateMovie(idMovie, name, durationStr);
    manageMovie(response);
}

void DisplayManager::removeMovie(string msg)
{
    clearScreen();
    cout << "=== Remove Movie ===\n";
    cout << msg << endl;
    cout << "Enter movie details (or '0' to return):\n";

    string idMovie = getInput("Movie ID to remove: ");
    if (isBackOption(idMovie))
        manageMovie();

    string response = ctl->removeMovie(idMovie);
    manageMovie(response);
}

void DisplayManager::manageShowtime(string msg)
{
    clearScreen();
    cout << "=== Manage Showtime ===\n";
    cout << msg << endl;
    cout << chooseAnOption << endl;
    cout << "0. Back\n";
    cout << "1. View all Showtime\n";
    cout << "2. Add Showtime\n";
    cout << "3. Update Showtime\n";
    cout << "4. Remove Showtime\n";

    switch (getOption())
    {
    case 0:
        signedInAdmin();
        break;
    case 1:
        viewAllShowtime(ctl->viewAllShowtime());
        break;
    case 2:
        addShowtime(ctl->viewAllMovie());
        break;
    case 3:
        updateShowtime(ctl->viewAllMovie());
        break;
    case 4:
        removeShowtime(ctl->viewAllMovie());
        break;
    default:
        manageShowtime();
        break;
    }
}

void DisplayManager::viewAllShowtime(string msg)
{
    // clearScreen();
    cout << "=== View All Showtimes ===\n";
    cout << msg << endl;
    cout << chooseAnOption << endl;
    cout << "0. Back\n";

    if (getOption() == 0)
        manageShowtime();
    else
        viewAllShowtime(ctl->viewAllShowtime());
}

void DisplayManager::addShowtime(string msg)
{
    clearScreen();
    cout << "=== Add Showtime ===\n";
    cout << msg << endl;
    cout << "Enter showtime details (or '0' to return):\n";

    string idMovie = getInput("Movie ID: ");
    if (isBackOption(idMovie))
        manageShowtime();

    string idRoom = getInput("Room ID: ");
    if (isBackOption(idRoom))
        manageShowtime();

    string onScreenDateTime = getInput("Date and time (DD/MM/YYYY-HH:MM): ");
    if (isBackOption(onScreenDateTime))
        manageShowtime();

    string response = ctl->addShowtime(idMovie, idRoom, onScreenDateTime);
    manageShowtime(response);
}

void DisplayManager::updateShowtime(string msg)
{
    clearScreen();
    cout << "=== Update Showtime ===\n";
    cout << msg << endl;
    cout << "Enter showtime details (or '0' to return):\n";

    string idMovie = NO_CHANGE;
    string idRoom = NO_CHANGE;
    string onScreenDateTime = NO_CHANGE;
    string idShowtime = getInput("Showtime ID to update: ");
    if (isBackOption(idShowtime))
        manageShowtime();

    if (getUpdateChoice("movie ID"))
    {
        idMovie = getInput("New movie ID: ");
        if (isBackOption(idMovie))
            manageShowtime();
    }

    if (getUpdateChoice("room ID"))
    {
        idRoom = getInput("New room ID: ");
        if (isBackOption(idRoom))
            manageShowtime();
    }

    if (getUpdateChoice("New Date and time: "))
    {
        onScreenDateTime = getInput("Date and time (DD/MM/YYYY-HH:MM): ");
        if (isBackOption(onScreenDateTime))
            manageShowtime();
    }

    string response = ctl->updateShowtime(idShowtime, idMovie, idRoom, onScreenDateTime);
    manageShowtime(response);
}

void DisplayManager::removeShowtime(string msg)
{
    clearScreen();
    cout << "=== Remove Showtime ===\n";
    cout << msg << endl;
    cout << "Enter showtime details (or '0' to return):\n";

    string idShowtime = getInput("Showtime ID to remove: ");
    if (isBackOption(idShowtime))
        manageShowtime();

    string response = ctl->removeShowtime(idShowtime);
    manageShowtime(response);
}

void DisplayManager::viewMyInfo(string msg)
{
    clearScreen();
    cout << "=== View My Info ===\n";
    cout << msg << endl;
    cout << chooseAnOption << endl;
    cout << "0. Back\n";
    cout << "1. Update my info\n";

    switch (getOption())
    {
    case 0:
        signedInCustomer();
        break;
    case 1:
        updateMyInfo();
        break;
    default:
        viewMyInfo(ctl->viewMyInfo(current_customer));
        break;
    }
}

void DisplayManager::updateMyInfo(string msg)
{
    clearScreen();
    cout << "=== Update My Info ===\n";
    cout << msg << endl;
    cout << "Update your information (or '0' to return):\n";

    string password = NO_CHANGE;
    string name = NO_CHANGE;
    if (getUpdateChoice("password"))
    {
        password = getInput("New password: ");
        if (isBackOption(password))
            manageShowtime();
    }

    if (getUpdateChoice("name"))
    {
        name = getInput("New name: ");
        if (isBackOption(name))
            manageShowtime();
    }

    string response = ctl->updateMyInfo(current_customer, password, name);
    signedInCustomer(response);
}

void DisplayManager::viewMyTicket(string msg)
{
    clearScreen();
    cout << "=== View My Tickets ===\n";
    cout << msg << endl;
    cout << chooseAnOption << endl;
    cout << "0. Back\n";
    cout << "1. Buy Ticket\n";

    switch (getOption())
    {
    case 0:
        signedInCustomer();
        break;
    case 1:
        buyTicket(ctl->viewAllMovie());
        break;
    default:
        viewMyTicket(ctl->viewMyTicket(current_customer));
        break;
    }
}

void DisplayManager::buyTicket(string msg)
{
    clearScreen();
    string backOption = "-1";
    cout << "=== Buy Ticket ===\n";
    cout << msg << endl;
    // cout << chooseAnOption << endl;
    // cout << "0. Back\n";
    // switch (getOption())
    // {
    // case 0:
    //     signedInCustomer();
    //     break;
    // default:
    //     viewMyTicket("FUNCTION IS IN DEVELOPMENT");
    //     break;
    // }
    // Show all movies first

    // Get movie selection
    cout << "Enter movie ID to view showtimes (or " << backOption << " to return): ";
    string idMovie;
    cin >> idMovie;

    if (idMovie == backOption)
        signedInCustomer();

    // Show showtimes for selected movie
    string displayShowtimes = ctl->viewDatetimeFor(idMovie);
    if (displayShowtimes == WRONG_ID || displayShowtimes == NO_SHOWTIMES_AVAILABLE_FOR_THIS_MOVIE)
    {
        signedInCustomer(displayShowtimes);
    }
    cout << displayShowtimes << endl;

    // Get showtime selection
    cout << "Enter showtime ID to view seat map (or " << backOption << " to return): ";
    string idShowtime;
    cin >> idShowtime;

    if (idShowtime == backOption)
        signedInCustomer();

    // Get seat selection
    cout << "Enter row (0-9) or " << backOption << " to cancel: ";
    int row;
    cin >> row;
    if (row == -1)
        signedInCustomer();

    cout << "Enter column (0-9) or " << backOption << " to cancel: ";
    int column;
    cin >> column;
    if (column == -1)
        signedInCustomer();

    string result = ctl->bookTicket(current_customer, idShowtime, to_string(row), to_string(column));
    signedInCustomer(result);
}