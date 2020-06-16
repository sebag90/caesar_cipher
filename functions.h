#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <vector>
#include <string>
#include <unordered_map>


void show_options();

std::unordered_map <char, char> create_cipher_alphabet(std::string v, int k);

std::unordered_map <char, char> create_decipher_alphabet(std::string v, int k);

std::string cipher(std::string input_s, std::unordered_map <char, char> alphb_cip);

std::string decipher(std::string input_s, std::string alphb_real, std::string alphb_cip);

std::string take_input_string();

int take_input_key(int limit);

std::vector<std::string> retrieve_files(std::string directory);

bool check_directories(std::string name);

void create_directories(std::string name);

std::string read_file(std::string filename, std::string directory);

void save_file(std::string filename, std::string string_to_save, std::string directory);

std::string calculate_letter_frequecy(std::string input_string, std::string alphabet);

int levenshtein (std::string string1, std::string string2);

std::vector <std::pair <int, std::string>> language_analysis (int start, int end, std::string real_alphabet, std::string input);

void printProgBar(int percent);

#endif 