// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "users/user.h"
#include "users/admin.h"

class System {
private:
    CustomVector<User*> userList;
    User* loggedUser;
    Admin* systemAdmin;
    bool closeSystem;

    // Private helper functions
    void removeUserById(int id);

public:
    System();
    ~System();

    // Getters and setters
    CustomVector<User*> getUserList() const;
    User* getLoggedUser() const;
    Admin* getSystemAdmin();
    bool getCloseSystem() const;

    void setUserList(CustomVector<User*>&);
    void setLoggedUser(User*);
    void setSystemAdmin(Admin*);
    void setCloseSystem(bool);

    // Common commands
    void login();
    void logout();
    void changePassword();
    void mailBox();
    void clearMailbox();
    void message();
    void quit();

    // Admin commands
    void addTeacher();
    void addStudent();
    void removeTeacher();
    void removeStudent();
    void mailboxUser(); //of a specific user
    void messageAll();

    // Teacher commands
    void createCourse();
    void addToCourse();
    void assignHomework();
    void messageStudents(); //of a specific course
    void viewAssignmentSubmissions();
    void gradeAssignment();

    // Student commands
    void enroll();
    void submitAssignment();
    void grades();

    // Auxiliar functions
    void detectCommand(CustomString& cmd);
    User* getUserById(int id);
    bool isUserA(User* user, UserType role) const;

    // Serialize/deserialize
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};