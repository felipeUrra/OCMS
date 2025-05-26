// Felipe Urra Rivadeneira 0MI8000066

#include "mail.h"
#include "users/user.h"
#include <iostream>

Mail::Mail(User* sender, CustomString text) :
    sender(sender),
    text(text)
{
    getActualDateAndTime();
}

// getters and setters
User* Mail::getSender() {return this->sender;}
CustomString Mail::getText() const{return this->text;}
CustomString Mail::getDate() const{return this->date;}
CustomString Mail::getTime() const{return this->time;}

void Mail::setSender(User* sender) {this->sender = sender;}
void Mail::setText(CustomString& text) {this->text = text;}

void Mail::getActualDateAndTime() {
    time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    // date format: DD-MM-YYYY
    char buffDate[11]; // DD-MM-YYYY\0
    std::strftime(buffDate, sizeof(buffDate), "%d.%m.%Y", now);
    date = buffDate;

    // time format: HH-MM
    char buffTime[6]; // HH-MM\0
    std::strftime(buffTime, sizeof(buffTime), "%H:%M", now);
    time = buffTime;
}

void Mail::print() {
    std::cout << time << " " << date << ", sent by " << sender->getName() << " " << sender->getLastName() << ": " << text;
}