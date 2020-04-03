#include <iostream>
#include <vector>
#include <string>
#include "../../functions.hpp"



int main(){
    std::vector <std::string> file_names;
    file_names = retrieve_files();

    for (auto x : file_names){
        std::string output = read_file(x);
        std::cout << output << std::endl;
    }
}
