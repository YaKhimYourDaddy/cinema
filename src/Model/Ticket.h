#ifndef TICKET_H
#define TICKET_H

#include <iostream>
using namespace std;
#include "Comparable.h"

class Ticket : public Comparable
{
private:
    string idTicket;
    string idShowTime;
    string idSeat;
    string idAccount;
    string orderDateTime;

public:
    Ticket();
    Ticket(const string &idTicket, const string &idShowTime, const string &idSeat, const string &idAccount, const string &orderDateTime);

    // Getters and setters
    string getIdTicket() const;
    void setIdTicket(const string &idTicket);
    string getIdShowTime() const;
    void setIdShowTime(const string &idShowTime);
    string getIdSeat() const;
    void setIdSeat(const string &idSeat);
    string getIdAccount() const;
    void setIdAccount(const string &idAccount);
    string getOrderDateTime() const;
    void setOrderDateTime(const string &orderDateTime);

    // Database string representation
    string database() const;

    // Comparable implementation
    bool isMatch(string keyword) override;

    // Operator overloads
    bool operator==(const Ticket &other) const;
    bool operator<(const Ticket &other) const;
    bool operator<=(const Ticket &other) const;
    bool operator>(const Ticket &other) const;
    bool operator>=(const Ticket &other) const;
    bool operator!=(const Ticket &other) const;

    friend ostream &operator<<(ostream &os, const Ticket &ticket);
    friend istream &operator>>(istream &is, Ticket &ticket);
};

#endif // TICKET_H
