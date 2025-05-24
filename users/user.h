// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "../mail.h"
#include <stdint.h>

enum class UserType {Admin = 1, Teacher = 2, Student = 3};

class User {
private:
    static uint8_t nextId;

    CustomString name;
    CustomString lastName;
    uint8_t id;
    CustomString password;
    CustomString email;
    CustomVector<Mail*> mails;
    UserType userType;

public:
    User(CustomString&, CustomString&, CustomString&, UserType);
    virtual ~User() = 0;

    // Getters and setters
    CustomString getName() const;
    CustomString getLastName() const;
    uint8_t getId() const;
    CustomString getPassword() const;
    CustomString getEmail() const;
    CustomVector<Mail*>& getMails();
    UserType getUserType() const;

    void setName(CustomString&);
    void setLastName(CustomString&);
    void setPassword(CustomString&);
    void setEmail();
    void setMail(CustomVector<Mail*>&);
    void setUserType(UserType);
    
    
    void sendMail(User*, const CustomString&);
    CustomString getStrUserType() const;
    
};