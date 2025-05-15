// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"

class Admin : public User{
private:
    static uint8_t adminCount;

public:
    Admin();
    Admin(CustomString&, CustomString&, CustomString&, CustomVector<Mail>);

    void createUser(UserType);
    void createUser(UserType, CustomString&, CustomString&, CustomString&, CustomVector<Mail>);
    void removeUser(uint8_t);
    void sendMail(User&, Mail&);
    CustomVector<Mail> getMailsUsers(User&);
};