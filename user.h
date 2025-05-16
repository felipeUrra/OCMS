// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "mail.h"
#include <stdint.h>

enum class UserType {Admin = 1, Professor = 2, Student = 3};

class User {
private:
    static uint8_t nextId;

    CustomString name;
    CustomString lastName;
    uint8_t id;
    CustomString email;
    CustomVector<Mail> mails;

public:
    User();
    User(CustomString&, CustomString&, CustomString&, CustomVector<Mail>);
    virtual ~User() = 0;

    // Getters and setters
    CustomString getName() const;
    CustomString getLastName() const;
    uint8_t getId() const;
    CustomString getEmail() const;
    CustomVector<Mail> getMails() const;

    void setName(CustomString&);
    void setLastName(CustomString&);
    void setEmail(CustomString&);
    void setMail(CustomVector<Mail>&);
};