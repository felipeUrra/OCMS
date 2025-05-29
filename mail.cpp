// Felipe Urra Rivadeneira 0MI8000066

#include "mail.h"
#include "users/user.h"
#include <iostream>

Mail::Mail(int senderId, CustomString text) :
    senderId(senderId),
    text(text)
{
    getActualDateAndTime();
}

// getters and setters
int Mail::getSenderId() {return this->senderId;}
CustomString Mail::getText() const{return this->text;}
CustomString Mail::getDate() const{return this->date;}
CustomString Mail::getTime() const{return this->time;}

void Mail::setSenderId(int senderId) {this->senderId = senderId;}
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

void Mail::print(User* sender) {
    std::cout << time << " " << date << ", sent by " << sender->getName() << " " << sender->getLastName() << ": " << text << "\n";
}

// Serialize/deserialize
void Mail::serialize(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&senderId), sizeof(senderId));
    this->text.serialize(out);
    this->date.serialize(out);
    this->time.serialize(out);
}

void Mail::deserialize(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&senderId), sizeof(senderId));
    this->text.deserialize(in);
    this->date.deserialize(in);
    this->time.deserialize(in);
}