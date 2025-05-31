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
    void login(); //ready
    void logout(); //ready
    void changePassword(); //ready
    void mailBox(); //ready
    void clearMailbox(); //ready
    void message(); //ready
    void quit(); //ready

    //arregalar que cuando el admin manda un mensaje, escribe (Deleted user) - ready
    //que el admin no pueda cambiar su contrasennna - ready
    //arreglar las comprobaciones para el id en system - ready
    //borrar el buffer de cin - ready

    // Admin commands
    void addTeacher(); //ready
    void addStudent(); //ready
    void removeTeacher(); //ready
    void removeStudent(); //ready
    void mailboxUser(); //ready
    void messageAll(); //ready

    // Teacher commands
    void createCourse(); //ready - solo si no hay algun curso con ese nombre ya
    void addToCourse(); //ready
    void assignHomework(); //ready
    void messageStudents(); //of a specific course - ready
    void viewAssignmentSubmissions(); //ready
    void gradeAssignment(); //ready

    // Student commands
    void enroll(); //ready
    void submitAssignment(); //ready
    void grades(); //ready

    // Auxiliar functions
    void detectCommand(CustomString& cmd);
    User* getUserById(int id);
    bool isUserA(User* user, UserType role) const;

    // Serialize/deserialize
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};