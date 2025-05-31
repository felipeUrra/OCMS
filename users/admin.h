// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "user.h"

class Admin : public User{
public:
    Admin() = default;
    Admin(CustomString, CustomString, CustomString);
    ~Admin() = default;

    CustomVector<Mail*>& getMailsUser(User&);
    void serialize(std::ofstream& out) const override;
};