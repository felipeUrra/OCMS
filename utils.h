#pragma once

#include <fstream>
#include <iostream>
#include "system.h"
#include "customFunctions/customVector.h"
#include "users/student.h"
#include "course.h"


class Utils {
public:
    Utils() = default;
    virtual ~Utils() = 0;

    static void saveSystemState(const System& system, const CustomString& filename);
    static void loadSystemState(System& system, const CustomString& filename);
    static Student* getStudentById(int id, CustomVector<Student*>& students);
    static User* getUserById(int id, const CustomVector<User*>& users);
    //quizas no es necesaria
    static Course* getCourseByName(CustomString& courseName, const CustomVector<Course*>& courses);
};

