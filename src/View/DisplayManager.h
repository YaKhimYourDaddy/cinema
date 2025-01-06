// DisplayManager.h
#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <iostream>
using namespace std;
#include "../Controller/Controller.h"

class DisplayManager
{
public:
    static const string divider;
    static const string chooseAnOption;
    static const string inputYourChoiceHere;
    DisplayManager();
    void home(string msg = "");
    void fillAdminSignIn(string msg = "");
    void fillCustomerSignIn(string msg = "");
    void fillCustomerSignUp(string msg = "");
    void signedInAdmin(string msg = "");
    void signedInCustomer(string msg = "");
    void manageMovie(string msg = "");
    void viewAllMovie(string msg = "");
    void addMovie(string msg = "");
    void updateMovie(string msg = "");
    void removeMovie(string msg = "");
    void manageShowtime(string msg = "");
    void viewAllShowtime(string msg = "");
    void addShowtime(string msg = "");
    void updateShowtime(string msg = "");
    void removeShowtime(string msg = "");
    void viewMyInfo(string msg = "");
    void updateMyInfo(string msg = "");
    void viewMyTicket(string msg = "");
    void buyTicket(string msg = "");
    bool isBackOption(const string &input);
    string getInput(const string &prompt);
    bool getUpdateChoice(const string &fieldName);
    // void setColor(int color);
    // void printMsg(string msg);
    void run();

private:
    Controller *ctl;
    string current_customer;
    void clearScreen();
    int getOption();
};

#endif // DISPLAY_MANAGER_H