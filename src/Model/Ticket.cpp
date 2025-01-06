#include "Ticket.h"
#include <sstream>

Ticket::Ticket() : idTicket(""), idShowTime(""), idSeat(""), idAccount(""), orderDateTime("") {}

Ticket::Ticket(const string &idTicket, const string &idShowTime, const string &idSeat, const string &idAccount, const string &orderDateTime) : idTicket(idTicket), idShowTime(idShowTime), idSeat(idSeat), idAccount(idAccount), orderDateTime(orderDateTime) {}

string Ticket::getIdTicket() const { return idTicket; }
void Ticket::setIdTicket(const string &value) { idTicket = value; }
string Ticket::getIdShowTime() const { return idShowTime; }
void Ticket::setIdShowTime(const string &value) { idShowTime = value; }
string Ticket::getIdSeat() const { return idSeat; }
void Ticket::setIdSeat(const string &value) { idSeat = value; }
string Ticket::getIdAccount() const { return idAccount; }
void Ticket::setIdAccount(const string &value) { idAccount = value; }
string Ticket::getOrderDateTime() const { return orderDateTime; }
void Ticket::setOrderDateTime(const string &value) { orderDateTime = value; }

string Ticket::database() const
{
    ostringstream oss;
    oss << idTicket;
    oss << "|" << idShowTime;
    oss << "|" << idSeat;
    oss << "|" << idAccount;
    oss << "|" << orderDateTime;
    return oss.str();
}

bool Ticket::isMatch(string keyword)
{
    return idTicket == keyword;
}

bool Ticket::operator==(const Ticket &other) const
{
    return idTicket == other.idTicket;
}

bool Ticket::operator<(const Ticket &other) const
{
    return idTicket < other.idTicket;
}

bool Ticket::operator<=(const Ticket &other) const
{
    return *this < other || *this == other;
}

bool Ticket::operator>(const Ticket &other) const
{
    return !(*this <= other);
}

bool Ticket::operator>=(const Ticket &other) const
{
    return !(*this < other);
}

bool Ticket::operator!=(const Ticket &other) const
{
    return !(*this == other);
}

ostream &operator<<(ostream &os, const Ticket &obj)
{
    os << "Ticket {";
    os << " idTicket: " << obj.idTicket << ",";
    os << " idShowTime: " << obj.idShowTime << ",";
    os << " idSeat: " << obj.idSeat << ",";
    os << " idAccount: " << obj.idAccount << ",";
    os << " orderDateTime: " << obj.orderDateTime;
    os << "}";
    return os;
}

istream &operator>>(istream &is, Ticket &obj)
{
    string line;
    if (getline(is, line))
    {
        istringstream iss(line);
        string token;
        getline(iss, token, '|');
        obj.idTicket = token;
        getline(iss, token, '|');
        obj.idShowTime = token;
        getline(iss, token, '|');
        obj.idSeat = token;
        getline(iss, token, '|');
        obj.idAccount = token;
        getline(iss, token, '|');
        obj.orderDateTime = token;
    }
    return is;
}
