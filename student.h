// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"
#include "course.h"

class Student : public User {
private:
    CustomVector<Course*> coursesEnrolled;

public:
    Student(CustomString&, CustomString&, CustomString&);
    ~Student() = default;

    // getters and setters
    CustomVector<Course*>& getCoursesEnrolled();
    void setCoursesEnrolled(CustomVector<Course*>&);

    void printAnswers(); // CourseName | AssignmentName | Grade | TeacherComment
};