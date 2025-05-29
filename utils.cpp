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

    std::cout << "No user found with ID: " << id << "\n";
    return nullptr;
}

Course* Utils::getCourseByName(CustomString& courseName, const CustomVector<Course*>& courses) {
    for (int i = 0; i < courses.getSize(); i++) {
        if (courses[i]->getName() == courseName) {
            return courses[i];
        }
    }
    std::cout << "No course found with name: " << courseName << '\n';
    return nullptr;
}