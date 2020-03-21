#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP


#include <vector>
#include <string>



void show_options();

std::vector <char> create_alphabet(std::vector <char> v, int k);

std::string cipher(std::string input_s, std::vector <char> alphb_real, std::vector <char> alphb_cip);

std::string decipher(std::string input_s, std::vector <char> alphb_real, std::vector <char> alphb_cip);

std::string take_input_string();

int take_input_key();

std::vector<std::string> retrieve_files();

bool check_directories(std::string name);

void create_directories(std::string name);

std::string read_file(std::string filename);

void save_file(std::string filename, std::string string_to_save);

std::string calculate_letter_frequecy(std::string input_string, std::vector <char> alphabet);

int levenshtein (std::string string1, std::string string2);

#endif 