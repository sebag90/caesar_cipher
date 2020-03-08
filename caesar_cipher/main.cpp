#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

#include "functions.hpp"


// TODO: add support for files from folder input >> output

int main(int argc, char *argv[]){
    if (argc < 2){
        std::cout << "Missing argument!" << std::endl;
        show_options();
        }
    else if (argc < 3){
        std::unordered_set <std::string> choice {"-c", "--cipher", "-d", "--decipher", "-c -f", "-cf", "-d -f", "-df", "--cipher -f", "--decipher -f"};
        if (std::string(argv[1]) == "--help" ||
            std::string(argv[1]) == "-h"){
            show_options();
        }        
        else if (choice.find(argv[1]) != choice.end()){
            std::vector <char> a {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                                  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                                  'u', 'v', 'w', 'x', 'y', 'z'};
            int key;
            while (true){
                std::cout << "Enter your message or '...' to exit:\n> ";
                std::string input_string = take_input_string();
                if (input_string == "..."){
                    break;
                }
                std::cout << "Please enter cipher key (1 - 26)\n> ";
                key = take_input_key();
                // flush the newline character out of the buffer between cin and getline in next loop
                std::cin.ignore();
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
        }

        else if ("file"){
            // TODO: file support
        }
        
        else{
            std::cout << "Invalid option!" << std::endl;
            show_options();
        }
    }
}