// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include <ctime>

class User;

class Mail {
private:
    User* sender;
    CustomString text;
    CustomString date;
    CustomString time;

public:
    Mail() = default;
    Mail(User*, CustomString);
    ~Mail() = default;

    // getters and setters
    User* getSender();
    CustomString getText() const;
    CustomString getDate() const;
    CustomString getTime() const;

    void setSender(User*);
    void setText(CustomString&);

    void getActualDateAndTime();
    void print();

    // Serialize/deserialize
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};