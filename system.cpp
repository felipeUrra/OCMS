// Felipe Urra Rivadeneira 0MI8000066

#include "system.h"
#include "exceptions.h"
#include "users/teacher.h"
#include "users/student.h"
#include "answer.h"
#include <iostream>

System::System() : closeSystem(false) {
    this->loggedUser = nullptr;
    this->userList = CustomVector<User*>();

    this->systemAdmin = new Admin("admin", "admin", "0000");
}

System::~System() {
    for (int i = 0; i < this->userList.getSize(); i++) {
        delete userList[i];
    }

    delete loggedUser;
    delete systemAdmin;
}

// Getters and setters
CustomVector<User*> System::getUserList() const{return this->userList;}
User* System::getLoggedUser() const{return this->loggedUser;}
Admin* System::getSystemAdmin() {return this->systemAdmin;}
bool System::getCloseSystem() const{return this->closeSystem;}

void System::setUserList(CustomVector<User*>& userList) {this->userList = userList;}
void System::setLoggedUser(User* loggedUser) {this->loggedUser = loggedUser;}
void System::setSystemAdmin(Admin* systemAdmin) {this->systemAdmin = systemAdmin;}
void System::setCloseSystem(bool closeSystem) {this->closeSystem = closeSystem;}


// Common commands
void System::login() {
    int id;
    CustomString password;

    std::cin >> id >> password;

    // while (!isdigit(id) || id < 0) {
    //     throw InvalidDataType();
    //     std::cin >> id >> password;
    // }
    
    User* user = nullptr;
    if (id == 0) {
        user = systemAdmin;
    } else {
        user = getUserById(id);
        if (user == nullptr) {
            std::cout << "There isn't user with that ID!\n";
            return;
        }
    }

    if (user->getPassword() == password) {
        this->loggedUser = user;
        user = nullptr;

        std::cout << "Login successful!\n";
        if (this->loggedUser->getUserType() != UserType::Admin) {
            std::cout << this->loggedUser->getName() << " " << this->loggedUser->getLastName() << " | " << this->loggedUser->getStrUserType() << " | " << this->loggedUser->getId() << "\n";
        }
        return;
    }

    std::cout << "Wrong password!\n";
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
        std::cout << "Password changed successfully!\n";
        return;
    }
    
    std::cout << "Wrong old password!\n"; // write something better here
}

void System::mailBox() {
    if (loggedUser->isInboxEmpty()) {
        std::cout << "No messages to show!\n";
        return;
    }
    
    this->loggedUser->printInbox();
}

void System::clearMailbox() {
    if (loggedUser->isInboxEmpty()) return;

    loggedUser->getInbox().clear();
}

void System::message() {
    int id;
    char* buffer = new char[256000];
    CustomString text;

    std::cin >> id;
    std::cin.getline(buffer, 256000);
    text = buffer;

    while (!isdigit(id) && id < 0) {
        throw InvalidDataType();
        std::cin >> id >> text;
    }

    User* addresse = getUserById(id);
    if (addresse == nullptr) {
        std::cout << "There isn't user with that ID!\n";
        return;
    }

    this->loggedUser->sendMail(addresse, text);
}

void System::quit() {this->setCloseSystem(true);}

// Admin commands
void System::addTeacher() {
    CustomString name;
    CustomString lastName;
    CustomString password;

    std::cin >> name >> lastName >> password;

    Teacher* teacher = new Teacher(name, lastName, password);
    this->userList.push_back(teacher);
    
    std::cout << "Added teacher " << name << " " << lastName << " with ID " << teacher->getId() << "!\n";
}

void System::addStudent() {
    CustomString name;
    CustomString lastName;
    CustomString password;

    std::cin >> name >> lastName >> password;

    Student* student = new Student(name, lastName, password);
    this->userList.push_back(student);
    //set the email

    std::cout << "Added student " << name << " " << lastName << " with ID " << student->getId() << "!\n";
}

