// Felipe Urra Rivadeneira 0MI8000066

#include "system.h"
#include "utils.h"
#include <limits>
#include <iostream>

int main() {
    
    System system;
    Utils::loadSystemState(system, "systemData.bin");

    int i = 0;
    while (system.getCloseSystem() == false) {
        if (i > 0 && std::cin.peek() != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Warning: You entered more parameters than necessary.\n";
        }
        
        std::cout << "> ";

        CustomString cmd;
        std::cin >> cmd;
        system.detectCommand(cmd);
        i++;
    }
    
    Utils::saveSystemState(system, "systemData.bin");

    return 0;
}