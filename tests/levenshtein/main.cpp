#include <iostream>
#include <string>
#include "../../functions.hpp"



int main(){
    std::string s1, s2;

    s1 = "test";
    s2 = "text";

    std::cout << levenshtein(s1, s2) << std::endl;
}
