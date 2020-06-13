#include <iostream>

#define PBSTR "############################################################"
#define PBWIDTH 60

void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}


int main(){
    for (double i=0; i<1000000; i++){
        printProgress(i/1000000);
    }
    std::cout << std::endl;
}
