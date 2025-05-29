// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "users/student.h"
#include <stdint.h>
#include <fstream>

class Answer {
private:
    int studentId;
    CustomString answerText;
    CustomString teacherComment;
    double grade;
    bool isGraded;

public:
    Answer() = default;
    Answer(int, CustomString&);
    ~Answer() = default;

    // getters and setters
    int getStudentId() const;
    CustomString getAnswerText() const;
    CustomString getTeacherComment() const;
    double getGrade() const;
    bool getIsGraded() const;

    void setStudentId(int);
    void setAnswerText(CustomString&);
    void setTeacherCommet(CustomString&);
    void setGrade(double);
    void setIsGraded(bool);

    // Serialize/deserialize
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};