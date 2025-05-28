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

// Serialize/deserialize
    void Answer::serialize(std::ofstream& out) const {
        int studentId = student->getId();
        out.write(reinterpret_cast<const char*>(&studentId), sizeof(studentId));
        answerText.serialize(out);
        teacherComment.serialize(out);
        out.write(reinterpret_cast<const char*>(&grade), sizeof(grade));
        out.write(reinterpret_cast<const char*>(&isGraded), sizeof(isGraded));
    }
    void Answer::deserialize(std::ifstream& in, const CustomVector<Student*>& students) {
        int studentId;
        in.read(reinterpret_cast<char*>(&studentId), sizeof(studentId));
        for (int i = 0; i < students.getSize(); i++) {
            if (students[i]->getId() == studentId) {
                this->student = students[i];
                break;
            }
        }
        answerText.deserialize(in);
        teacherComment.deserialize(in);
        in.read(reinterpret_cast<char*>(&grade), sizeof(grade));
        in.read(reinterpret_cast<char*>(&isGraded), sizeof(isGraded));
    }