// Felipe Urra Rivadeneira 0MI8000066

#include "system.h"
#include "utils.h"
#include <iostream>

int main() {
    
    System system;
    Utils::loadSystemState(system, "systemData.bin");

    while (system.getCloseSystem() == false) {
        std::cout << "> ";
        CustomString cmd;
        std::cin >> cmd;
        system.detectCommand(cmd);
    }
    
    Utils::saveSystemState(system, "systemData.bin");

    return 0;
}