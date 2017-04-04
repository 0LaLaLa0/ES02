#include <iostream>
#include "../include/Printf.h"

void init(char _string[]){
    for (int i = 0; i < 4; i++){
        _string[i] = 0;
    }
}

int main() {
    char _string[15];

    Printf(_string, _string+14, "%%%z%d%s", -2000000, "testString", 'c', -42, -42, 42, 42);
    std::cout << _string << std::endl;
    return 0;
}

