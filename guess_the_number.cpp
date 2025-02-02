#include <iostream>
#include <string>

#include "guess_funcs.hpp"

int main(int argc, char **argv)
{
    const std::string high_scores_filename = "high_scores.txt";

    // Create empty file if not exist
    if (!create_empty_file(high_scores_filename))
    {
        std::cout << "File with records does not exist and can't be created!" << std::endl;
        return EXIT_FAILURE;
    }

    const unsigned int default_max_value = 100;

    // Process command line arguments: -table -max N
    bool is_table(false);
    bool is_max_value(false);
    unsigned int param_max_value = 0;
    bool is_level_value(false);
    unsigned int param_level_value = 0;
    if (argc > 1)
    {
        if (!recognize_command_line_parameters(argc, argv, is_table, is_max_value, param_max_value, is_level_value, param_level_value))
        {
            std::cout << "\nWrong command line parameters: " << array_to_string(argc, argv) << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Print table when -table argument
    if (is_table)
    {
        if (print_table_of_best_scores(high_scores_filename))
        {
            return EXIT_SUCCESS;
        }
        else
        {
            return EXIT_FAILURE;
        }
    }

    // Change default Max value with -max N
    unsigned int max_value;
    if (is_level_value)
    {
        switch (param_level_value)
        {
        case 1:
            max_value = 10;
            break;
        case 2:
            max_value = 50;
            break;
        case 3:
            max_value = 100;
            break;
        default:
            return EXIT_FAILURE;
        }
        std::cout << "\nNew maximum value (" << max_value << ") is defined by command line argument '-level " << param_level_value << "'." << std::endl;
    }
    else if (is_max_value)
    {
        max_value = param_max_value;
        std::cout << "\nNew maximum value (" << max_value << ") is defined by command line argument '-max" << max_value << "'." << std::endl;
    }
    else
    {
        max_value = default_max_value;
    }

    // Ask about name
    std::cout << "\nHi! Enter your name, please:" << std::endl;
    std::string user_name;
    std::cin >> user_name;

    // Print short game rules
    std::cout << "\n"
              << user_name << ", let's play the game! \nI select a number between 0 and "
              << max_value << ". You enter your guess, and I provide hints.\n"
              << std::endl;

    // Select random target value
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // use current time (seconds) as seed for random generator
    const unsigned int target_value = std::rand() % max_value;

    // Play game cycle
    const int guess_count = interactive_guess_cycle(user_name, target_value);

    // Write record to the file
    if (!write_record_to_file(high_scores_filename, user_name, guess_count))
        return EXIT_FAILURE;

    // Print the table of records
    if (!print_table_of_best_scores(high_scores_filename))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
