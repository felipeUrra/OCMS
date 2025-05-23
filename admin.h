// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"

class Admin : public User{
private:
    static bool adminExists;

    static void changeAdminExists(bool); // choose a better name

public:
    Admin(CustomString&, CustomString&, CustomString&);
    ~Admin() = default;

    static bool getAdminExists();

    void createUser(UserType);
    void createUser(UserType, CustomString&, CustomString&, CustomString&, CustomVector<Mail>);
    void removeUser(uint8_t);
    CustomVector<Mail> getMailsUser(User&);
};