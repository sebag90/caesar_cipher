#include <iostream>
#include <vector>
#include <string>


std::vector <char> create_alphabet(std::vector <char> v, int k){
    std::vector <char> b;
    for (int i=v.size() - k; i <= v.size() - 1; i++){
        b.push_back(v[i]);
    }

    for (int j = 0; j < v.size() - k; j++){
        b.push_back(v[j]);
    }
    return b;
}

int main(){
    std::vector <char> a {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int key;
    while (true){
        std::cout << "Please enter cipher key\n> ";
        std::cin >> key;
        if (key > 0 &&
            key < 27){
                break;
        }
    }
    std::vector <char> cipher_alphabet = create_alphabet(a, key);

   
}