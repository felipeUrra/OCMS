// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"
#include "course.h"

class Student : public User {
private:
    //CustomVector<Answer*> answers;
    CustomVector<Course*> coursesEnrolled; // cambiar las cosas que usas answers, para que usen este atributo

public:
    Student();
    Student(CustomString&, CustomString&, CustomString&);
    ~Student() = default;

    // getters and setters
    CustomVector<Course*>& getCoursesEnrolled();

    void setCoursesEnrolled();

    void sendMail(CustomString&, uint8_t);
    void printAnswers();
};