#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
using namespace std;
#include "Comparable.h"

class Account : public Comparable
{
private:
    string username;
    string password;
    string name;

public:
    Account();
    Account(const string &username, const string &password, const string &name);

    // Getters and setters
    string getUsername() const;
    void setUsername(const string &username);
    string getPassword() const;
    void setPassword(const string &password);
    string getName() const;
    void setName(const string &name);

    // Database string representation
    string database() const;

    // Comparable implementation
    bool isMatch(string keyword) override;

    // Operator overloads
    bool operator==(const Account &other) const;
    bool operator<(const Account &other) const;
    bool operator<=(const Account &other) const;
    bool operator>(const Account &other) const;
    bool operator>=(const Account &other) const;
    bool operator!=(const Account &other) const;

    friend ostream &operator<<(ostream &os, const Account &account);
    friend istream &operator>>(istream &is, Account &account);
};

#endif // ACCOUNT_H