void System::messageAll() {
    CustomString mailText;
    char* buffer = new char[256000]; // 256kB buffer for the mail text
    
    std::cin.getline(buffer, 256000);
    mailText = buffer;

    for (uint8_t i = 0; i < userList.getSize(); i++) {
        this->loggedUser->sendMail(userList[i], mailText);
    }
}

// Teacher commands
void System::createCourse() {
    CustomString courseName;
    CustomString password;

    std::cin >> courseName >> password;

    Teacher* t = dynamic_cast<Teacher*>(loggedUser);
    t->createCourse(courseName, password);
}

void System::addToCourse() { //solo si el estudiante no esta en el curso
    CustomString courseName;
    int studentId;

    std::cin >> courseName >> studentId;

    while (!isdigit(studentId) && studentId < 0) {
        throw InvalidDataType();
        std::cin >> courseName >> studentId;
    }

    for (uint8_t i = 0; i < this->userList.getSize(); i++) {
        if (this->userList[i]->getId() == studentId && this->userList[i]->getUserType() == UserType::Student) {
            Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);
            t->enrollStudent(t->getSpecificCourse(courseName), dynamic_cast<Student*>(this->userList[i])); // need to change this

            CustomString mailText = this->loggedUser->getName() + " " + this->loggedUser->getLastName() + " added you to " + courseName + ".\n";
            this->loggedUser->sendMail(userList[i], mailText);
            return;
        }
    }

    std::cout << "There is no student with that ID!\n";
}

void System::assignHomework() {
    CustomString courseName;
    CustomString assignmentName;

    std::cin >> courseName >> assignmentName;

    Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);

    for (uint8_t i = 0; i < t->getCourses().getSize(); i++) {
        if (t->getCourses()[i]->getName() == courseName) {
            t->createAssignment(t->getCourses()[i], assignmentName);
            std::cout << "Successfully created a new assignment!\n";
            return;
        }
    }

    std::cout << "You don't have any course with that name!\n";
}

void System::messageStudents() {
    CustomString courseName;
    char* buffer = new char[256000]; // 256kB buffer for the mail text
    CustomString mailText;

    std::cin >> courseName;
    std::cin.getline(buffer, 256000);
    mailText = buffer;

    Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);

    for (uint8_t i = 0; i < t->getCourses().getSize(); i++) {
        if (t->getCourses()[i]->getName() == courseName) {  
            for (int j = 0; j < t->getCourses()[i]->getStudentsMembers().getSize(); j++) {
                t->sendMail(t->getCourses()[i]->getStudentsMembers()[j], mailText);
            }
            return;
        }
    }

    std::cout << "You don't have any courses with that name!\n";
}

void System::viewAssignmentSubmissions() {
    CustomString courseName;
    CustomString assignmentName;

    std::cin >> courseName >> assignmentName;

    Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);

    for (uint8_t i = 0; i < t->getCourses().getSize(); i++) {
        if (t->getCourses()[i]->getName() == courseName) {
            for (uint8_t j = 0; j < t->getCourses()[i]->getAssignments().getSize(); j++) {
                if (t->getCourses()[i]->getAssignments()[j]->getName() == assignmentName) {
                    t->getCourses()[i]->getAssignments()[j]->printAnswers();
                    return;
                }
            }
            std::cout << "This course doesn't have any assignments with that name!\n";
            return;
        }
    }

    std::cout << "You don't have any courses with that name!\n";
}

