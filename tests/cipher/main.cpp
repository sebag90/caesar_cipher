#include <iostream>
#include <string>
#include "../../functions.hpp"



int main(){
    
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int key = 4;

    std::string cipher_alphabet = create_alphabet(alphabet, key);
    std::string message = "ciao";

    std::cout << cipher(message, alphabet, cipher_alphabet) << std::endl;

}
