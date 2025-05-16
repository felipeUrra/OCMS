// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "student.h"
#include <stdint.h>

class Answer {
private:
    uint8_t idStudent;
    CustomString text;
    uint8_t grade;

public:
    Answer();
    Answer(uint8_t, CustomString, uint8_t);
    ~Answer() = default;

    // getters and setters
    uint8_t getIdStudent() const;
    CustomString getText() const;
    uint8_t getGrade() const;

    void setIdStudent(uint8_t);
    void setText(CustomString);
    void setGrade(uint8_t);
};