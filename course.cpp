// Felipe Urra Rivadeneira 0MI8000066

#include "course.h"

Course::Course(const CustomString& name, const CustomString& password) : name(name), password(password) {}
Course::~Course() {
    for (int i = 0; i < this->assignments.getSize(); i++) {
        delete this->assignments[i];
    }
}


// Getters and setters
CustomString Course::getName() const{return this->name;}
CustomString Course::getPassword() const{return this->password;}
CustomVector<Assignment*>& Course::getAssignments() {return this->assignments;}
CustomVector<Student*>& Course::getStudentsMembers() {return this->studentsMembers;}

void Course::setName(CustomString& name) {this->name = name;}
void Course::setPassword(CustomString& password) {this->password = password;}
void Course::setAssignments(CustomVector<Assignment*>& assigments) {this->assignments = assigments;}
void Course::setStudentsMembers(CustomVector<Student*>& studentsMembers) {
    
    int count = 0;
    for (int i = 0; i < studentsMembers.getSize(); i++) {
        if (studentsMembers[i]->getUserType() == UserType::Student) {count++;}
    }
    
    if (count == studentsMembers.getSize()) {
        this->studentsMembers = studentsMembers;
        return;
    }
    
    // maybe write something or handle it like a exception
}


bool Course::hasAssignment(CustomString& assignmentName) const {
    for (int i = 0; i < this->assignments.getSize(); i++) {
        if (this->assignments[i]->getName() == assignmentName) {
            return true;
        }
    }
    return false;
}

Assignment* Course::getAssignmentByName(CustomString& assignmentName) {
    for (int i = 0; i < this->assignments.getSize(); i++) {
        if (this->assignments[i]->getName() == assignmentName) {
            return this->assignments[i];
        }
    }
    return nullptr;
}

// Serialize/deserialize
void Course::serialize(std::ofstream& out) const {
    this->name.serialize(out);
    this->password.serialize(out);

    int assignSize = assignments.getSize();
    out.write(reinterpret_cast<const char*>(&assignSize), sizeof(assignSize));
    for (int i = 0; i < assignSize; i++) {
        assignments[i]->serialize(out);
    }
    
    // el error esta aqui
    // int studentCount = studentsMembers.getSize();
    // out.write(reinterpret_cast<const char*>(&studentCount), sizeof(studentCount));
    // for (int i = 0; i < studentCount; i++) {
    //     int id = studentsMembers[i]->getId();
    //     out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    // }
}
void Course::deserialize(std::ifstream& in) {
    this->name.deserialize(in);
    this->password.deserialize(in);

    int assignSize;
    in.read(reinterpret_cast<char*>(&assignSize), sizeof(assignSize));
    // for (size_t i = 0; i < assignments.getSize(); ++i) {
    //     delete assignments[i];
    // }
    // this->assignments.clear();
    for (int i = 0; i < assignSize; i++) {
        Assignment* a = new Assignment();
        a->deserialize(in);
        this->assignments.push_back(a);
    }
}