#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

bool create_empty_file(const std::string &filename);
bool recognize_command_line_parameters(const int &argc, char **argv, bool &is_table, bool &is_max_value, unsigned int &max_value, bool &is_level_value, unsigned int &level_value);
std::string array_to_string(const int &argc, char **argv);
bool print_table_of_best_scores(const std::string &filename);
int interactive_guess_cycle(const std::string &user_name, const int &target_value);
bool write_record_to_file(const std::string &filename, const std::string &username, const int &guess_count);
