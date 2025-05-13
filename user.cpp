// Felipe Urra Rivadeneira 0MI8000066

#include "user.h"

uint8_t User::nextId = 0;

User::User() : id(nextId++) {}
User::User(CustomString& name, CustomString& lastName, CustomString& email, CustomVector<Mail> mails) :
    name(name),
    lastName(lastName),
    id(nextId++),
    mails(mails)
{
    setEmail(email);
}