void System::gradeAssignment() {
    CustomString courseName;
    CustomString assignmentName;
    uint8_t studentId;
    double grade;
    CustomString comment;

    std::cin >> courseName >> assignmentName >> studentId >> grade >> comment;

    while ((!isdigit(studentId) || studentId < 0) || (!isdigit(grade))) {
        throw InvalidDataType();
        std::cin >> courseName >> assignmentName >> studentId >> grade >> comment;
    }

    Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);

    for (uint8_t i = 0; i < t->getCourses().getSize(); i++) {
        if (t->getCourses()[i]->getName() == courseName) {
            for (uint8_t j = 0; j < t->getCourses()[i]->getAssignments().getSize(); j++) {
                if (t->getCourses()[i]->getAssignments()[j]->getName() == assignmentName) {
                    for (uint8_t k = 0; k < t->getCourses()[i]->getAssignments()[j]->getAnswers().getSize(); k++) {
                        if (t->getCourses()[i]->getAssignments()[j]->getAnswers()[k]->getStudent()->getId() == studentId) {
                            t->getCourses()[i]->getAssignments()[j]->getAnswers()[k]->setGrade(grade);
                            t->getCourses()[i]->getAssignments()[j]->getAnswers()[k]->setTeacherCommet(comment);
                            t->getCourses()[i]->getAssignments()[j]->getAnswers()[k]->setIsGraded(true);

                            for (uint8_t l = 0; l < this->userList.getSize(); l++) {
                                if (this->userList[l]->getId() == studentId) {
                                    CustomString mailText = t->getName() + " " + t->getLastName() + " graded your work on";
                                    t->sendMail(this->userList[l], mailText);
                                    return;
                                }
                            }
                        }
                    }
                    std::cout << "There is no assigment submission belonging to a student with that ID.";
                    return;
                }
            }
            std::cout << "This course doesn't have any assignments with that name!\n";
            return;
        }
    }

    std::cout << "You don't have any courses with that name!\n";    
}

// Student commands
void System::enroll() { // solo si el estudiante no esta en el cursoS
    CustomString courseName;
    CustomString coursePassword;

    std::cin >> courseName >> coursePassword;

    Student* s = dynamic_cast<Student*>(this->loggedUser);

    for (uint8_t i = 0; i < this->userList.getSize(); i++) {
        if (userList[i]->getUserType() == UserType::Teacher) {
            Teacher* t = dynamic_cast<Teacher*>(this->userList[i]);

            for (uint8_t j = 0; j < t->getCourses().getSize(); j++) {
                if (t->getCourses()[j]->getName() == courseName) {
                    if (t->getCourses()[j]->getPassword() == coursePassword) {
                        t->enrollStudent(t->getCourses()[j], s);
                        s->getCoursesEnrolled().push_back(t->getCourses()[j]);
                        std::cout << "Successfully enrolled in " + courseName + ".\n";
                        return;
                    }
                    std::cout << "Incorrect password.\n";
                    return;
                }
            }
        }
    }

    std::cout << "Theres is no course with that name!\n";
}

void System::submitAssignment() { //solo si no hay una submission del estudiante para esa tarea
    CustomString courseName;
    CustomString assignmentName;
    char* buffer = new char[256000]; // 256kB buffer for the answer text
    CustomString answerText;

    std::cin >> courseName >> assignmentName;
    std::cin.getline(buffer, 256000);
    answerText = buffer;

    Student* s = dynamic_cast<Student*>(this->loggedUser);

    for (uint8_t i = 0; i < s->getCoursesEnrolled().getSize(); i++) {
        if (s->getCoursesEnrolled()[i]->getName() == courseName) {
            for (uint8_t j = 0; j < s->getCoursesEnrolled()[i]->getAssignments().getSize(); j++) {
                if (s->getCoursesEnrolled()[i]->getAssignments()[j]->getName() == assignmentName) {
                    s->getCoursesEnrolled()[i]->getAssignments()[j]->addAnswer(s, answerText);
                    return;
                }
            }
            std::cout << "This course doesn't have any assignments with that name!\n";
            return;
        }
    }
    std::cout << "You have not enrolled in any course with this name!\n";
}

void System::grades() {
    Student* s = dynamic_cast<Student*>(this->loggedUser);
    
    s->printGradesInfo();
}

