#include <iostream>
#include <vector>
#include <string>
#include "functions.hpp"


int main(int argc, char *argv[]){
    if (argc < 2){
        std::cout << "Missing argument!" << std::endl;
        show_options();
        }
    else if (argc < 3){
        if (std::string(argv[1]) == "--help" ||
            std::string(argv[1]) == "-h"){
            show_options();
        }
        else if (std::string(argv[1]) == "-c" ||
                 std::string(argv[1]) == "-cipher" ||
                 std::string(argv[1]) == "-d" ||
                 std::string(argv[1]) == "-decipher" ||
                 std::string(argv[1]) == "-c -f" ||
                 std::string(argv[1]) == "-cf" ||
                 std::string(argv[1]) == "-d -f" ||
                 std::string(argv[1]) == "-df" ||
                 std::string(argv[1]) == "-cipher -f" ||
                 std::string(argv[1]) == "-decipher -f"){
            std::vector <char> a {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                                  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                                  'u', 'v', 'w', 'x', 'y', 'z'};
            int key;
            while (true){
                std::string input_string;
                std::cout << "Please enter a message or '...' to exit\n> ";
                std::getline(std::cin, input_string);
                if (input_string == "..."){
                    break;
                }
                std::cout << "Please enter cipher key (1 - 26)\n> ";
                std::cin >> key;
                // flush the newline character out of the buffer between cin and getline in next loop
                std::cin.ignore();
                if (key > 0 && key < 26){
                    std::vector <char> cipher_alphabet = create_alphabet(a, key);
                    if (std::string(argv[1]) == "--cipher" ||
                        std::string(argv[1]) == "-c"){
                    // if (std::string_view(argv[1]) == "cipher") {    **valid from C++17??
                        std::string output = cipher(input_string, a, cipher_alphabet);
                        std::cout << output << "\n\n";
                    }
                    else if (std::string(argv[1]) == "--decipher" ||
                             std::string(argv[1]) == "-d"){
                        std::string output = decipher(input_string, a, cipher_alphabet);
                        std::cout << output << "\n\n";
                    }
                }
                else{
                    std::cout << "sorry, try that again\n";
                }
            }
        }
        else{
            std::cout << "Invalid option!" << std::endl;
            show_options();
        }
    }
}