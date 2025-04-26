#pragma once
#include <iostream>
/*Source: https://github.com/Angeld55/Object-oriented_programming_FMI/tree/master/Week%2009/MyString%20(with%20move) */

class MyString
{
	char *_data;
	size_t _length;

	void copyFrom(const MyString &data);
	void free();

	void moveFrom(MyString &&other);

public:
	MyString();
	MyString(const char *data);
	MyString(const MyString &other);
	MyString &operator=(const MyString &other);
	~MyString();

	explicit MyString(size_t capacity); // for memory allocation. How much bytes to allocate

	MyString(MyString &&other) noexcept;
	MyString &operator=(MyString &&other) noexcept;

	MyString(const char *str, const char *begin, const char *end, const size_t MAX);
	size_t length() const;
	MyString &operator+=(const MyString &other);

	MyString substr(size_t begin, size_t howMany) const;

	char &operator[](size_t index);
	char operator[](size_t index) const;

	const char *c_str() const;

	friend MyString operator+(const MyString &lhs, const MyString &rhs);
	friend std::istream &operator>>(std::istream &, MyString &str);
	friend class StringPiece;
};
MyString operator+(const MyString &lhs, const MyString &rhs);

std::ostream &operator<<(std::ostream &os, const MyString &str);

std::istream &operator>>(std::istream &os, MyString &str);

bool operator<(const MyString &lhs, const MyString &rhs);
bool operator<=(const MyString &lhs, const MyString &rhs);
bool operator>=(const MyString &lhs, const MyString &rhs);
bool operator>(const MyString &lhs, const MyString &rhs);
bool operator==(const MyString &lhs, const MyString &rhs);
bool operator!=(const MyString &lhs, const MyString &rhs);