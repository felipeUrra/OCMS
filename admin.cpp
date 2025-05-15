// Felipe Urra Rivadeneira 0MI8000066

#include "admin.h"

bool Admin::adminExists = false;

Admin::Admin() : User() {changeAdminExists(true);}
Admin::Admin(CustomString& name, CustomString& lastName, CustomString& email, CustomVector<Mail> mails) :
    User(name, lastName, email, mails)
{
    changeAdminExists(true);
}

// this two funcs must be changed
bool Admin::getAdminExists() {return adminExists;}
void Admin::changeAdminExists(bool adminExists) {Admin::adminExists = adminExists;} 


void Admin::sendMail(User& user, Mail& mail) {
    getMailsUser(user).push_back(mail);    
}

CustomVector<Mail> Admin::getMailsUser(User& user) {return user.getMails();}