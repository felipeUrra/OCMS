#include "utils.h"



void Utils::saveSystemState(const System& system, const CustomString& filename) {
    const char* fn = filename.c_str();

    std::ofstream outFile(fn, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Could not open file for writing: " << filename << "\n";
        return;
    }

    system.serialize(outFile);
    outFile.close();
}

void Utils::loadSystemState(System& system, const CustomString& filename) {
    const char* fn = filename.c_str();

    std::ifstream inFile(fn, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Could not open file for reading: " << filename << "\n";
        return;
    }

    system.deserialize(inFile);
    inFile.close();
}