#ifndef ADMIN_H
#define ADMIN_H

#include <fstream>
#include <iostream>
using namespace std;
#include <sstream>

class Admin
{
private:
    string password;

public:
    Admin();
    void setPasswordFromFile();
    string getPassword();
};

#endif // ADMIN_H
