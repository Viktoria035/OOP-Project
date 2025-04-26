#pragma once
#include <iostream>
#include <exception>

const size_t DEFAULT_CAPACITY = 8;

template <typename T>
class Vector
{
	T *data;
	size_t capacity;
	size_t size;

	void copyFrom(const Vector<T> &other);
	void free();
	void moveFrom(Vector<T> &&other);

	void resize();

public:
	Vector();
	Vector(const Vector<T> &other);
	Vector(Vector<T> &&other) noexcept;

	Vector<T> &operator=(const Vector<T> &other);
	Vector<T> operator=(Vector<T> &&other) noexcept;

	~Vector();

	Vector(size_t n);
	Vector(size_t n, const T &elem);

	void setCapacity(size_t capacity);

	void push_back(const T &obj);
	void push_back(T &&obj);

	T &pop_back();

	T &operator[](size_t at);
	const T &operator[](size_t at) const;

	size_t getSize() const;
	size_t getCapacity() const;

	void clear();

	bool isEmpty() const;
};

template <typename T>
void Vector<T>::setCapacity(size_t capacity)
{
	this->capacity = capacity;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T> &other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

template <typename T>
void Vector<T>::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

template <typename T>
void Vector<T>::moveFrom(Vector<T> &&other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;

	other.capacity = 0;
	other.size = 0;
	other.data = nullptr;
}

template <typename T>
void Vector<T>::resize()
{
	T *newData = new T[capacity *= 2];
	for (size_t i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
}

template <typename T>
Vector<T>::Vector()
{
	capacity = DEFAULT_CAPACITY;
	data = new T[capacity];
	size = 0;
}

template <typename T>
Vector<T>::Vector(const Vector<T> &other)
{
	copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector<T> &&other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return (*this);
}

template <typename T>
Vector<T> Vector<T>::operator=(Vector<T> &&other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return (*this);
}

template <typename T>
Vector<T>::~Vector()
{
	free();
}

template <typename T>
Vector<T>::Vector(size_t n)
{
	size = n;
	capacity = n;
	data = new T[capacity];
}

template <typename T>
Vector<T>::Vector(size_t n, const T &elem)
{
	size = n;
	capacity = n;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = elem;
	}
}

template <typename T>
void Vector<T>::push_back(const T &obj)
{
	if (size == capacity)
		resize();
	data[size++] = obj;
}

template <typename T>
void Vector<T>::push_back(T &&obj)
{
	if (size == capacity)
		resize();
	data[size++] = std::move(obj);
}

template <typename T>
T &Vector<T>::pop_back()
{
	if (isEmpty())
		throw std::out_of_range("Empty data!");
	return data[--size];
}

template <typename T>
T &Vector<T>::operator[](size_t at)
{
	return data[at];
}

template <typename T>
const T &Vector<T>::operator[](size_t at) const
{
	return data[at];
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return size;
}

template <typename T>
size_t Vector<T>::getCapacity() const
{
	return capacity;
}

template <typename T>
void Vector<T>::clear()
{
	delete[] data;
	data = new T[capacity];
	size = 0;
}

template <typename T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
}