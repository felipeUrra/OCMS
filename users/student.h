// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"
#include "../assignment.h"

class Course; // Forward declaration
class Student : public User {
private:
    CustomVector<Course*> coursesEnrolled;

public:
    Student() = default;
    Student(CustomString&, CustomString&, CustomString&);
    ~Student() = default;

    // getters and setters
    CustomVector<Course*>& getCoursesEnrolled();
    void setCoursesEnrolled(CustomVector<Course*>&);

    void printGradesInfo(); // CourseName | AssignmentName | Grade | TeacherComment
    bool hasCourse(CustomString& courseName) const;
    bool hasAssignment(CustomString& assignmentName) const;

    // Serialize/deserialize
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in, const CustomVector<Course*>& courses);
};