#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

bool recognize_command_line_parameters(const int &argc, char **argv, bool &is_table, bool &is_max_value, unsigned int &max_value, bool &is_level_value, unsigned int &level_value)
{
    for (short i = 1; (i < argc); i++)
    {
        std::string argi = argv[i];
        if (argi == "-max")
        {
            i++;
            if (i >= argc) return false;
            const int parameter_value = std::stoi(argv[i]);
            if (parameter_value <= 0) return false;
            max_value = parameter_value;
            is_max_value = true;
        }
        if (argi == "-level")
        {
            i++;
            if (i >= argc) return false;
            level_value = std::stoi(argv[i]);
            if (level_value < 1 && level_value >> 3) return false;
            is_level_value = true;
        }
        else if (argi == "-table")
        {
            is_table = true;
        }
        else
        {
            return false;
        }
    }
    if (is_max_value && is_level_value) return false;
    return true;
}

std::string array_to_string(const int &argc, char **argv)
{
    std::string out_str = "";
    for (int i = 1; i < argc; i++)
    {
        if (i != 1)
            out_str += " ";
        out_str += argv[i];
    }
    return out_str;
}

bool create_empty_file(const std::string &filename)
{
    if (!std::filesystem::exists(filename))
    {
        std::ofstream out_file{filename, std::ios::out};
        if (!out_file.is_open())
        {
            return false;
        }
        else
        {
            out_file.close();
        }
    }
    return true;
}

bool read_unique_records_from_file(const std::string &filename, std::vector<std::pair<std::string, int>> &table_)
{
    std::ifstream in_file{filename};

    if (!in_file.is_open())
    {
        std::cout << "Failed to open file for reading: " << filename << "!" << std::endl;
        return false;
    }

    // Read file records and store in vector best records for each username, so one record per username
    std::string username;
    int guess_count = 0;
    while (true)
    {
        in_file >> username;
        in_file >> guess_count;
        in_file.ignore(); // Ignore the end of line symbol

        if (in_file.fail())
        {
            break;
        }

        bool is_found = false;
        for (auto &record : table_)
        {
            if (record.first == username && record.second > guess_count)
            {
                record.second = guess_count;
                is_found = true;
                break;
            }
        }

        if (!is_found)
        {
            table_.push_back({username, guess_count});
        }
    }
    in_file.close();
    return true;
}

bool rewrite_table_to_file(const std::string &filename, const std::vector<std::pair<std::string, int>> &table_)
{
    // Open file for writing and remove old content
    std::ofstream out_file{filename, std::ios_base::out | std::ios_base::trunc};

    if (!out_file.is_open())
    {
        std::cout << "Failed to open file for writing: " << filename << "!" << std::endl;
        return false;
    }

    // Writing new table of values to the file
    for (const auto &record : table_)
    {
        out_file << record.first << " " << record.second << std::endl;
    }
    out_file.close();
    return true;
}

bool print_table_of_best_scores(const std::string &filename)
{
    std::vector<std::pair<std::string, int>> table_;

    // Read best records from file
    if (!read_unique_records_from_file(filename, table_))
        return false;

    // Print best attempts of every username
    std::cout << "High score table:" << std::endl;
    for (const auto &record : table_)
    {
        std::cout << record.first << '\t' << record.second << std::endl;
    }
    return true;
}

bool write_record_to_file(const std::string &filename, const std::string &username, const int &guess_count)
{
    std::vector<std::pair<std::string, int>> table_;

    // Read best records from file
    if (!read_unique_records_from_file(filename, table_)) return false;

    // Delete record from vector if score is worse
    for (int i = 0; i < table_.size(); i++)
    {
        if (table_[i].first == username)
        {
            // std::cout << "Record exist" << std::endl;
            if (guess_count < table_[i].second)
            {
                table_.erase(table_.begin() + i);
                // std::cout << "Delete record with index " << i << std::endl;
            }
        }
    }

    // Append new record to the vector
    table_.push_back({username, guess_count});

    // Delete current content of the file and write new records
    if (!rewrite_table_to_file(filename, table_))
        return false;

    return true;
}

int interactive_guess_cycle(const std::string &user_name, const int &target_value)
{
    int guess_count = 0;
    int current_value = -1;
    std::cout << user_name << ", enter your guess:" << std::endl;
    while (true)
    {
        guess_count++;
        std::cin >> current_value;
        if (current_value < target_value)
        {
            std::cout << current_value << " is less than choosen nubmer" << std::endl;
        }
        else if (current_value > target_value)
        {
            std::cout << current_value << " is greater than choosen number" << std::endl;
        }
        else
        {
            std::cout << "\n"
                      << user_name << ", you win with score = " << guess_count << "! The choosen number was " << target_value << ".\n"
                      << std::endl;
            break;
        }
    }
    return guess_count;
}
