#include "Account_Management.h"
#include <fstream>
#include <iostream>
#include <sstream>

Account_Management::Account_Management(const string &file_path) : DB_Helper(file_path)
{
    extract_all_lines();
}

void Account_Management::extract_all_lines()
{
    accounts.clear();
    ifstream file(file_path);
    string line;
    getline(file, line); // skip headers

    while (getline(file, line))
    {
        istringstream iss(line);
        Account obj;
        iss >> obj;
        accounts.push_back(obj);
    }
}

void Account_Management::add(const Account &obj)
{
    accounts.push_back(obj);
    append(obj.database());
}

void Account_Management::add(string username, string password, string name)
{
    Account *obj = new Account(username, password, name);
    add(*obj);
}

void Account_Management::update(const Account &obj)
{
    int index = find_line_starting_with(obj.getUsername());
    if (index != -1)
    {
        update_line(index, obj.database());
        extract_all_lines();
    }
}

void Account_Management::remove(const string &id)
{
    Account temp;
    temp.setUsername(id);
    if (accounts.remove(temp))
    {
        int index = find_line_starting_with(id);
        if (index != -1)
        {
            delete_line(index);
        }
    }
}

Account *Account_Management::find_by_username(string id)
{
    for (auto it = accounts.begin(); it != accounts.end(); ++it)
    {
        if ((*it).getUsername() == id)
        {
            return &(*it);
        }
    }
    return nullptr;
}

vector<Ticket *> Account_Management::getTickets(Ticket_Management *src, Account *acc)
{
    vector<Ticket *> result;

    // Validate input parameters
    if (!src || acc->getUsername().empty())
    {
        return result;
    }

    // Get all tickets from the Tikcet_Management system
    const vector<Ticket *> &all = src->tickets.toVector();

    // Filter ticket for the specific account
    for (Ticket *tic : all)
    {
        if (tic && tic->getIdAccount() == acc->getUsername())
        {
            result.push_back(tic);
        }
    }

    return result;
}

Account *Account_Management::getByUsername(string id)
{
    return accounts.find(id);
}
