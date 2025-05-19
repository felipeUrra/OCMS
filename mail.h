// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"
#include <ctime>

class Mail {
private:
    static uint8_t nextIdMail;

    User* sender;
    uint8_t idMail;
    CustomString content;
    CustomString date;
    CustomString time;

public:
    Mail();
    Mail(User*, CustomString);
    ~Mail() = default;

    // getters and setters
    User* getSender() const;
    uint8_t getIdMail() const;
    CustomString getContent() const;
    CustomString getDate() const;
    CustomString getTime() const;

    void setSender(User&);
    void setContent(CustomString&);
    //void setDate(CustomString&);
    //void setTime(CustomString&);


    void getActualDateAndTime();
    void print();
};