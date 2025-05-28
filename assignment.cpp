// Felipe Urra Rivadeneira 0MI8000066

#include "assignment.h"
#include "answer.h"
#include "users/student.h"
#include <iostream>

Assignment::Assignment(CustomString& name) : name(name), answers() {}
Assignment::~Assignment() {
    for (int i = 0; i < answers.getSize(); i++) {
        delete answers[i];
    }
}

// getters and setters
CustomVector<Answer*>& Assignment::getAnswers() {return answers;}
CustomString Assignment::getName() const{return name;}

void Assignment::setAnswers(CustomVector<Answer*>& answers) {this->answers = answers;}
void Assignment::setName(CustomString& name)  {this->name = name;}

void Assignment::addAnswer(Student* s, CustomString& answerText) {
    Answer* answer = new Answer(s, answerText);
    answers.push_back(answer);
}

void Assignment::printAnswers() {
    for (int i = 0; i < this->answers.getSize(); i++) {
        std::cout << this->answers[i]->getStudent()->getName() << " " 
            << this->answers[i]->getStudent()->getLastName() << " "
            << this->answers[i]->getStudent()->getId() << " : "
            << this->answers[i]->getAnswerText() << "\n";
    }
}

// Serialize/deserialize
    void Assignment::serialize(std::ofstream& out) const {
        this->serialize(out);

        size_t ansSize = answers.getSize();
        out.write(reinterpret_cast<const char*>(&ansSize), sizeof(ansSize));
        for (int i = 0; i < ansSize; i++) {
            answers[i]->serialize(out);
        }
    }
    void Assignment::deserialize(std::ifstream& in, const CustomVector<Student*>& students) {
        this->name.deserialize(in);
        size_t ansSize;
        in.read(reinterpret_cast<char*>(&ansSize), sizeof(ansSize));
        //this->answers.clear();
        for (size_t i = 0; i < ansSize; i++) {
            Answer* ans = new Answer();
            ans->deserialize(in, students);
            answers.push_back(ans);
        }
    }