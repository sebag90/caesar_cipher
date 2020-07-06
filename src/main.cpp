#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <thread>
#include <future>

#include "functions.h"


int main(int argc, char *argv[]){

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
                // check if directories exist and take key (user input) to form a cipher alphabet
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
                int file_counter = 1;
                std::string actual_alphabet = "abcdefghijklmnopqrstuvwxyz";
                for (auto x : my_files){
                    
                    std::string input_string = read_file(x, "./input/");
                    
                    auto t1 = std::async(language_analysis, 0, 3, actual_alphabet, input_string);
                    auto t2 = std::async(language_analysis, 3, 6, actual_alphabet, input_string);
                    auto t3 = std::async(language_analysis, 6, 9, actual_alphabet, input_string);
                    auto t4 = std::async(language_analysis, 9, 12, actual_alphabet, input_string);
                    auto t5 = std::async(language_analysis, 12, 16, actual_alphabet, input_string);
                    auto t6 = std::async(language_analysis, 16, 19, actual_alphabet, input_string);
                    auto t7 = std::async(language_analysis, 19, 22, actual_alphabet, input_string);
                    auto t8 = std::async(language_analysis, 22, 26, actual_alphabet, input_string);

                    std::vector <std::vector <std::pair <int, std::string>>> vec_of_vecs;

                    std::vector <std::pair <int, std::string>> vect1 = t1.get();
                    std::vector <std::pair <int, std::string>> vect2 = t2.get();
                    std::vector <std::pair <int, std::string>> vect3 = t3.get();
                    std::vector <std::pair <int, std::string>> vect4 = t4.get();
                    std::vector <std::pair <int, std::string>> vect5 = t5.get();
                    std::vector <std::pair <int, std::string>> vect6 = t6.get();
                    std::vector <std::pair <int, std::string>> vect7 = t7.get();
                    std::vector <std::pair <int, std::string>> vect8 = t8.get();
        
                    vec_of_vecs.push_back(vect1);
                    vec_of_vecs.push_back(vect2);
                    vec_of_vecs.push_back(vect3);
                    vec_of_vecs.push_back(vect4);
                    vec_of_vecs.push_back(vect5);
                    vec_of_vecs.push_back(vect6);
                    vec_of_vecs.push_back(vect7);
                    vec_of_vecs.push_back(vect8);

                    int lowest_i = 100;
                    std::string best_text;

                    for (auto vec: vec_of_vecs){    
                        if( vec[0].first <= lowest_i){
                            best_text = vec[0].second;
                            lowest_i = vec[0].first;
                        }
                    }
                
                    save_file(x, best_text, "./output/");
                    print_progbar(100);
	                std::cout << std::endl;
                    std::cout << "File " << file_counter << " of " << my_files.size() << " completed\n" <<  std::endl;
                    file_counter = file_counter + 1;
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