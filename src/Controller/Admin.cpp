#include "Admin.h"
#include <fstream>
#include <iostream>
using namespace std;
#include <sstream>

#include <unistd.h>
#include <limits.h>

Admin::Admin()
{
    setPasswordFromFile();
}

void Admin::setPasswordFromFile()
{
    // Relative path to Admin.txt in the Database directory
    string filePath = "../src/Database/Admin.txt";

    // Open the file
    ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file at " << filePath << std::endl;
        return;
    }

    // Read the first line from the file
    string firstLine;
    if (getline(file, firstLine))
    {
        cout << password;
        password = firstLine; // Set the password to the first line
    }
    else
    {
        std::cerr << "Error: File is empty or could not read the first line" << std::endl;
    }

    file.close();
}

string Admin::getPassword()
{
    return password;
}
