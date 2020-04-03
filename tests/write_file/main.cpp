#include <iostream>
#include <vector>
#include <string>
#include "../../functions.hpp"



int main(){
   
    std::string test1, test2, test3;

    test1 = "this is a test";
    test2 = "this is another test";
    test3 = "khaleesi is marrying jack sparrow";

    std::vector <std::string> file_names {test1, test2, test3};
    
    for (int i = 0; i < file_names.size(); i++){
        save_file("test" + std::to_string(i + 1), file_names[i]);
    }
}
