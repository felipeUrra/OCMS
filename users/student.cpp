// Felipe Urra Rivadeneira 0MI8000066

#include "student.h"
#include "../answer.h"
#include "../course.h"
#include <iostream>

Student::Student(CustomString& name, CustomString& lastName, CustomString& password) :
    User(name, lastName, password, UserType::Student) {}

// Getters and setters
CustomVector<Course*>& Student::getCoursesEnrolled() {return coursesEnrolled;}
void Student::setCoursesEnrolled(CustomVector<Course*>& coursesEnrolled) {this->coursesEnrolled = coursesEnrolled;}

void Student::printGradesInfo() {
    for (int i = 0; i < this->coursesEnrolled.getSize(); i++) {
        Course* course = this->coursesEnrolled[i];
        for (int j = 0; j < course->getAssignments().getSize(); j++) {
            Assignment* assignment = course->getAssignments()[j];
            for (int k = 0; k < assignment->getAnswers().getSize(); k++) {
                Answer* answer = assignment->getAnswers()[k];
                if (answer->getStudentId() == this->getId() && answer->getIsGraded() == true) {
                    std::cout << course->getName() << " | " << assignment->getName() << " | " << answer->getGrade() << " |  " << answer->getTeacherComment() << "\n";
                }
            }
        }
    }
    
}

bool Student::hasCourse(CustomString& courseName) const{
    for (int i = 0; i < this->coursesEnrolled.getSize(); i++) {
        if (this->coursesEnrolled[i]->getName() == courseName) return true;
    }
    return false;
}

bool Student::hasAssignment(CustomString& assignmentName) const{
    for (int i = 0; i < this->coursesEnrolled.getSize(); i++) {
        for (int j = 0; i < this->coursesEnrolled[i]->getAssignments().getSize(); j++) {
            if (this->coursesEnrolled[i]->getAssignments()[j]->getName() == assignmentName) {
                return true;
            }
        }
    }
    
    return false;
}

// Serialize/deserialize
void Student::serialize(std::ofstream& out) const {
    this->serializeCommon(out);
    int courseCount = this->coursesEnrolled.getSize();
    out.write(reinterpret_cast<const char*>(&courseCount), sizeof(courseCount));
    for (int i = 0; i < courseCount; i++) {
        this->coursesEnrolled[i]->getName().serialize(out);
    }
}
void Student::deserialize(std::ifstream& in, const CustomVector<Course*>& courses) {
    this->deserializeCommon(in);

    int courseCount;
    in.read(reinterpret_cast<char*>(&courseCount), sizeof(courseCount));
    this->coursesEnrolled.clear();

    for (int i = 0; i < courseCount; i++) {
        CustomString courseName;
        courseName.deserialize(in);
        for (int j = 0; j < courses.getSize(); j++) {
            if (courses[j]->getName() == courseName) {
                courses[j]->getStudentsMembers().push_back(this);
                this->coursesEnrolled.push_back(courses[j]);
                break;
            }
        }
    }
}