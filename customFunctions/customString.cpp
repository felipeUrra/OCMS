// Felipe Urra Rivadeneira 0MI8000066

#include "customString.h"
#include "cstring"
#include <stdexcept>

CustomString::CustomString() : CustomString("")
{
}

CustomString::CustomString(const char* data) : size(strlen(data)), capacity(allocateCapacity(size))
{
	this->data = new char[this->capacity];
	strcpy(this->data, data);
}

CustomString::CustomString(size_t newSize) : size(0), capacity(allocateCapacity(newSize))
{
	this->data = new char[this->capacity] { '\0' };
}

CustomString::CustomString(const CustomString& other)
{
	copyFrom(other);
}

CustomString& CustomString::operator=(const CustomString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

const char* CustomString::c_str() const
{
	return this->data;
}

size_t CustomString::getSize() const
{
	return this->size;
}

size_t CustomString::getCapacity() const
{
	return this->capacity;
}

// Serialize/deserialize
void CustomString::serialize(std::ofstream& out) const {
	int len = this->size;
	out.write(reinterpret_cast<const char*>(&len), sizeof(len));
	out.write(this->data, len);
}
void CustomString::deserialize(std::ifstream& in) {
	int len;
	in.read(reinterpret_cast<char*>(&len), sizeof(len));
	if (len < 0 || len > 10000) { // límite arbitrario razonable
        throw std::runtime_error("String length out of bounds");
    }

	delete[] this->data;
	this->data = new char[len + 1];
	in.read(this->data, len);
	this->data[len] = '\0';
	this->size = len;
	this->capacity = len + 1;
}


const char& CustomString::operator[](size_t idx) const
{
	return this->data[idx];
}

char& CustomString::operator[](size_t idx)
{
	return this->data[idx];
}

CustomString& CustomString::operator+=(const CustomString& other)
{
	if (getSize() + other.getSize() >= getCapacity())
	{
		resize(allocateCapacity(getSize() + other.getSize()));
	}

	strncat(this->data, other.data, other.getSize());

	this->size += other.getSize();

	return *this;
}

CustomString operator+(const CustomString& lhs, const CustomString& rhs)
{
	CustomString toReturn(lhs.getSize() + rhs.getSize());

	toReturn += lhs;
	toReturn += rhs;

	return toReturn;
}

CustomString CustomString::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > getSize()) return CustomString("");

	CustomString toReturn(howMany);
	strncat(toReturn.data, this->data + begin, howMany);
	return toReturn;
}

bool operator==(const CustomString& lhs, const CustomString& rhs)
{
	return strcmp(lhs.data, rhs.data) == 0;
}

bool operator!=(const CustomString& lhs, const CustomString& rhs)
{
	return strcmp(lhs.data, rhs.data) != 0;
}

bool operator<=(const CustomString& lhs, const CustomString& rhs)
{
	return strcmp(lhs.data, rhs.data) <= 0;
}

bool operator>=(const CustomString& lhs, const CustomString& rhs)
{
	return strcmp(lhs.data, rhs.data) >= 0;
}

bool operator<(const CustomString& lhs, const CustomString& rhs)
{
	return strcmp(lhs.data, rhs.data) < 0;
}

bool operator>(const CustomString& lhs, const CustomString& rhs)
{
	return strcmp(lhs.data, rhs.data) > 0;
}

std::istream& operator>>(std::istream& is, CustomString& other)
{
	char buff[Constants::MAX_SIZE + 1];
	is >> buff;

	size_t buffLength = strlen(buff);

	if (buffLength >= other.getCapacity())
	{
		other.resize(other.allocateCapacity(buffLength));
	}

	strcpy(other.data, buff);

	other.size = buffLength;

	return is;
}

std::ostream& operator<<(std::ostream& os, const CustomString& other)
{
	return os << other.data;
}

CustomString::~CustomString()
{
	free();
}

unsigned int CustomString::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
	{
		n &= (n - 1);
	}

	return n << 1;
}

unsigned int CustomString::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

void CustomString::resize(size_t newCapacity)
{
	this->capacity = newCapacity;

	char* newData = new char[this->capacity];
	strcpy(newData, this->data);

	delete[] this->data;
	this->data = newData;
}

void CustomString::copyFrom(const CustomString& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new char[strlen(other.data) + 1];
	strcpy(this->data, other.data);
}

void CustomString::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = this->capacity = 0;
}