// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "assignment.h"
#include "users/user.h"
#include "users/student.h"

class Course {
private:
    CustomString name;
    CustomString password;
    CustomVector<Assignment*> assignments;
    CustomVector<Student*> studentsMembers;

public:
    Course() = default;
    Course(const CustomString&, const CustomString&);
    ~Course();

    // getters and setters
    CustomString getName() const;
    CustomString getPassword() const;
    CustomVector<Assignment*>& getAssignments();
    CustomVector<Student*>& getStudentsMembers();

    void setName(CustomString&);
    void setPassword(CustomString&);
    void setAssignments(CustomVector<Assignment*>&);
    void setStudentsMembers(CustomVector<Student*>&);

    bool hasAssignment(CustomString& assignmentName) const; 

    // Serialize/deserialize
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in, const CustomVector<Student*>& students);
};