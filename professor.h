// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"
#include "course.h"
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"

class Teacher : public User {
private:
    CustomVector<Course*> courses;

public:
    Teacher();
    Teacher(CustomString&, CustomString&, CustomString&);
    ~Teacher() = default;

    // getters and setters
    CustomVector<Course*>& getCourses();
    void setCourses(CustomVector<Course*>&);

    void createCourse(CustomString&, CustomString&);
    void createAssignment(Course*, CustomString&);
    void enrollStudent(Course*, User*);
    Course* getSpecificCourse(CustomString&); // by courseName
    void gradeAssignment(Assignment&, uint8_t, uint8_t);
    void sendMailsCourse(Course*, CustomString&);
};