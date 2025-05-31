// Felipe Urra Rivadeneira 0MI8000066

#include "system.h"
#include "users/teacher.h"
#include "users/student.h"
#include "answer.h"
#include "utils.h"
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

    if (!Utils::isAllGoodWithDataEntry(id)) return;
    
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
    
    std::cout << "Wrong old password!\n";
}

void System::mailBox() {
    if (loggedUser->isInboxEmpty()) {
        std::cout << "No messages to show!\n";
        return;
    }
    
    this->loggedUser->printInbox(this->userList, this->systemAdmin);
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

    if (!Utils::isAllGoodWithDataEntry(id)) return;

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

    std::cout << "Added student " << name << " " << lastName << " with ID " << student->getId() << "!\n";
}

void System::removeTeacher() {
    int id;

    std::cin >> id;

    if (!Utils::isAllGoodWithDataEntry(id)) return;

    User* u = getUserById(id);
    if (u == nullptr) {
        std::cout << "There is no user with that ID!\n";
        return;
    }

    if (u->getUserType() == UserType::Admin) {
        std::cout << "You can't remove the system administrator!\n";
        return;
    }

    Teacher* teacher = dynamic_cast<Teacher*>(u);

    for (int i = 0; i < teacher->getCourses().getSize(); i++) {
        Course* course = teacher->getCourses()[i];
        for (int j = 0; j < course->getStudentsMembers().getSize(); j++) {
            Student* student = course->getStudentsMembers()[j];

            for (int k = 0; k < student->getCoursesEnrolled().getSize(); k++) {
                if (student->getCoursesEnrolled()[k]->getName() == course->getName()) {
                    student->getCoursesEnrolled().remove(k);
                    break;
                }
            }
        }
    }
    

    removeUserById(id);
}

void System::removeStudent() {
    int id;

    std::cin >> id;

    if (!Utils::isAllGoodWithDataEntry(id)) return;

    User* u = Utils::getUserById(id, this->userList);
    if (u == nullptr) {
        std::cout << "There is no user with that ID!\n";
        return;
    }

    if (u->getUserType() != UserType::Student) {
        std::cout << "This user is not a student!\n";
        delete u;
        return;
    }

    // Remove the student from all courses they are enrolled in
    Student* s = dynamic_cast<Student*>(u);

    for (int i = 0; i < s->getCoursesEnrolled().getSize(); i++) {
        Course* course = s->getCoursesEnrolled()[i];
        for (int j = 0; j < course->getAssignments().getSize(); j++) {
            Assignment* assignment = course->getAssignments()[j];
            for (int k = 0; k < assignment->getAnswers().getSize(); k++) {
                Answer* answer = assignment->getAnswers()[k];
                if (answer->getStudentId() == s->getId()) {
                    delete answer;
                    assignment->getAnswers().remove(k);
                    break;
                }
            }
        }

        for (int j = 0; j < course->getStudentsMembers().getSize(); j++) {
            if (course->getStudentsMembers()[j]->getId() == s->getId()) {
                course->getStudentsMembers().remove(j);
            }
        }
    }
    // Remove the student from the user list
    removeUserById(id);
}

void System::mailboxUser() {
    int id;

    std::cin >> id;

    if (!Utils::isAllGoodWithDataEntry(id)) return;

    User* u = getUserById(id);
    if (u == nullptr) {
        std::cout << "There is no user with that ID!\n";
        return;
    }

    u->printInbox(this->userList, this->systemAdmin);
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

    for (int i = 0; i < this->userList.getSize(); i++) {
        if (this->userList[i]->getUserType() == UserType::Teacher) {
            Teacher* t = dynamic_cast<Teacher*>(userList[i]);
            if (t->getCourseByName(courseName) != nullptr) {
                std::cout << "There is already one course with that name!\n";
                return;
            }
        }
    }
    
    Teacher* t = dynamic_cast<Teacher*>(loggedUser);
    if (t->getCourseByName(courseName) != nullptr) {
        std::cout << "You already have one course with that name!\n";
        return;
    }
    
    t->createCourse(courseName, password);
}

