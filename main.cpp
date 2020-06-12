#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>


#include "functions.h"


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
        std::unordered_set <std::string> bruteforce_choice {"-bf", "--bruteforce"};
        std::string actual_alphabet = "abcdefghijklmnopqrstuvwxyz";
        int key_limit = actual_alphabet.size();

        // -h, --help
        if (std::string_view(argv[1]) == "--help" ||
            std::string_view(argv[1]) == "-h"){
            show_options();
        }  

        // interactive mode (loop)  
        else if (interactive_choice.find(argv[1]) != interactive_choice.end()){
            while (true){
                // take input string and key (with input validation)
                std::cout << "Enter your message or '...' to exit:\n> ";
                std::string input_string = take_input_string();

                if (input_string == "..."){
                    break;
                }

                int key = take_input_key(key_limit);
                std::unordered_map <char, char> cipher_alphabet = create_cipher_alphabet(actual_alphabet, key);
                std::unordered_map <char, char> decipher_alphabet = create_decipher_alphabet(actual_alphabet, key);

                // cipher or decipher based on user's choice
                if (std::string_view(argv[1]) == "--cipher" ||
                    std::string_view(argv[1]) == "-c"){
                        
                    std::string output = cipher(input_string, cipher_alphabet);
                    std::cout << output << "\n\n";
                }

                else if (std::string_view(argv[1]) == "--decipher" ||
                         std::string_view(argv[1]) == "-d"){
                             
                    std::string output = cipher(input_string, decipher_alphabet);
                    std::cout << output << "\n\n";
                }
            }
        }

        // chipher and decipher files from input directory
        else if (cipher_file_choice.find(argv[1]) != cipher_file_choice.end() ||
                 decipher_file_choice.find(argv[1]) != decipher_file_choice.end()){
            
            std::vector <std::string> my_files;
            my_files = retrieve_files("input");

            if (my_files.size() == 0){
                std::cout << "Input folder is empty" << std::endl;
            }

            else{
                // check if directories exist and take key to gorm a cipher alphabet
                if (check_directories("output") == false){
                    create_directories("output");
                }

                int key = take_input_key(key_limit);
                std::unordered_map <char, char> cipher_alphabet = create_cipher_alphabet(actual_alphabet, key);
                std::unordered_map <char, char> decipher_alphabet = create_decipher_alphabet(actual_alphabet, key);
                
                // cipher or decipher every file in the input order using the selected key
                for (auto x : my_files){
                    std::string input_string = read_file(x, "./input/");
                    std::string ciphred_input;

                    if (cipher_file_choice.find(argv[1]) != cipher_file_choice.end()){
                        ciphred_input = cipher(input_string, cipher_alphabet);
                    }

                    else if (decipher_file_choice.find(argv[1]) != decipher_file_choice.end()){
                        ciphred_input = cipher(input_string, decipher_alphabet);
                    }

                    save_file(x, ciphred_input, "./output/");
                    
                }
                std::cout << "All input files have been succesfully processed" << std::endl;
            }
        }

        // decipher by bruteforce + frequency analysis
        else if (bruteforce_choice.find(argv[1]) != bruteforce_choice.end()){

            std::vector <std::string> my_files;
            my_files = retrieve_files("input");

            if (my_files.size() == 0){
                std::cout << "Input folder is empty" << std::endl;
            }

            else{

                if (check_directories("output") == false){
                    create_directories("output");
                }

                for (auto x : my_files){
                    std::string input_string = read_file(x, "./input/");
                    std::string eng_letter_frequency = "etaoinsrhldcumfpgwybvkxjqz";
                    std::vector <std::pair <int, int>> results;
                    
                    // try every key and save pairs of <frequency, key> in a vector
                    for (int i = 0; i < 26; i++){
                        std::unordered_map <char, char> ciphred_alphabet = create_decipher_alphabet(actual_alphabet, i);
                        std::string deciphred_output = cipher(input_string, ciphred_alphabet);
                        std::string frequency_input = calculate_letter_frequecy(deciphred_output, actual_alphabet);
                        int distance = levenshtein(eng_letter_frequency, frequency_input);
                        results.push_back(std::make_pair(distance, i));
                        std::cout << "finished language analysis " << i+1 << " of " << 26 << std::endl;
                    }

                    // sort vector, the first result (smallest levenshtein distance) is the right key to decipher
                    std::sort(results.begin(), results.end());
                    std::unordered_map <char, char> ciphred_alphabet = create_decipher_alphabet(actual_alphabet, results[0].second);
                    std::string real_result = cipher(input_string, ciphred_alphabet);
                    save_file(x, real_result, "./output/");
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