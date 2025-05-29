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
    Assignment() = default;
    Assignment(CustomString&);
    ~Assignment();

    // getters and setters
    CustomVector<Answer*>& getAnswers();
    CustomString getName() const;

    void setAnswers(CustomVector<Answer*>&);
    void setName(CustomString&);

    void addAnswer(Student*, CustomString&);
    void printAnswers(CustomVector<Student*>& students); // Student Name, StudentLastName, StudentId: AnswerText

    // Serialize/deserialize
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};