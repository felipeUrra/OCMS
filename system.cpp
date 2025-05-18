// Felipe Urra Rivadeneira 0MI8000066

#include "system.h"
#include "customFunctions/customString.h"
#include <stdint.h>
#include <iostream>

// Getters and setters
CustomVector<User> System::getUserList() const{return userList;}
User* System::getLoggedUser() const{return loggedUser;}

void System::setUserList(CustomVector<User>& userList) {this->userList = userList;}
void System::setLoggedUser(User& loggedUser) {this->loggedUser = &loggedUser;}

// Common commands
void System::login() {
    uint8_t id;
    CustomString password;

    std::cin >> id >> password;
    for (uint8_t i = 0; i < this->userList.getSize(); i++) {
        if (id == this->userList[i].getId()) {

            if (password == this->userList[i].getPassword()) {
                setLoggedUser(this->userList[i]);
                std::cout << "Login successful!";
                return;
            }
            
            std::cout << "Wrong password! Try again.";
            return;
        }        
    }
    
    std::cout << "Wrong ID!";
}

void System::logout() {
    this->loggedUser = nullptr;
}

void System::changePassword() {
    CustomString oldPassword;
    CustomString newPassword;

    std::cin >> oldPassword >> newPassword;
    if (loggedUser->getPassword() == oldPassword) {
        loggedUser->setPassword(newPassword);
        std::cout << "Password changed successfully!";
        return;
    }
    
    std::cout << "Wrong old password!"; // write something better here
}

// Auxiliar functions
void System::detectCommand(CustomString& cmd) {
    if(cmd == "login" && loggedUser == nullptr) {login();} // add else

    if(cmd == "logout" && loggedUser != nullptr) {logout();} // add else

    if(cmd == "change_password" && loggedUser != nullptr) {changePassword();} // add else
}