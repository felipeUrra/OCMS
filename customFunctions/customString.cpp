#include "customString.h"
#include <iostream>
#include <cstring>

void CustomString::copyFrom(const CustomString& other) {
    setData(other.data);
}

void CustomString::free() {
    delete[] data;
    data = nullptr;
}

void CustomString::setData(const char* data) {
    if (!data || this->data == data) return;

    this->data = new char[strlen(data) + 1];
    strcpy(this->data, data);
}

const char* CustomString::getData() const{
    return data;
}

// big four
CustomString::CustomString() : data(nullptr) {};

CustomString::CustomString(const CustomString& other) {
    copyFrom(other);
}

CustomString& CustomString::operator=(const CustomString& other) {
    if (this != &other)
    {
        free();
        copyFrom(other);   
    }
    return *this;
}

CustomString::~CustomString() {
    free();
}



CustomString::CustomString(const char* data) {
    setData(data);
}


CustomString& CustomString::operator=(const char* str) {
    setData(data);
}

bool operator==(const CustomString& lStr, const CustomString& rStr) {
    return strcmp(lStr.data, rStr.data) == 0;
}

bool operator!=(const CustomString& lStr, const CustomString& rStr) {
    return strcmp(lStr.data, rStr.data) != 0;
}