#include <iostream>
#include <unordered_map>
#include <string>

std::unordered_map <char, char> create_alphabet(std::string v, int k){
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

std::string cipher(std::string input_s, std::unordered_map <char, char> alphb_cip){
    std::string message;

    for (int i=0; i<input_s.size(); i++){
        if (ispunct(input_s[i]) || isspace(input_s[i]) || isdigit(input_s[i])){
            message.push_back(input_s[i]);
        }

        else{
            if (isupper(input_s[i])){
                message.push_back(toupper(alphb_cip[tolower(input_s[i])]));
                std::cout << "e" << std::endl;
            }
            else{
                message.push_back(alphb_cip[input_s[i]]);
            }
            
        }
    }
    return message;
}


int main(){
    std::string actual_alphabet = "abcdefghijklmnopqrstuvwxYz";
    std::unordered_map  <char, char> alph = create_alphabet(actual_alphabet, 1);
    // for (auto& it: alph) {
    // // Do stuff
    // std::cout << it.first << " " << it.second << std::endl;
    // }
    std::string strin = "ciaoCIAOciao";
    std::string message = cipher(strin, alph);
    std::cout << message << std::endl;
}