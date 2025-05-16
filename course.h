// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "assignment.h"

class Course {
private:
    CustomString name;
    CustomString password;
    CustomVector<Assignment> assignments;
    CustomVector<Student> studentsMembers;

public:
    Course();
    Course(CustomString, CustomString, CustomVector<Assignment>, CustomVector<Student>);

    // getters and setters
    CustomString getName();
    CustomString getPassword();
    CustomVector<Assignment> getAssignments();
    CustomVector<Student> getStudentsMembers();

    void setName(CustomString);
    void setPassword(CustomString);
    void setAssignments(CustomVector<Assignment>);
    void setStudentsMembers(CustomVector<Student>);
};