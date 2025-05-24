// Felipe Urra Rivadeneira 0MI8000066

#include "answer.h"

Answer::Answer(Student*  owner, CustomString& answerText) : student(owner), answerText(answerText), isGraded(false) {}

// Getters and setters
Student* Answer::getStudent() {return this->student;}
CustomString Answer::getAnswerText() const{return this->answerText;}
CustomString Answer::getTeacherComment() const{return this->teacherComment;}
double Answer::getGrade() const{return this->grade;}
bool Answer::getIsGraded() const{return this->isGraded;}

void Answer::setStudent(Student* student) {this->student = student;}
void Answer::setAnswerText(CustomString& answerText) {this->answerText = answerText;}
void Answer::setTeacherCommet(CustomString& teacherComment) {this->teacherComment = teacherComment;}
void Answer::setGrade(double grade) {this->grade = grade;}
void Answer::setIsGraded(bool isGraded) {this->isGraded = isGraded;}