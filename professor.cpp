// Felipe Urra Rivadeneira 0MI8000066

#include "professor.h"

Teacher::Teacher() {}
Teacher::Teacher(CustomString& name, CustomString& lastName, CustomString& password) :
    User(name, lastName, password, UserType::Teacher) {}

// getters and setters
CustomVector<Course*>& Teacher::getCourses() {return courses;}
void Teacher::setCourses(CustomVector<Course*>& courses) {this->courses = courses;}

void Teacher::createCourse(CustomString& name, CustomString& password) {
    Course course(name, password);
    this->courses.push_back(&course);
}

void Teacher::createAssignment(Course* course, CustomString& name) {
    Assignment assignment(name);
    course->getAssignments().push_back(&assignment);
}

void Teacher::enrollStudent(Course* course, User* student) {course->getStudentsMembers().push_back(student);}

Course* Teacher::getSpecificCourse(CustomString& courseName){
    for (uint8_t i = 0; i < this->courses.getSize(); i++) {
        if (this->courses[i]->getName() == courseName) {
            return this->courses[i];
        }
    }  
}

void Teacher::gradeAssignment(Assignment& assignment, uint8_t idStudent, uint8_t grade) {
    int i = 0;
    while (assignment.getAnswers()[i].getStudentId() == idStudent) {
        assignment.getAnswers()[i].setGrade(grade);
    }
}

void Teacher::sendMailsCourse(Course* course, CustomString& mailText) {
    for (uint8_t i = 0; i < course->getStudentsMembers().getSize(); i++) {
        sendMail(course->getStudentsMembers()[i], mailText);
    }
}