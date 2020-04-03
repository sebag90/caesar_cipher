#include <iostream>
#include "../../functions.hpp"


int main(){
    std::locale::global(std::locale(""));
    while(true){
        //std::string testing = L"ciao";
        std::string testing = take_input_string();
        
        int key = take_input_key(100);
        
        std::cout << "string: " <<  testing  << "\nkey: " << key  << "\n\n"  << std::endl;
    }
}
