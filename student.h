// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"
#include "course.h"

class Student : public User {
private:
    CustomVector<Course> courses; 

public:
    Student();
    Student(CustomString&, CustomString&, CustomString&, CustomVector<Mail>);
    ~Student() = default;

    // getters and setters
    CustomVector<Course>& getCourses();
    void setCourses(CustomVector<Course>&);

    void sendMail(CustomString&, uint8_t);
    void seeGrades();
};