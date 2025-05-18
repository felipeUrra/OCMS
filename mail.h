// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"

class Mail {
private:
    static uint8_t nextIdMail;

    User* sender;
    uint8_t idMail;
    CustomString content;
    CustomString date; // it will be a class or an struct
    uint8_t time; // it will be a class or an struct;

public:
    Mail();
    Mail(User*, CustomString, CustomString, uint8_t);
    ~Mail() = default;

    // getters and setters
    User* getSender() const;
    uint8_t getIdMail() const;
    CustomString getContent() const;
    CustomString getDate() const;
    uint8_t getTime() const;

    void setSender(User&);
    void setContent(CustomString&);
    void setDate(CustomString&);
    void setTime(uint8_t);
};