// Felipe Urra Rivadeneira 0MI8000066

#include "utils.h"
#include <limits>

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

Student* Utils::getStudentById(int id, CustomVector<Student*>& students) {

    for (int i = 0; i < students.getSize(); ++i) {
        if (students[i]->getId() == id) {
            return students[i];
        }
    }

    std::cout << "No student found with ID: " << id << "\n";
    return nullptr;
}

User* Utils::getUserById(int id, const CustomVector<User*>& users) {
    for (int i = 0; i < users.getSize(); ++i) {
        if (users[i]->getId() == id) {
            return users[i];
        }
    }

    return nullptr;
}

Course* Utils::getCourseByName(CustomString& courseName, const CustomVector<Course*>& courses) {
    for (int i = 0; i < courses.getSize(); i++) {
        if (courses[i]->getName() == courseName) {
            return courses[i];
        }
    }
    return nullptr;
}

bool Utils::isAllGoodWithDataEntry(int id) {
    if (std::cin.fail() || id < 0) {
        std::cout << "Invalid ID! Please enter a positive integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool Utils::isAllGoodWithDataEntry(double grade) {
    if (std::cin.fail() || grade > 6.0) {
        std::cout << "Invalid grade! Please enter a positive rational number lower than 6.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}