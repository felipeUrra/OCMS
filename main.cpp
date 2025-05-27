// Felipe Urra Rivadeneira 0MI8000066

#include "system.h"
#include <iostream>

int main() {
    
    System system;

    while (system.getCloseSystem() == false) {
        std::cout << "> ";
        CustomString cmd;
        std::cin >> cmd;
        system.detectCommand(cmd);
    }
    
    return 0;
}