// Felipe Urra Rivadeneira 0MI8000066

#include "answer.h"

Answer::Answer(int studentId, CustomString& answerText) : studentId(studentId), answerText(answerText), isGraded(false) {}

// Getters and setters
int Answer::getStudentId() const{return this->studentId;}
CustomString Answer::getAnswerText() const{return this->answerText;}
CustomString Answer::getTeacherComment() const{return this->teacherComment;}
double Answer::getGrade() const{return this->grade;}
bool Answer::getIsGraded() const{return this->isGraded;}

void Answer::setStudentId(int studentId) {this->studentId = studentId;}
void Answer::setAnswerText(CustomString& answerText) {this->answerText = answerText;}
void Answer::setTeacherCommet(CustomString& teacherComment) {this->teacherComment = teacherComment;}
void Answer::setGrade(double grade) {this->grade = grade;}
void Answer::setIsGraded(bool isGraded) {this->isGraded = isGraded;}

// Serialize/deserialize
void Answer::serialize(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&studentId), sizeof(studentId));
    answerText.serialize(out);
    teacherComment.serialize(out);
    out.write(reinterpret_cast<const char*>(&grade), sizeof(grade));
    out.write(reinterpret_cast<const char*>(&isGraded), sizeof(isGraded));
}

void Answer::deserialize(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&studentId), sizeof(studentId));
    answerText.deserialize(in);
    teacherComment.deserialize(in);
    in.read(reinterpret_cast<char*>(&grade), sizeof(grade));
    in.read(reinterpret_cast<char*>(&isGraded), sizeof(isGraded));
}