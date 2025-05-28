// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"

class Admin : public User{
public:
    Admin() = default;
    Admin(CustomString, CustomString, CustomString);
    ~Admin() = default;

    void createUser(UserType);
    void createUser(UserType, CustomString&, CustomString&, CustomString&, CustomVector<Mail>);
    void removeUser(int);
    CustomVector<Mail*>& getMailsUser(User&);
};