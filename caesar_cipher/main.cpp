#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>

#include "functions.hpp"


int main(int argc, char *argv[]){

    // https://www.bfilipek.com/2019/04/dir-iterate.html#using-c17
    // https://en.cppreference.com/w/cpp/filesystem/directory_iterator


    if (check_directories("input") == false){
        create_directories("input");
    }

    // warn user if code is run with no options
    else if (argc < 2){
        std::cout << "Missing argument!" << std::endl;
        show_options();
    }

    // options
    else if (argc < 3){
        std::unordered_set <std::string> interactive_choice {"-c", "--cipher", "-d", "--decipher"};
        std::unordered_set <std::string> cipher_file_choice {"-cf", "-c -f", "--cipher -f"};
        std::unordered_set <std::string> decipher_file_choice {"-df", "-d -f", "--decipher -f"};
        std::vector <char> a {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 
                              'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 
                              's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

        // -h, --help
        if (std::string(argv[1]) == "--help" ||
            std::string(argv[1]) == "-h"){
            show_options();
        }  

        // interactive mode     
        else if (interactive_choice.find(argv[1]) != interactive_choice.end()){
            while (true){
                std::cout << "Enter your message or '...' to exit:\n> ";
                std::string input_string = take_input_string();
                if (input_string == "..."){
                    break;
                }
                std::cout << "Please enter cipher key (1 - 26)\n> ";
                int key = take_input_key();
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

        //chipher and decipher files from input directory
        else if (cipher_file_choice.find(argv[1]) != cipher_file_choice.end() ||
                 decipher_file_choice.find(argv[1]) != decipher_file_choice.end()){
            
            std::vector <std::string> my_files;
            my_files = retrieve_files();
            if (my_files.size() == 0){
                std::cout << "Input folder is empty" << std::endl;
            }
            else{
                if (check_directories("output") == false){
                    create_directories("output");
                }
                std::cout << "Please enter cipher key (1 - 26)\n> ";
                int key = take_input_key();
                std::vector <char> cipher_alphabet = create_alphabet(a, key);
                
                for (auto x : my_files){
                    std::string input_string = read_file(x);
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
                    
                }
                std::cout << "All input files have been succesfully processed" << std::endl;
            }
        }

        // TODO:implement decipher by bruteforce + frequency analysis
        // else if (){

        // }


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