#ifndef DB_HELPER_H
#define DB_HELPER_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class DB_Helper
{
protected:
    string file_path;

public:
    DB_Helper(const string &path);

    virtual ~DB_Helper() = default;

    virtual void extract_all_lines() = 0;

    void delete_line(size_t index);

    void update_line(size_t index, const string &new_line);

    void insert_line(size_t index, const string &new_line);

    void append(const string &new_line);

    int find_line_starting_with(const string &prefix);
};

#endif // DB_HELPER_H