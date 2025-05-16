// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"
#include "course.h"
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"

class Professor : public User {
private:
    CustomVector<Course> courses;

public:
    Professor();
    Professor(CustomString&, CustomString&, CustomString&, CustomVector<Mail>&);
    ~Professor() = default;

    void createCourse(CustomString&, CustomString&, CustomVector<Assignment>&, CustomVector<Student>&);
    void createAssignment(Course&, CustomString&);
    void enrollStudent(Course&, Student&);
    void gradeAssignment(Assignment&, uint8_t, uint8_t);
    void sendMails(Mail&, CustomVector<Course>&);
};