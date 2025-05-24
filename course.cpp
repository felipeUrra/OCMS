// Felipe Urra Rivadeneira 0MI8000066

#include "course.h"

Course::Course(const CustomString& name, const CustomString& password) : name(name), password(password) {}
Course::~Course() {
    for (uint8_t i = 0; i < this->assignments.getSize(); i++) {
        delete this->assignments[i];
    }
}


// Getters and setters
CustomString Course::getName() const{return this->name;}
CustomString Course::getPassword() const{return this->password;}
CustomVector<Assignment*>& Course::getAssignments() {return this->assignments;}
CustomVector<User*>& Course::getStudentsMembers() {return this->studentsMembers;}

void Course::setName(CustomString& name) {this->name = name;}
void Course::setPassword(CustomString& password) {this->password = password;}
void Course::setAssignments(CustomVector<Assignment*>& assigments) {this->assignments = assigments;}
void Course::setStudentsMembers(CustomVector<User*>& studentsMembers) {
    
    uint8_t count = 0;
    for (uint8_t i = 0; i < studentsMembers.getSize(); i++) {
        if (studentsMembers[i]->getUserType() == UserType::Student) {count++;}
    }
    
    if (count == studentsMembers.getSize()) {
        this->studentsMembers = studentsMembers;
        return;
    }
    
    // maybe write something or handle it like a exception
}