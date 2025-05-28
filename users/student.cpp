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

// Serialize/deserialize
    void Student::serialize(std::ofstream& out) const {
        User::serialize(out);

        int courseCount = this->coursesEnrolled.getSize();
        out.write(reinterpret_cast<const char*>(&courseCount), sizeof(courseCount));
        for (int i = 0; i < courseCount; i++) {
            this->coursesEnrolled[i]->getName().serialize(out);
        }
    }
    void Student::deserialize(std::ifstream& in, const CustomVector<Course*>& courses) {
        User::deserialize(in);

        int courseCount;
        in.read(reinterpret_cast<char*>(&courseCount), sizeof(courseCount));
        this->coursesEnrolled.clear();

        for (int i = 0; i < courseCount; i++) {
            CustomString courseName;
            courseName.deserialize(in);

            for (int j = 0; j < courses.getSize(); j++) {
                if (courses[j]->getName() == courseName) {
                    this->coursesEnrolled.push_back(courses[j]);
                    break;
                }
            }
        }
    }