#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <dirent.h>
#include <filesystem>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <fstream>


// show programme parameters
void show_options(){
    std::cout   << "Options:\n"
                << "\t-h, --help\t\tshow this message and exit\n"
                << "\t-c, --cipher\t\tencode a message in interactive mode\n"
                << "\t-d, --decipher\t\tdecode a message in interactive mode\n"
                << "\t-cf, --cipher -f\tencode files in input folder\n"
                << "\t-df, --decipher -f\tdecode files in input folder\n"
                << "\t-bf, --bruteforce\tcrack ciphred files in input folder"
                << std::endl << std::endl;
}


// shift the alphabet based on the given shift-key
std::unordered_map <char, char> create_cipher_alphabet(std::string v, int k){
    std::unordered_map <char, char> a;
    std::string b;

    for (int i=v.size() - k; i <= v.size() - 1; i++){
        b.push_back(v[i]);
    }

    for (int j = 0; j < v.size() - k; j++){
        b.push_back(v[j]);
    }

    for (int k = 0; k < b.size(); k++){
        a[b[k]] = v[k];
    }

    return a;
}

std::unordered_map <char, char> create_decipher_alphabet(std::string v, int k){
    std::unordered_map <char, char> a;
    std::string b;

    for (int i=v.size() - k; i <= v.size() - 1; i++){
        b.push_back(v[i]);
    }

    for (int j = 0; j < v.size() - k; j++){
        b.push_back(v[j]);
    }

    for (int k = 0; k < b.size(); k++){
        a[v[k]] = b[k];
    }

    return a;
}


// based on the real and shifted alphabet, cipher a message
std::string cipher(std::string input_s, std::unordered_map <char, char> alphb_cip){
    std::string message;

    for (int i=0; i<input_s.size(); i++){
        if (ispunct(input_s[i]) || isspace(input_s[i]) || isdigit(input_s[i])){
            message.push_back(input_s[i]);
        }

        else{
            if (isupper(input_s[i])){
                message.push_back(toupper(alphb_cip[tolower(input_s[i])]));
            }
            else{
                message.push_back(alphb_cip[input_s[i]]);
            }
            
        }
    }
    return message;
}


// based on the real and shifted alphabet, decipher a message
// std::string decipher(std::string input_s, std::string alphb_real, std::string alphb_cip){
//     std::string message;

//     for (int i=0; i<input_s.size(); i++){
//         if (ispunct(input_s[i]) || isspace(input_s[i]) || isdigit(input_s[i])){
//             message.push_back(input_s[i]);
//         }

//         for (int j=0; j<alphb_real.size(); j++){
//             if (tolower(input_s[i]) == alphb_real[j]){
//                 if (isupper(input_s[i])){
//                     message.push_back(toupper(alphb_cip[j]));
//                 }
//                 else{
//                     message.push_back(alphb_cip[j]);
//                 }
//             }
//         }
//     }
//     return message;
// }


// take an input string
std::string take_input_string(){
    std::string a;
    getline(std::cin, a);
    return a;
}


// ask user for cipher key with input validation for 0 < int < 26
int take_input_key(int limit){
    std::cout << "Please enter cipher key (1 - " << limit - 1 << ")\n> ";
    int a;
    std::cin>>a;

    while(true){
        if (std::cin.fail() || a < 1 || a >= limit){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits <std::streamsize> ::max(),'\n');
            std::cout << "Invalid key\n> ";
            std::cin>>a;
        }

        if(!std::cin.fail() && a > 0 && a < limit){
            break;
        }
    }

    std::cout << "Entered key: " << a << std::endl;
    // flush the newline character out of the buffer between cin and getline in next loop
    std::cin.ignore();
    return a;
}


// create a vector with filenames
std::vector<std::string> retrieve_files(std::string directory){
    std::vector<std::string> files;   

    for(auto& p: std::filesystem::directory_iterator(directory)){
        files.push_back(p.path().filename());
    }
   
return files;
}


// read file from input directory
std::string read_file(std::string filename, std::string directory){
    std::ifstream file;
    file.open(directory + filename);
    std::string input_string, temp_input_string;

    while(getline(file, temp_input_string)){
        input_string += temp_input_string + "\n";
    }

    if (!input_string.empty() && input_string[input_string.length()-1] == '\n') {
        input_string.erase(input_string.length()-1);
    }

    file.close();

    return input_string;
}


//save file in output directory
void save_file(std::string filename, std::string string_to_save, std::string directory){
    std::ofstream my_output (directory + filename);
    my_output << string_to_save;
    my_output.close();
}


// check if a directory is present
bool check_directories(std::string name){
    std::unordered_set <std::string> directories;

    for(auto& p: std::filesystem::directory_iterator(std::filesystem::current_path())){
        if (p.is_directory()){
            directories.insert(p.path().filename());
        }
    } 

    if (directories.find(name) != directories.end()){
        return true;
    }

    else{
        return false;
    }
}


// create a directory
void create_directories(std::string name){
    std::filesystem::create_directories(name);
    std::cout << name << " directory has been created, you are now ready to go" << std::endl;
}


// calculate letter frequency
std::string calculate_letter_frequecy(std::string input_string, std::string alphabet){
    std::map <char, double> letter_frequency;
    std::string ordered_letters;
    int total = 0;
    
    for (auto x : input_string){
        if (find(alphabet.begin(), alphabet.end(), x) != alphabet.end()){
            total = total + 1;
            letter_frequency[x] = letter_frequency[x] + 1;
        }
    }

    // create vector of pairs (frequency - letter)
    std::vector <std::pair <double, char>> freq_vec;
    for (auto x : letter_frequency){
        x.second = x.second/total;
        freq_vec.push_back(std::make_pair(x.second, x.first));
    }

    // sort vector in descending order
    std::sort(freq_vec.rbegin(), freq_vec.rend());

    // create a string of used letters most frequent to least frequent
    for (auto x : freq_vec){
        ordered_letters.push_back(x.second);
    }
    return ordered_letters;
}


// calculate levenshtein distance
int levenshtein (std::string string1, std::string string2){
    const int x = string1.length () + 1;
    const int y = string2.length() + 1;
    
    // working only linux
    // int matrix[x][y] = {0}; 

    int matrix[x][y];

    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            matrix[i][j] = 0;
        }
    }

    // borders of matrix
    for (int i = 0; i < x ; i++){
        matrix[i][0] = i;
    }
    for (int j = 0; j < y; j++){
        matrix[0][j] = j;
    }
    // levenshtein matrix
    for (int i = 1; i < x; i++){
        for (int j = 1; j < y; j++){
            int cost;
            if (string1[i - 1] == string2[j-1]){
                matrix[i][j] = std::min({matrix[i - 1][j] + 1, 
                                         matrix[i][j - 1] + 1, 
                                         matrix[i - 1][j - 1]});
            }
            else{
                matrix[i][j] = std::min({matrix[i - 1][j] + 1, 
                                         matrix[i][j - 1] + 1, 
                                         matrix[i - 1][j - 1] + 1});
            }
        }
    }
    return matrix[x - 1][y - 1];
}