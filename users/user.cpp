// Felipe Urra Rivadeneira 0MI8000066

#include "user.h"

uint8_t User::nextId = 0;

User::User(CustomString& name, CustomString& lastName, CustomString& password, UserType userType) :
    name(name),
    lastName(lastName),
    password(password),
    id(nextId++),
    userType(userType)
{
    setEmail();
}

CustomString User::getName() const{return name;}
CustomString User::getLastName() const{return lastName;}
uint8_t User::getId() const{return id;}
CustomString User::getPassword() const{return password;}
CustomString User::getEmail() const{return email;}
CustomVector<Mail*>& User::getMails() {return mails;}
UserType User::getUserType() const{return userType;}

void User::setName(CustomString& name) {this->name = name;}
void User::setLastName(CustomString& lastName) {this->lastName = lastName;}
void User::setPassword(CustomString& password) {this->password = password;}
void User::setEmail() {this->email = (this->name) + this->lastName + "@gmail.com";}
void User::setMail(CustomVector<Mail*>& mails) {this->mails = mails;}
void User::setUserType(UserType userType) {this->userType = userType;}

void User::sendMail(User* addressee, const CustomString& text) {
    Mail* mail = new Mail(this, text);

    addressee->getMails().push_back(mail);
}

CustomString User::getStrUserType() const{
    switch (userType)
    {
    case UserType::Admin:
        return "Admin";
        break;
    case UserType::Teacher:
        return "Teacher";
        break;
    case UserType::Student:
        return "Student";
        break;
    default:
        break;
    }
}