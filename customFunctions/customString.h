// Felipe Urra Rivadeneira 0MI8000066

#pragma once

class CustomString
{
private:
    char* data;

    void copyFrom(const CustomString&);
    void free();

public:
    // big four
    CustomString();
    CustomString(const CustomString&);
    CustomString& operator=(const CustomString&);
    ~CustomString();

    CustomString(const char*);

    CustomString& operator=(const char*);
    friend bool operator==(const CustomString&, const CustomString&);
    friend bool operator!=(const CustomString&, const CustomString&);

    // getters and setters
    const char* getData() const;
    void setData(const char*);
};