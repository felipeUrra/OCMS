#include "mail.h"

uint8_t Mail::nextIdMail = 0;

Mail::Mail() : sender(nullptr), idMail(nextIdMail++) {}
Mail::Mail(User* sender, CustomString content, CustomString date, uint8_t time) :
    sender(sender),
    idMail(nextIdMail++),
    content(content),
    date(date),
    time(time) {}

// getters and setters
User* Mail::getSender() const{return this->sender;}
uint8_t Mail::getIdMail() const{return this->idMail;}
CustomString Mail::getContent() const{return this->content;}
CustomString Mail::getDate() const{return this->date;}
uint8_t Mail::getTime() const{return this->time;}

void Mail::setSender(User& sender) {this->sender = &sender;}
void Mail::setContent(CustomString& content) {this->content = content;}
void Mail::setDate(CustomString& date) {this->date = date;}
void Mail::setTime(uint8_t time) {this->time = time;}