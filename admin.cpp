// Felipe Urra Rivadeneira 0MI8000066

#include "admin.h"

bool Admin::adminExists = false;

Admin::Admin(CustomString& name, CustomString& lastName, CustomString& password) :
    User(name, lastName, password, UserType::Admin)
{
    changeAdminExists(true);
}

// this two funcs must be changed
bool Admin::getAdminExists() {return adminExists;}
void Admin::changeAdminExists(bool adminExists) {Admin::adminExists = adminExists;} 

CustomVector<Mail*>& Admin::getMailsUser(User& user) {return user.getMails();}