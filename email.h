#pragma once
#include "customFunctions/customString.h"
#include "customFunctions/customVector.h"
#include "mail.h"

class Email {
private:
    CustomString emailAddress;
    CustomVector<Mail> mails;

    CustomVector<Mail>& getMails() const; // should it go here or in public?

public:
    Email();
    Email(CustomString);
    ~Email() = default;

    // Getters and setters
    CustomString getEmailAddres() const;
    
    void setEmailAddress(CustomString);
    void setMails(CustomVector<Mail>&);
};