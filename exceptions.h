// Felipe Urra Rivadeneira 0MI8000066

#pragma once
#include <stdexcept>
#include <iostream>
#include "customFunctions/customString.h"

class InvalidDataType : public std::runtime_error {
public:
    InvalidDataType()
        : std::runtime_error("Invalid data type") {}
};