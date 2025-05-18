// Felipe Urra Rivadeneira 0MI8000066

#include "professor.h"

Teacher::Teacher() {}
Teacher::Teacher(CustomString& name, CustomString& lastName, CustomString& email, CustomVector<Mail>& mails) :
    User(name, lastName, email, mails) {}

void Teacher::createCourse(CustomString& name, CustomString& password, CustomVector<Assignment>& assignments, CustomVector<Student>& studentsMembers) {
    Course course(name, password, assignments, studentsMembers);
    this->courses.push_back(course);
}

void Teacher::createAssignment(Course& course, CustomString& name) {
    Assignment assignment(name);
    course.getAssignments().push_back(assignment);
}

void Teacher::enrollStudent(Course& course, Student& student) {course.getStudentsMembers().push_back(student);}

void Teacher::gradeAssignment(Assignment& assignment, uint8_t idStudent, uint8_t grade) {
    int i = 0;
    while (assignment.getAnswers()[i].getIdStudent() == idStudent) {
        assignment.getAnswers()[i].setGrade(grade);
    }
}

void Teacher::sendMailsCourse(& mail, CustomString courseName) {
    int i = 0;
    while (this->courses[i].getName() == courseName) {
        for (uint8_t i = 0; i < this->courses[i].getStudentsMembers().getSize(); i++) {
            sendMail()
        }
        
    }
    
}