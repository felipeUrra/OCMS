// Felipe Urra Rivadeneira 0MI8000066

#include "professor.h"

Teacher::Teacher(CustomString& name, CustomString& lastName, CustomString& password) :
    User(name, lastName, password, UserType::Teacher) {}

Teacher::~Teacher() {
    for (uint8_t i = 0; i < this->courses.getSize(); i++) {
        delete this->courses[i];
    }
}

// getters and setters
CustomVector<Course*>& Teacher::getCourses() {return courses;}
void Teacher::setCourses(CustomVector<Course*>& courses) {this->courses = courses;}

void Teacher::createCourse(CustomString& name, CustomString& password) {
    Course* course = new Course(name, password);
    this->courses.push_back(course);
}

void Teacher::createAssignment(Course* course, CustomString& name) {
    Assignment* assignment = new Assignment(name);
    course->getAssignments().push_back(assignment);
}

void Teacher::enrollStudent(Course* course, User* student) {course->getStudentsMembers().push_back(student);}

Course* Teacher::getSpecificCourse(CustomString& courseName){
    for (uint8_t i = 0; i < this->courses.getSize(); i++) {
        if (this->courses[i]->getName() == courseName) {
            return this->courses[i];
        }
    }  
}
