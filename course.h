// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "assignment.h"

class Course {
private:
    CustomString name;
    CustomString password;
    CustomVector<Assignment*> assignments;
    CustomVector<User*> studentsMembers;

public:
    Course();
    Course(const CustomString&, const CustomString&);

    // getters and setters
    CustomString& getName() const;
    CustomString& getPassword() const;
    CustomVector<Assignment*>& getAssignments() const;
    CustomVector<User*> getStudentsMembers() const;

    void setName(CustomString&);
    void setPassword(CustomString&);
    void setAssignments(CustomVector<Assignment*>&);
    void setStudentsMembers(CustomVector<Student*>&);
};