#include <iostream>
#include <vector>
#include <string>
#include "functions.cpp"


void show_options();

std::vector <char> create_alphabet(std::vector <char> v, int k);

std::string cipher(std::string input_s, std::vector <char> alphb_real, std::vector <char> alphb_cip);

std::string decipher(std::string input_s, std::vector <char> alphb_real, std::vector <char> alphb_cip);