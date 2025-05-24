// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include "customFunctions/customString.h"
#include "users/user.h"

class System {
private:
    CustomVector<User*> userList;
    User* loggedUser;

public:
    System() = default;
    virtual ~System() = 0;

    // Getters and setters
    CustomVector<User*> getUserList() const;
    User* getLoggedUser() const;

    void setUserList(CustomVector<User*>&);
    void setLoggedUser(User*);

    // Common commands
    void login();
    void logout();
    void changePassword();
    void mailBox();
    void clearMailbox();
    void message();

    // Admin commands
    void addTeacher();
    void addStudent();
    void messageAll();

    // Teacher commands
    void createCourse();
    void addToCourse();
    void assignHomework();
    void messageStudents(); // of a specific course
    void viewAssignmentSubmissions();
    void gradeAssignment();

    // Student commands
    void enroll();
    void submitAssignment();
    void grades();

    // Auxiliar functions
    void detectCommand(CustomString& cmd);
};