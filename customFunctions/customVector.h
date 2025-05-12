#pragma once
#include <fstream>

//#define TT template <typename T>

template <typename T>
class CustomVector
{
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void resize(size_t newCapacity);

	unsigned int getNextPowerOfTwo(unsigned int n) const;
	unsigned int allocateCapacity(unsigned int n) const;

	void copyFrom(const CustomVector& other);
	void moveFrom(CustomVector&& other) noexcept;
	void free();

public:
	CustomVector();
	explicit CustomVector(size_t newSize);

	CustomVector(const CustomVector<T>& other);
	CustomVector<T>& operator=(const CustomVector<T>& other);

	CustomVector(CustomVector<T>&& other) noexcept;
	CustomVector<T>& operator=(CustomVector<T>&& other) noexcept;

	size_t getSize() const;
	size_t getCapacity() const;

	CustomVector& push_back(const T& element);
	CustomVector& push_back(T&& element);

	CustomVector& pop_back();

	CustomVector& insert(const T& element, size_t position);
	CustomVector& insert(T&& element, size_t position);

	CustomVector& remove(size_t position);

	bool isEmpty() const;

	CustomVector& clear();

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	CustomVector& operator+=(const CustomVector<T>& other);

	template <typename D>
	friend CustomVector<D> operator+(const CustomVector<D>& lhs, const CustomVector<D>& rhs);

	template <typename D>
	friend bool operator==(const CustomVector<D>& lhs, const CustomVector<D>& rhs);

	template <typename D>
	friend bool operator!=(const CustomVector<D>& lhs, const CustomVector<D>& rhs);

	template <typename D>
	friend std::istream& operator>>(std::istream& is, CustomVector<D>& vector);

	template <typename D>
	friend std::ostream& operator<<(std::ostream& os, const CustomVector<D>& vector);

	~CustomVector() noexcept;
};
