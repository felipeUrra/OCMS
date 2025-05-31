// Felipe Urra Rivadeneira 0MI8000066

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
    static Course* getCourseByName(CustomString& courseName, const CustomVector<Course*>& courses);
    static bool isAllGoodWithDataEntry(int id);
    static bool isAllGoodWithDataEntry(double grade);
};

