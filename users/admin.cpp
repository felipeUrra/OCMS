// Felipe Urra Rivadeneira 0MI8000066

#include "admin.h"

Admin::Admin(CustomString name, CustomString lastName, CustomString password) :
    User(name, lastName, password, UserType::Admin) {}

CustomVector<Mail*>& Admin::getMailsUser(User& user) {return user.getInbox();}