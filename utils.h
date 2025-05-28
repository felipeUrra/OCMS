#pragma once

#include <fstream>
#include <iostream>
#include "system.h"


class Utils {
public:
    Utils() = default;
    virtual ~Utils() = 0;

    static void saveSystemState(const System& system, const CustomString& filename);
    static void loadSystemState(System& system, const CustomString& filename);
};

