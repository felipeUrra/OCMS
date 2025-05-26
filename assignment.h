// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"

class Answer;
class Student;

class Assignment {
private:
    CustomString name;
    CustomVector<Answer*> answers;

public:
    Assignment(CustomString&);
    ~Assignment();

    // getters and setters
    CustomVector<Answer*>& getAnswers();
    CustomString getName() const;

    void setAnswers(CustomVector<Answer*>&);
    void setName(CustomString&);

    void addAnswer(Student*, CustomString&);
    void printAnswers(); // Student Name, StudentLastName, StudentId: AnswerText
};