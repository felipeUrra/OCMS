// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "student.h"
#include <stdint.h>

class Answer {
private:
    uint8_t studentId;
    CustomString answerText;
    CustomString teacherComment;
    double grade;

public:
    Answer(uint8_t, CustomString);
    ~Answer() = default;

    // getters and setters
    uint8_t getStudentId() const;
    CustomString getAnswerText() const;
    CustomString getTeacherComment() const;
    double getGrade() const;

    void setStudentId(uint8_t);
    void setAnswerText(CustomString);
    void setTeacherCommet(CustomString);
    void setGrade(double);

    void print();
};