// Felipe Urra Rivadeneira 0MI8000066

#include "assignment.h"
#include <iostream>

Assignment::Assignment(CustomString& name) : name(name) {}
Assignment::~Assignment() {
    for (uint8_t i = 0; i < answers.getSize(); i++) {
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
    for (uint8_t i = 0; i < this->answers.getSize(); i++) {
        std::cout << this->answers[i]->getStudent()->getName() << " " 
            << this->answers[i]->getStudent()->getLastName() << " "
            << this->answers[i]->getStudent()->getId() << " : "
            << this->answers[i]->getAnswerText() << "\n";
    }
}