// Felipe Urra Rivadeneira 0MI8000066

#include "professor.h"

Professor::Professor() {}
Professor::Professor(CustomString& name, CustomString& lastName, CustomString& email, CustomVector<Mail>& mails) :
    User(name, lastName, email, mails) {}

void Professor::createCourse(CustomString& name, CustomString& password, CustomVector<Assignment>& assignments, CustomVector<Student>& studentsMembers) {
    Course course(name, password, assignments, studentsMembers);
    this->courses.push_back(course);
}

void Professor::createAssignment(Course& course, CustomString& name) {
    Assignment assignment(name);
    course.getAssignments().push_back(assignment);
}

void Professor::enrollStudent(Course& course, Student& student) {course.getStudentsMembers().push_back(student);}

void Professor::gradeAssignment(Assignment& assignment, uint8_t idStudent, uint8_t grade) {
    int i = 0;
    while (assignment.getAnswers()[i].getIdStudent() == idStudent) {
        assignment.getAnswers()[i].setGrade(grade);
    }
}