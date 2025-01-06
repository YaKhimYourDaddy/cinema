#ifndef ACCOUNT_MANAGEMENT_H
#define ACCOUNT_MANAGEMENT_H

#include "DB_Helper.h"
#include "LinkedList.h"
#include "../Model/Account.h"
#include "../Model/Ticket.h"
#include "Ticket_Management.h"

class Ticket_Management;
class Account_Management : public DB_Helper
{
public:
    LinkedList<Account> accounts;

    Account_Management(const string &file_path);
    void extract_all_lines() override;
    void add(const Account &account);
    void update(const Account &account);
    void remove(const string &id);
    Account *find_by_username(string id);
    void add(string username, string password, string name);
    Account *getByUsername(string id);

    // Relationship 1 Account - many Ticket
    vector<Ticket *> getTickets(Ticket_Management *src, Account *acc);
};

#endif // ACCOUNT_MANAGEMENT_H
