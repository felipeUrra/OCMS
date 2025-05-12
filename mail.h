#pragma once
#include "user.h"

class Mail {
private:
    User* sender;
    CustomString content;
    CustomString date; // it will be a class or an struct
    uint8_t time; // it will be a class or an struct;
};