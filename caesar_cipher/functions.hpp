#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
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

#endif 