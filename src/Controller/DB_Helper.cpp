#include "DB_Helper.h"
DB_Helper::DB_Helper(const string &path) : file_path(path) {}
// void DB_Helper::delete_line(size_t index) {
//     vector<string> lines;
//     string line;
//     ifstream file(file_path);
//     while (getline(file, line))
//     {
//         lines.push_back(line);
//     }
//     file.close();
//     if (index < lines.size() && index > 0)
//     {
//         lines.erase(lines.begin() + index);
//         ofstream outFile(file_path);
//         for (const auto &l : lines)
//         {
//             outFile << l << '\n';
//         }
//     }
// }
void DB_Helper::delete_line(size_t index)
{
    vector<string> lines;
    string line;
    ifstream file(file_path);

    // Đọc toàn bộ các dòng từ file
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    // Kiểm tra index hợp lệ và xóa dòng
    if (index < lines.size())
    {
        lines.erase(lines.begin() + index);

        // Ghi các dòng còn lại vào file
        ofstream outFile(file_path);
        for (size_t i = 0; i < lines.size(); ++i)
        {
            outFile << lines[i];
            if (i != lines.size() - 1)
            {
                outFile << '\n'; // Thêm newline nếu không phải dòng cuối
            }
        }
    }
}

void DB_Helper::update_line(size_t index, const string &new_line)
{
    vector<string> lines;
    string line;
    ifstream file(file_path);
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();
    if (index < lines.size() && index > 0)
    {
        lines[index] = new_line;
        ofstream outFile(file_path);
        for (const auto &l : lines)
        {
            outFile << l << '\n';
        }
    }
}

void DB_Helper::append(const string &new_line)
{
    // Open file for both reading and writing, move to end
    fstream file(file_path, ios::in | ios::out | ios::ate);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file for appending!" << endl;
        return;
    }
    // Check if the file is not empty and doesn't already end at the last line
    file.seekp(0, ios::end); // Move to the end of the file
    if (file.tellp() != 0)   // If file is not empty
    {
        file.seekg(-1, ios::end); // Move to the last character
        char last_char;
        file.get(last_char);   // Read the last character
        if (last_char != '\n') // If not ending with a newline, add one
        {
            file << '\n';
        }
    }
    file << new_line; // Append the new line
    file.close();     // Close the file
}

int DB_Helper::find_line_starting_with(const string &id)
{
    string line;
    ifstream file(file_path);
    int index = 0;
    while (getline(file, line))
    {
        if (line.substr(0, id.length()) == id && line.at(id.length()) == '|')
        {
            file.close();
            return index;
        }
        index++;
    }
    file.close();
    return -1;
}
void DB_Helper::insert_line(size_t index, const string &new_line)
{
    vector<string> lines;
    string line;
    ifstream file(file_path);

    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    if (index <= lines.size())
    {
        lines.insert(lines.begin() + index, new_line);

        ofstream outFile(file_path);
        for (const auto &l : lines)
        {
            outFile << l << '\n';
        }
    }
}
