#include "Account.h"
#include <sstream>

Account::Account() : username(""), password(""), name("") {}

Account::Account(const string &username, const string &password, const string &name) : username(username), password(password), name(name) {}

string Account::getUsername() const { return username; }
void Account::setUsername(const string &value) { username = value; }
string Account::getPassword() const { return password; }
void Account::setPassword(const string &value) { password = value; }
string Account::getName() const { return name; }
void Account::setName(const string &value) { name = value; }

string Account::database() const
{
    ostringstream oss;
    oss << username;
    oss << "|" << password;
    oss << "|" << name;
    return oss.str();
}

bool Account::isMatch(string keyword)
{
    return username == keyword;
}

bool Account::operator==(const Account &other) const
{
    return username == other.username;
}

bool Account::operator<(const Account &other) const
{
    return username < other.username;
}

bool Account::operator<=(const Account &other) const
{
    return *this < other || *this == other;
}

bool Account::operator>(const Account &other) const
{
    return !(*this <= other);
}

bool Account::operator>=(const Account &other) const
{
    return !(*this < other);
}

bool Account::operator!=(const Account &other) const
{
    return !(*this == other);
}

ostream &operator<<(ostream &os, const Account &obj)
{
    os << "Account {";
    os << " username: " << obj.username << ",";
    os << " password: " << obj.password << ",";
    os << " name: " << obj.name << ",";
    os << "}";
    return os;
}

istream &operator>>(istream &is, Account &obj)
{
    string line;
    if (getline(is, line))
    {
        istringstream iss(line);
        string token;
        getline(iss, token, '|');
        obj.username = token;
        getline(iss, token, '|');
        obj.password = token;
        getline(iss, token, '|');
        obj.name = token;
    }
    return is;
}
