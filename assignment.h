// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "answer.h"

class Assignment {
private:
    CustomString name;
    CustomVector<Answer> answers;

public:
    Assignment();
    Assignment(CustomString&);
    ~Assignment() = default;

    // getters and setters
    CustomVector<Answer>& getAnswers();
    CustomString& getName();

    void setAnswers(CustomVector<Answer>&);
    void setName(CustomString&);

    void addAnswer(uint8_t, CustomString);
    void printAnswers();
};