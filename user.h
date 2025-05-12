// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "email.h"
#include <stdint.h>

class User {
private:
    CustomString name;
    CustomString lastName;
    uint8_t id;
    Email email;

public:
    User();
    User(CustomString, CustomString, uint8_t, CustomString);
    virtual ~User() = 0;

    // Getters and setters
    CustomString getName() const;
    CustomString getLastName() const;
    uint8_t getId() const;
    Email& getEmail() const;

    void setName(CustomString&);
    void setLastName(CustomString&);
    void setId(uint8_t);
    void setEmail(Email&);
};