// Auxiliar functions
void System::detectCommand(CustomString& cmd) { // hacer que haga algo cuando el comando no coincide
    if(loggedUser == nullptr) {
        if(cmd == "login") {
            login();
            return;
        }
        if(cmd == "quit") {
            quit();
            return;
        }
        std::cout << "Incorrect command! Please try again.\n";
    } else {
        if (loggedUser->getUserType() == UserType::Admin) {
            if(cmd == "add_teacher") {
                addTeacher();
                return;
            }
            if(cmd == "add_student") {
                addStudent();
                return;
            }
            if(cmd == "message_all") {
                messageAll();
                return;
            }
        }

        if(loggedUser->getUserType() == UserType::Teacher) {
            if(cmd == "create_course") {
                createCourse();
                return;
            }
            if(cmd == "add_to_course") {
                addToCourse();
                return;
            }
            if(cmd == "assign_homework") {
                assignHomework();
                return;
            }
            if(cmd == "message_students") {
                messageStudents();
                return;
            }
            if(cmd == "view_assignment_submissions") {
                viewAssignmentSubmissions();
                return;
            }
            if(cmd == "grade_assignment") {
                gradeAssignment();
                return;
            }
        }

        if(loggedUser->getUserType() == UserType::Student) {
            if(cmd == "enroll") {
                enroll();
                return;
            }
            if(cmd == "submit_assignment") {
                submitAssignment();
                return;
            }
            if(cmd == "grades") {
                grades();
                return;
            }
        }
        
        if(cmd == "logout") {
            logout();
            return;
        }
        if(cmd == "change_password") {
            changePassword();
            return;
        }
        if(cmd == "mailbox") {
            mailBox();
            return;
        }
        if(cmd == "clearMailbox") {
            clearMailbox();
            return;
        }
        if(cmd == "message") {
            message();
            return;
        }
        std::cout << "Incorrect command! Please try again.\n";
    }
}

User* System::getUserById(int id) {
    for (uint8_t i = 0; i < this->userList.getSize(); i++) {
        if (this->userList[i]->getId() == id) {return userList[i];}
    }
    
    return nullptr;
}

// Serialize/deserialize
    void System::serialize(std::ofstream& out) const {
        int userCount = this->userList.getSize();
        out.write(reinterpret_cast<const char*>(&userCount), sizeof(userCount));
        for (int i = 0; i < userCount; i++) {
            int userTypeVal = static_cast<int>(this->userList[i]->getUserType());
            out.write(reinterpret_cast<const char*>(&userTypeVal), sizeof(userTypeVal));

            if 
            this->userList[i]->serialize(out);
        }

        int next = User::getNextId();
        out.write(reinterpret_cast<const char*>(&next), sizeof(next));

        //int adminId = this->systemAdmin ? this->systemAdmin->getId() : -1;
        //out.write(reinterpret_cast<const char*>(&adminId), sizeof(adminId));
    }
    void System::deserialize(std::ifstream& in) {
        // Limpiamos estado anterior
        // esto quizas si
        // for (size_t i = 0; i < userList.getSize(); ++i) {
        //     delete userList[i];
        // }
        // userList.clear();

        //delete systemAdmin;
        //systemAdmin = nullptr;

        // Leemos closeSystem
        //in.read(reinterpret_cast<char*>(&closeSystem), sizeof(closeSystem));

        // Deserialize systemAdmin
        //bool hasAdmin;
        //in.read(reinterpret_cast<char*>(&hasAdmin), sizeof(hasAdmin));
        //if (hasAdmin) {
        //    systemAdmin = new Admin();
        //    systemAdmin->deserialize(in);
        //}

        // Deserialize user list
        int userCount;
        in.read(reinterpret_cast<char*>(&userCount), sizeof(userCount));
        for (int i = 0; i < userCount; ++i) {
            int userTypeVal;
            in.read(reinterpret_cast<char*>(&userTypeVal), sizeof(userTypeVal));
            UserType type = static_cast<UserType>(userTypeVal);

            User* u = nullptr;
            if (type == UserType::Student) {
                u = new Student();
                static_cast<Student*>(u)->deserialize(in, /* allCourses */ {}); // pasa cursos si es necesario
            } else if (type == UserType::Teacher) {
                u = new Teacher();
                static_cast<Teacher*>(u)->deserialize(in, /* allCourses */ {}); // igual
            }

            if (u != nullptr) {
                userList.push_back(u);
            }
        }

        int next;
        in.read(reinterpret_cast<char*>(&next), sizeof(next));
        User::setNextId(next);
    }
