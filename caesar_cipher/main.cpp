#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>

#include "functions.hpp"


int main(int argc, char *argv[]){

    // TODO:add function to create input and output directory if not present
    // https://www.bfilipek.com/2019/04/dir-iterate.html#using-c17
    // https://en.cppreference.com/w/cpp/filesystem/directory_iterator

    if (argc < 2){
        std::cout << "Missing argument!" << std::endl;
        show_options();
        }
    else if (argc < 3){
        std::unordered_set <std::string> choice {"-c", "--cipher", "-d", "--decipher"};
        std::unordered_set <std::string> cipher_file_choice {"-cf", "-c -f", "--cipher -f"};
        std::unordered_set <std::string> decipher_file_choice {"-df", "-d -f", "--decipher -f"};
        std::vector <char> a {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 
                                  'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 
                                  's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

        if (std::string(argv[1]) == "--help" ||
            std::string(argv[1]) == "-h"){
            show_options();
        }        
        else if (choice.find(argv[1]) != choice.end()){
            
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
        //chipher file
        else if (cipher_file_choice.find(argv[1]) != cipher_file_choice.end() ||
                 decipher_file_choice.find(argv[1]) != decipher_file_choice.end()){
            std::vector <std::string> my_files;
            my_files = retrieve_files();
            
            if (my_files.size() == 0){
                std::cout << "Input folder is empty" << std::endl;
            }
            else{
                std::cout << "Please enter cipher key (1 - 26)\n> ";
                int key = take_input_key();
                std::vector <char> cipher_alphabet = create_alphabet(a, key);
                
                for (auto x : my_files){
                    std::ifstream file;
                    file.open("./input/" + x);
                    std::string input_string;
                    std::string input_string2;
                    while(getline(file, input_string2)){
                        input_string += input_string2 + "\n";
                    }
                    if (!input_string.empty() && input_string[input_string.length()-1] == '\n') {
                        input_string.erase(input_string.length()-1);
                    }
                    std::string output;
                    if (cipher_file_choice.find(argv[1]) != cipher_file_choice.end()){
                        output = cipher(input_string, a, cipher_alphabet);
                    }
                    else if (decipher_file_choice.find(argv[1]) != decipher_file_choice.end()){
                        output = decipher(input_string, a, cipher_alphabet);
                    }
                    std::ofstream my_output ("./output/" + x);
                    my_output << output;
                    my_output.close();
                    file.close();
                }
                std::cout << "All input files have been succesfully processed" << std::endl;
            }
        }
        else{
        std::cout << "Function not supported" << std::endl;
        show_options();
        }
    }
    else{
        std::cout << "Function not supported" << std::endl;
        show_options();
    }
}