void System::addToCourse() {
    CustomString courseName;
    int studentId;

    std::cin >> courseName >> studentId;

    if (!Utils::isAllGoodWithDataEntry(studentId)) return;

    User* u = getUserById(studentId);
    if (u == nullptr) {
        std::cout << "There is no user with that ID!\n";
        return;
    }

    Student* s;
    if (isUserA(u, UserType::Student)) {
        s = dynamic_cast<Student*>(u);

        if (s->hasCourse(courseName)){
            std::cout << "That student is already in this course!\n";
            return;
        }
        
        Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);
        Course* c = t->getCourseByName(courseName);
        if (c == nullptr) {
            std::cout << "You don't have any course with that name!\n";
            return;
        }
        
        t->enrollStudent(t->getCourseByName(courseName), s);

        CustomString mailText = this->loggedUser->getName() + " " + this->loggedUser->getLastName() + " added you to " + courseName;
        this->loggedUser->sendMail(s, mailText);
        return;
    }
    
    std::cout << "There is no student with that ID!\n";
}

void System::assignHomework() {
    CustomString courseName;
    CustomString assignmentName;

    std::cin >> courseName >> assignmentName;

    Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);

    Course* course = t->getCourseByName(courseName);
    if (course == nullptr) {
        std::cout << "You don't have any course with that name!\n";
        return;
    }

    if (course->hasAssignment(assignmentName)) {
        std::cout << "This course already has an assignment with that name!\n";
        return;
    }

    t->createAssignment(course, assignmentName);
    std::cout << "Successfully created a new assignment!\n";
}

void System::messageStudents() {
    CustomString courseName;
    char* buffer = new char[256000]; // 256kB buffer for the mail text
    CustomString mailText;

    std::cin >> courseName;
    std::cin.getline(buffer, 256000);
    mailText = buffer;

    Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);

    Course* course = t->getCourseByName(courseName);
    if (course == nullptr) {
        std::cout << "You don't have any courses with that name!\n";
        return;
    }

    for (int i = 0; i < course->getStudentsMembers().getSize(); i++) {
        t->sendMail(course->getStudentsMembers()[i], mailText);
    }
}

void System::viewAssignmentSubmissions() {
    CustomString courseName;
    CustomString assignmentName;

    std::cin >> courseName >> assignmentName;

    Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);

    Course* course = t->getCourseByName(courseName);
    if (course == nullptr) {
        std::cout << "You don't have any courses with that name!\n";
        return;
    }
    
    Assignment* assignment = course->getAssignmentByName(assignmentName);
    if (assignment == nullptr) {
        std::cout << "This course doesn't have any assignments with that name!\n";
        return;
    }

    assignment->printAnswers(course->getStudentsMembers());
}

void System::gradeAssignment() {
    CustomString courseName;
    CustomString assignmentName;
    int studentId;
    double grade;
    char* buffer = new char[256000];
    CustomString comment;

    std::cin >> courseName >> assignmentName >> studentId;
    if (!Utils::isAllGoodWithDataEntry(studentId)) return;

    std::cin >> grade;
    if (!Utils::isAllGoodWithDataEntry(grade)) return;

    std::cin.getline(buffer, 256000);
    comment = buffer;

    Teacher* t = dynamic_cast<Teacher*>(this->loggedUser);
    Course* c = t->getCourseByName(courseName);
    if (c == nullptr) {
        std::cout << "You don't have any courses with that name!\n";
        return;
    }

    Assignment* assignment = c->getAssignmentByName(assignmentName);
    if (assignment == nullptr) {
        std::cout << "This course doesn't have any assignments with that name!\n";
        return;
    }

    Answer* answer = assignment->getAnswerByStudentId(studentId);
    if (answer == nullptr) {
        std::cout << "There is no assigment submission belonging to a student with that ID.\n";
        return;
    }

    if (answer->getIsGraded()) {
        std::cout << "This assignment has already been graded!\n";
        return;
    }
    
    answer->setGrade(grade);
    answer->setTeacherCommet(comment);
    answer->setIsGraded(true);

    CustomString mailText = t->getName() + " " + t->getLastName() + " graded your work on " + assignment->getName() + " in " + courseName;
    Student* s = Utils::getStudentById(studentId, c->getStudentsMembers());
    t->sendMail(s, mailText); 
}

// Student commands
void System::enroll() {
    CustomString courseName;
    CustomString coursePassword;

    std::cin >> courseName >> coursePassword;

    Student* s = dynamic_cast<Student*>(this->loggedUser);

    for (uint8_t i = 0; i < this->userList.getSize(); i++) {
        if (userList[i]->getUserType() == UserType::Teacher) {
            Teacher* t = dynamic_cast<Teacher*>(this->userList[i]);

            Course* c = t->getCourseByName(courseName);
            if (c == nullptr) {
                continue;
            }
            
            if (c->getPassword() == coursePassword) {
                if (s->hasCourse(courseName)) {
                    std::cout << "You are already enrolled in that course!\n";
                    return;
                }
                
                t->enrollStudent(c, s);
                s->getCoursesEnrolled().push_back(c);
                std::cout << "Successfulle enrolled in " + courseName + ".\n";
                return;
            }
            
            std::cout << "Incorrect password.\n";
            return;
        }
    }

    std::cout << "There is no course with that name!\n";
}

