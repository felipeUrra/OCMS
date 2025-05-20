// Felipe Urra Rivadeneira 0MI8000066

#include "system.h"
#include "customFunctions/customString.h"
#include <stdint.h>
#include "exceptions.h"
#include "professor.h"
#include "student.h"


// Getters and setters
CustomVector<User*> System::getUserList() const{return userList;}
User* System::getLoggedUser() const{return loggedUser;}

void System::setUserList(CustomVector<User*>& userList) {this->userList = userList;}
void System::setLoggedUser(User* loggedUser) {this->loggedUser = loggedUser;}


// Common commands
void System::login() {
    uint8_t id;
    CustomString password;

    std::cin >> id >> password;

    while (!isdigit(id) && id < 0) {
        throw InvalidDataType();
        std::cin >> id >> password;
    }
    

    for (uint8_t i = 0; i < this->userList.getSize(); i++) {
        if (id == this->userList[i]->getId()) {

            if (password == this->userList[i]->getPassword()) {
                setLoggedUser(this->userList[i]);
                std::cout << "Login successful!\n";
                return;
            }
            
            std::cout << "Wrong password! Try again.\n";
            return;
        }        
    }
    
    std::cout << "There is no user with that ID!\n";
}

void System::logout() {
    this->loggedUser = nullptr;
}

void System::changePassword() {
    CustomString oldPassword;
    CustomString newPassword;

    std::cin >> oldPassword >> newPassword;
    if (loggedUser->getPassword() == oldPassword) {
        loggedUser->setPassword(newPassword);
        std::cout << "Password changed successfully!\n";
        return;
    }
    
    std::cout << "Wrong old password!\n"; // write something better here
}

void System::mailBox() {
    if (loggedUser->getMails().getSize() == 0) {
        std::cout << "No messages to show!\n";
        return;
    }
    
    for (uint8_t i = 0; i < loggedUser->getMails().getSize(); i++) {
        this->loggedUser->getMails()[i].print();
    }
}

void System::clearMailbox() {
    if (loggedUser->getMails().getSize() == 0) {return;}

    loggedUser->getMails().clear();
}

void System::message() {
    uint8_t id;
    CustomString text;

    std::cin >> id >> text;

    while (!isdigit(id) && id < 0) {
        throw InvalidDataType();
        std::cin >> id >> text;
    }

    for (uint8_t i = 0; i < userList.getSize(); i++) {
        if (this->userList[i]->getId() == id) {
            loggedUser->sendMail(this->userList[i], text);
            return;
        }
    }

    std::cout << "There is no user with that ID!\n";
}

// Admin commands
void System::addTeacher() {
    CustomString name;
    CustomString lastName;
    CustomString password;

    std::cin >> name >> lastName >> password;

    Teacher teacher(name, lastName, password);
    this->userList.push_back(&teacher);

    std::cout << "Added teacher " << name << " " << lastName << " with ID " << teacher.getId() << "!\n";
}

void System::addStudent() {
    CustomString name;
    CustomString lastName;
    CustomString password;

    std::cin >> name >> lastName >> password;

    Student student(name, lastName, password);
    this->userList.push_back(&student);

    std::cout << "Added student " << name << " " << lastName << " with ID " << student.getId() << "!\n";
}

void System::messageAll() {
    CustomString mailText;

    std::cin >> mailText;

    for (uint8_t i = 0; i < userList.getSize(); i++) {
        this->loggedUser->sendMail(userList[i], mailText);
    }
}

// Teacher commands
void System::createCourse() {
    CustomString courseName;
    CustomString password;

    std::cin >> courseName >> password;

    Teacher* t = dynamic_cast<Teacher*>(loggedUser);
    t->createCourse(courseName, password);
}

void System::addToCourse() {
    CustomString courseName;
    uint8_t studentId;

    std::cin >> courseName >> studentId;

    while (!isdigit(studentId) && studentId < 0) {
        throw InvalidDataType();
        std::cin >> courseName >> studentId;
    }

    for (uint8_t i = 0; i < this->userList.getSize(); i++) {
        if (this->userList[i]->getId() == studentId && this->userList[i]->getUserType() == UserType::Student) {
            Teacher* t = dynamic_cast<Teacher*>(loggedUser);
            t->enrollStudent(t->getSpecificCourse(courseName), userList[i]);

            CustomString mailText = this->loggedUser->getName() + " " + this->loggedUser->getLastName() + " added you to " + courseName + ".\n";
            loggedUser->sendMail(userList[i], mailText);
            return;
        }
    }

    std::cout << "There is no student with that ID!";
}

// Auxiliar functions
void System::detectCommand(CustomString& cmd) {
    if(loggedUser == nullptr) {
        if(cmd == "login") {login();}
    }else if(loggedUser != nullptr) {
        if (loggedUser->getUserType() == UserType::Admin) {
            if(cmd == "add_teacher") {addTeacher();}
            if(cmd == "add_student") {addStudent();}
            if(cmd == "message_all") {messageAll();}
        }

        if(loggedUser->getUserType() == UserType::Teacher) {
            if(cmd == "create_course") {createCourse();}
            if(cmd == "add_to_course") {addToCourse();}
        }
        
        if(cmd == "logout") {logout();}
        if(cmd == "change_password") {changePassword();}
        if(cmd == "mailbox") {mailBox();}
        if(cmd == "clearMailbox") {clearMailbox();}
        if(cmd == "message") {message();}
    }
}