// Felipe Urra Rivadeneira 0MI8000066

#include "user.h"

uint8_t User::nextId = 0;

User::User() : id(nextId++) {}
User::User(CustomString& name, CustomString& lastName, CustomString& email, CustomVector<Mail> mails) :
    name(name),
    lastName(lastName),
    id(nextId++),
    mails(mails)
{
    setEmail(email);
}

CustomString User::getName() const{return name;}
CustomString User::getLastName() const{return lastName;}
uint8_t User::getId() const{return id;}
CustomString User::getEmail() const{return email;}
CustomVector<Mail> User::getMails() const{return mails;};

void User::setName(CustomString& name) {this->name = name;}
void User::setLastName(CustomString& lastName) {this->lastName = lastName;}
void User::setEmail(CustomString& email) {
    this->email = email; // i will have to verify if the paremeter has required format
}
void User::setMail(CustomVector<Mail>& mails) {this->mails = mails;}
