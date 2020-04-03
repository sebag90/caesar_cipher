#include <iostream>
#include <string>
#include "../../functions.hpp"



int main(){
    
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string s1 = "tttteest";

    std::cout << calculate_letter_frequecy(s1, alphabet) << std::endl;
}
