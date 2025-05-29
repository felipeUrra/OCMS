// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "../customFunctions/customString.h"
#include "../customFunctions/customVector.h"
#include "../mail.h"
#include <stdint.h>
#include <fstream>

enum class UserType {Admin = 1, Teacher = 2, Student = 3};

class User {
private:
    static int nextId;

    CustomString name;
    CustomString lastName;
    int id;
    CustomString password;
    CustomVector<Mail*> inbox;
    UserType userType;

public:
    User() = default;
    User(CustomString&, CustomString&, CustomString&, UserType);
    virtual ~User() = 0;

    // Getters and setters
    CustomString getName() const;
    CustomString getLastName() const;
    int getId() const;
    CustomString getPassword() const;
    CustomVector<Mail*>& getInbox();
    UserType getUserType() const;
    static int getNextId();

    void setName(CustomString& name);
    void setLastName(CustomString& lastName);
    void setPassword(CustomString& password);
    void setInbox(CustomVector<Mail*>& inbox);
    void setUserType(UserType userType);
    static void setNextId(int nextId);
    
    
    void sendMail(User*, const CustomString&);
    CustomString getStrUserType() const;
    void printInbox(CustomVector<User*>& users);
    bool isInboxEmpty() const;
    virtual void serialize(std::ofstream& out) const = 0;
    void serializeCommon(std::ofstream& out) const;
    void deserializeCommon(std::ifstream& in);
};