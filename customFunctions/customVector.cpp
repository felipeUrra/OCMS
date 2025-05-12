// Felipe Urra Rivadeneira 0MI8000066

#include "customVector.h"
#include <iostream>

template <typename T>
inline CustomVector<T>::CustomVector() : CustomVector(4) {}

template <typename T>
inline CustomVector<T>::CustomVector(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->data = new T[this->capacity]{ };
}

template <typename T>
inline CustomVector<T>::CustomVector(const CustomVector<T>& other)
{
	copyFrom(other);
}

template <typename T>
inline CustomVector<T>& CustomVector<T>::operator=(const CustomVector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <typename T>
inline CustomVector<T>::CustomVector(CustomVector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
inline CustomVector<T>& CustomVector<T>::operator=(CustomVector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <typename T>
inline size_t CustomVector<T>::getSize() const
{
	return this->size;
}

template <typename T>
inline size_t CustomVector<T>::getCapacity() const
{
	return this->capacity;
}

template <typename T>
inline CustomVector<T>& CustomVector<T>::push_back(const T& element)
{
	if (getSize() >= getCapacity())
	{
		resize(getCapacity() * 2);
	}

	this->data[size++] = element;

	return *this;
}

template <typename T>
inline CustomVector<T>& CustomVector<T>::push_back(T&& element)
{
	if (getSize() >= getCapacity())
	{
		resize(getCapacity() * 2);
	}

	this->data[size++] = std::move(element);

	return *this;
}

template <typename T>
inline CustomVector<T>& CustomVector<T>::pop_back()
{
	if (getSize())
	{
		this->size--;
	}
	else
	{
		return *this;
	}

	if ((getSize() * 4) <= getCapacity() && getCapacity() > 1)
	{
		resize(getCapacity() / 2);
	}

	return *this;
}

template <typename T>
inline CustomVector<T>& CustomVector<T>::insert(const T& element, size_t position)
{
	if (position > size)
	{
		return *this;
	}

	if (getSize() >= getCapacity())
	{
		resize(getCapacity() * 2);
	}

	for (int i = size; i > position; i--) {
		this->data[i] = this->data[i - 1];
	}

	this->data[position] = element;
	this->size++;

	return *this;
}

template <typename T>
inline CustomVector<T>& CustomVector<T>::insert(T&& element, size_t position)
{
	if (position > size)
	{
		return *this;
	}

	if (getSize() >= getCapacity())
	{
		resize(getCapacity() * 2);
	}

	for (int i = size; i > position; i--) {
		this->data[i] = this->data[i - 1];
	}

	this->data[position] = std::move(element);
	this->size++;

	return *this;
}

template <typename T>
inline CustomVector<T>& CustomVector<T>::remove(size_t position)
{
	if (position > size)
	{
		return *this;
	}

	for (size_t i = position + 1; i < getSize(); i++)
	{
		this->data[i - 1] = this->data[i];
	}

	this->size--;

	if ((getSize() * 4) <= getCapacity() && getCapacity() > 1)
	{
		resize(getCapacity() / 2);
	}

	return *this;
}

template <typename T>
inline bool CustomVector<T>::isEmpty() const
{
	return getSize() == 0;
}

template <typename T>
inline CustomVector<T>& CustomVector<T>::clear()
{
	this->size = 0;
	return *this;
}

template <typename T>
inline const T& CustomVector<T>::operator[](size_t index) const
{
	return this->data[index];
}

template <typename T>
inline T& CustomVector<T>::operator[](size_t index)
{
	return this->data[index];
}

template <typename T>
CustomVector<T>& CustomVector<T>::operator+=(const CustomVector<T>& other)
{
	size_t newSize = getSize() + other.getSize();

	if (getCapacity() < newSize)
	{
		resize(getNextPowerOfTwo(newSize));
	}

	for (size_t i = 0; i < other.getSize(); i++)
	{
		this->data[getSize() + i] = other.data[i];
	}

	this->size = newSize;

	return *this;
}

template <typename D>
CustomVector<D> operator+(const CustomVector<D>& lhs, const CustomVector<D>& rhs)
{
	CustomVector<D> toReturn(lhs.getSize() + rhs.getSize());

	toReturn += lhs;
	toReturn += rhs;

	return toReturn;
}

template <typename D>
bool operator==(const CustomVector<D>& lhs, const CustomVector<D>& rhs)
{
	if (lhs.size != rhs.size) return false;

	for (int i = 0; i < lhs.size; i++)
	{
		if (lhs.data[i] != rhs.data[i])
		{
			return false;
		}
	}

	return true;
}

template <typename D>
bool operator!=(const CustomVector<D>& lhs, const CustomVector<D>& rhs)
{
	return !(lhs == rhs);
}

template <typename D>
inline std::istream& operator>>(std::istream& is, CustomVector<D>& vector)
{
	is >> vector.size;
	vector.resize(vector.allocateCapacity(vector.getSize()));

	for (size_t i = 0; i < vector.getSize(); i++)
	{
		is >> vector.data[i];
	}

	return is;
}

template <typename D>
inline std::ostream& operator<<(std::ostream& os, const CustomVector<D>& vector)
{
	for (size_t i = 0; i < vector.getSize(); i++)
	{
		os << vector.data[i] << " ";
	}

	os << std::endl;
	return os;
}

template <typename T>
inline CustomVector<T>::~CustomVector() noexcept
{
	free();
}

template <typename T>
inline void CustomVector<T>::resize(size_t newCapacity)
{
	T* newData = new T[newCapacity];
	for (size_t i = 0; i < getSize(); i++)
	{
		newData[i] = this->data[i];
	}

	delete[] this->data;
	this->data = newData;
	this->capacity = newCapacity;
}

template <typename T>
inline void CustomVector<T>::copyFrom(const CustomVector<T>& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new T[this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
	{
		this->data[i] = other.data[i];
	}
}

template <typename T>
inline void CustomVector<T>::moveFrom(CustomVector<T>&& other) noexcept
{
	this->data = other.data;
	this->size = other.size;
	this->capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template <typename T>
inline void CustomVector<T>::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = this->capacity = 0;
}

template <typename T>
inline unsigned int CustomVector<T>::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
	{
		n &= (n - 1);
	}

	return n << 1;
}

template <typename T>
inline unsigned int CustomVector<T>::allocateCapacity(unsigned int n) const
{
	return std::max(getNextPowerOfTwo(n + 1), 8u);
}