// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include <ctime>

class User;

class Mail {
private:
    int senderId;
    CustomString text;
    CustomString date;
    CustomString time;

public:
    Mail() = default;
    Mail(int senderId, CustomString text);
    ~Mail() = default;

    // getters and setters
    int getSenderId();
    CustomString getText() const;
    CustomString getDate() const;
    CustomString getTime() const;

    void setSenderId(int);
    void setText(CustomString&);

    void getActualDateAndTime();
    void print(User* sender);

    // Serialize/deserialize
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};