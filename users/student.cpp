// Felipe Urra Rivadeneira 0MI8000066

#include "student.h"
#include <iostream>

Student::Student(CustomString& name, CustomString& lastName, CustomString& password) :
    User(name, lastName, password, UserType::Student) {}

// Getters and setters
CustomVector<Course*>& Student::getCoursesEnrolled() {return coursesEnrolled;}
void Student::setCoursesEnrolled(CustomVector<Course*>& coursesEnrolled) {this->coursesEnrolled = coursesEnrolled;}

void Student::printGradesInfo() {
    for (uint8_t i = 0; i < this->coursesEnrolled.getSize(); i++) {
        for (uint8_t j = 0; j < this->coursesEnrolled[i]->getAssignments().getSize(); j++) {
            for (uint8_t k = 0; k < this->coursesEnrolled[i]->getAssignments()[j]->getAnswers().getSize(); k++) {
                Answer* a = this->coursesEnrolled[i]->getAssignments()[j]->getAnswers()[k];
                if (a->getStudent()->getId() == this->getId() && a->getIsGraded() == true) {
                    std::cout << this->coursesEnrolled[i]->getName() << " | " << this->coursesEnrolled[i]->getAssignments()[j] << " | " << a->getGrade() << " | " << a->getTeacherComment() << "\n";
                }              
            }
        }
    }
}