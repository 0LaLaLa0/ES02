#include <iostream>
#include "../include/Printf.h"

char _hex[] = {'0', '1', '2'};

void init(char _string[]){
    for (int i = 0; i < 42; i++){
        _string[i] = 0;
    }
}

int main() {
    char _string[42];

    init(_string);
    intToBaseString(_string,_string+42,10,2, true);
    std::cout << _string << std::endl;

    init(_string);
    intToBaseString(_string,_string+42,-10,10, false);
    std::cout << _string << std::endl;

    init(_string);
    intToBaseString(_string,_string+42,10,16, true);
    std::cout << _string << std::endl;

    Printf(nullptr, nullptr, "");
    return 0;
}