void System::submitAssignment() {
    CustomString courseName;
    CustomString assignmentName;
    char* buffer = new char[256000]; // 256kB buffer for the answer text
    CustomString answerText;

    std::cin >> courseName >> assignmentName;
    std::cin.getline(buffer, 256000);
    answerText = buffer;

    Student* s = dynamic_cast<Student*>(this->loggedUser);
    Course* c = Utils::getCourseByName(courseName, s->getCoursesEnrolled());
    if (c == nullptr) {
        std::cout << "You have not enrolled in any course with this name!\n";
        return;
    }

    Assignment* a = c->getAssignmentByName(assignmentName);
    if (a == nullptr) {
        std::cout << "This course doesn't have any assignments with that name!\n";
        return;
    }

    if (a->hasAnswerOfStudent(s->getId())) {
        std::cout << "You have already submitted an answer for this assignment!\n";
        return;
    }
    
    a->addAnswer(s, answerText);
}

void System::grades() {
    Student* s = dynamic_cast<Student*>(this->loggedUser);
    
    s->printGradesInfo();
}

// Auxiliar functions
void System::detectCommand(CustomString& cmd) {
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
            if(cmd == "remove_teacher") {
                removeTeacher();
                return;
            }
            if (cmd == "remove_student") {
                removeStudent();
                return;
            }
            if (cmd == "mailbox_user") {
                mailboxUser();
                return;
            }
            if(cmd == "message_all") {
                messageAll();
                return;
            }
        }

        if(loggedUser->getUserType() == UserType::Teacher) {
            if(cmd == "change_password") {
                changePassword();
                return;
            }    
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
            if(cmd == "change_password") {
                changePassword();
                return;
            }            
            
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
        if(cmd == "mailbox") {
            mailBox();
            return;
        }
        if(cmd == "clear_mailbox") {
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

bool System::isUserA(User* user, UserType role) const {
    if (user->getUserType() == role) return true;
    return false;
}

// Serialize/deserialize
void System::serialize(std::ofstream& out) const {
    int userCount = this->userList.getSize();
    out.write(reinterpret_cast<const char*>(&userCount), sizeof(userCount));
    for (int i = 0; i < userCount; i++) {
        if (userList[i]->getUserType() == UserType::Student) continue;

        int userTypeVal = static_cast<int>(this->userList[i]->getUserType());
        out.write(reinterpret_cast<const char*>(&userTypeVal), sizeof(userTypeVal));
        this->userList[i]->serialize(out);
    }

    for (int i = 0; i < userCount; i++) {
        if (userList[i]->getUserType() == UserType::Teacher) continue;

        int userTypeVal = static_cast<int>(this->userList[i]->getUserType());
        out.write(reinterpret_cast<const char*>(&userTypeVal), sizeof(userTypeVal));
        this->userList[i]->serialize(out);
    }

    int nextId = User::getNextId();
    out.write(reinterpret_cast<const char*>(&nextId), sizeof(nextId));
}

void System::deserialize(std::ifstream& in) {
    // Deserialize user list
    int userCount;
    in.read(reinterpret_cast<char*>(&userCount), sizeof(userCount));
    CustomVector<Course*> allCourses;
    for (int i = 0; i < userCount; i++) {
        int userTypeVal;
        in.read(reinterpret_cast<char*>(&userTypeVal), sizeof(userTypeVal));
        UserType type = static_cast<UserType>(userTypeVal);

        User* u = nullptr;
        if (type == UserType::Teacher) {
            u = new Teacher();
            dynamic_cast<Teacher*>(u)->deserialize(in);
            allCourses += dynamic_cast<Teacher*>(u)->getCourses();
        } else {
            u = new Student();
            dynamic_cast<Student*>(u)->deserialize(in, allCourses);
        }

        if (u != nullptr) {
            userList.push_back(u);
        }
    }

    int n;
    in.read(reinterpret_cast<char*>(&n), sizeof(n));
    User::setNextId(n);
}

void System::removeUserById(int id) {
    for (int i = 0; i < userList.getSize(); i++) {
        if (userList[i]->getId() == id) {
            userList.remove(i);
            std::cout << "Removed user with ID " << id << "!\n";
            return;
        }
    }
}