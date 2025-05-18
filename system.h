#pragma once
#include "customFunctions/customString.h"
#include "user.h"

class System {
private:
    CustomVector<User> userList;
    User* loggedUser;

public:
    System() = default;
    virtual ~System() = 0;

    // Getters and setters
    CustomVector<User> getUserList() const;
    User* getLoggedUser() const;

    void setUserList(CustomVector<User>&);
    void setLoggedUser(User&);

    // Common commands
    void login();
    void logout();
    void changePassword();
    void mailBox();
    void message();
    void clearMailbox();

    // Admin commands
    void addTeacher();
    void addStudent();
    void messageAll();

    // Teacher commands
    void createCourse();
    void addToCourse();
    void enroll();
    void assignHomework();
    void messageStudents();
    void viewAssignmentSubmissions();
    void gradeAssignment();

    // Student commands
    void submitAssignment();
    void grades();

    // Auxiliar functions
    void detectCommand(CustomString& cmd);
    UserType whoIslogged(); // maybe it isn't necessary :(
};