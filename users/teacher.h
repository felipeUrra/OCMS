// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"
#include "student.h"
#include "../course.h"
#include "../customFunctions/customString.h"
#include "../customFunctions/customVector.h"

class Teacher : public User {
private:
    CustomVector<Course*> courses;

public:
    Teacher() = default;
    Teacher(CustomString&, CustomString&, CustomString&);
    ~Teacher();

    // getters and setters
    CustomVector<Course*>& getCourses();
    void setCourses(CustomVector<Course*>&);

    void createCourse(CustomString&, CustomString&);
    void createAssignment(Course*, CustomString&);
    void enrollStudent(Course*, Student*);
    Course* getCourseByName(CustomString&);

    // Serialize/deserialize
    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in);
};