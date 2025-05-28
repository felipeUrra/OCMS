// Felipe Urra Rivadeneira 0MI8000066

#include "user.h"

int User::nextId = 0;

User::User(CustomString& name, CustomString& lastName, CustomString& password, UserType userType) :
    name(name),
    lastName(lastName),
    password(password),
    id(nextId++),
    userType(userType) {}

User::~User() {
    for (int i = 0; i < inbox.getSize(); i++) {
        delete inbox[i];
    }
}

CustomString User::getName() const{return name;}
CustomString User::getLastName() const{return lastName;}
int User::getId() const{return id;}
CustomString User::getPassword() const{return password;}
CustomVector<Mail*>& User::getInbox() {return inbox;}
UserType User::getUserType() const{return userType;}
int User::getNextId() {return User::nextId;}

void User::setName(CustomString& name) {this->name = name;}
void User::setLastName(CustomString& lastName) {this->lastName = lastName;}
void User::setPassword(CustomString& password) {this->password = password;}
void User::setInbox(CustomVector<Mail*>& inbox) {this->inbox = inbox;}
void User::setUserType(UserType userType) {this->userType = userType;}
void User::setNextId(int nextId) {User::nextId = nextId;}

void User::sendMail(User* addressee, const CustomString& text) {
    Mail* mail = new Mail(this, text);

    addressee->getInbox().push_back(mail);
}

CustomString User::getStrUserType() const{
    if (this->userType == UserType::Admin) {return "Administrator";}
    if (this->userType == UserType::Teacher) {return "Teacher";}
    else {return "Student";}
}

void User::printInbox() {
    for (int i = 0; i < this->inbox.getSize(); i++) {
        this->getInbox()[i]->print();
    }
}

bool User::isInboxEmpty() const{
    if (this->inbox.getSize() == 0) return true;
    return false;
}

// Serialize/deserialize
    void User::serialize(std::ofstream& out) const {
        // tengo que ver que hacer con nextID
        this->name.serialize(out);
        this->lastName.serialize(out);
        out.write(reinterpret_cast<const char*>(&this->id), sizeof(id));
        this->password.serialize(out);
        
        size_t inboxSize = this->inbox.getSize();
        out.write(reinterpret_cast<const char*>(&inboxSize), sizeof(inboxSize));
        for (int i = 0; i < inboxSize; i++) {
            this->inbox[i]->serialize(out);
        }

        out.write(reinterpret_cast<const char*>(&this->userType), sizeof(userType));
    }
    void User::deserialize(std::ifstream& in) {
        this->name.deserialize(in);
        this->lastName.deserialize(in);
        in.read(reinterpret_cast<char*>(&this->id), sizeof(id));
        this->password.deserialize(in);

        int inboxSize;
        in.read(reinterpret_cast<char*>(&inboxSize), sizeof(inboxSize));
        //this->inbox.clear();
        for (int i = 0; i < inboxSize; i++) {
            Mail* m = new Mail();
            m->deserialize(in);
            this->inbox.push_back(m);
        }
        
        in.read(reinterpret_cast<char*>(&this->userType), sizeof(userType));
    }