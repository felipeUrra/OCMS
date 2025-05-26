// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "assignment.h"
#include "users/user.h"

class Course {
private:
    CustomString name;
    CustomString password;
    CustomVector<Assignment*> assignments;
    CustomVector<User*> studentsMembers;

public:
    Course(const CustomString&, const CustomString&);
    ~Course();

    // getters and setters
    CustomString getName() const;
    CustomString getPassword() const;
    CustomVector<Assignment*>& getAssignments();
    CustomVector<User*>& getStudentsMembers();

    void setName(CustomString&);
    void setPassword(CustomString&);
    void setAssignments(CustomVector<Assignment*>&);
    void setStudentsMembers(CustomVector<User*>&);
};