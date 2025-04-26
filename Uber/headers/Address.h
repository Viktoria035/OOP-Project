#pragma once
#include "MyString.h"
struct Point
{
	int x = 0;
	int y = 0;

	int getX() const
	{
		return x;
	}
	int getY() const
	{
		return y;
	}
};

class Address
{
	MyString name = "Unknown";
	MyString note = "";
	Point coordinates = {0, 0};

public:
	Address() = default;
	Address(const MyString &name, int x, int y);
	Address(const MyString &name, const MyString &note, int x, int y);

	const MyString &getName() const;
	const MyString &getNote() const;
	const Point &getCoordinates() const;

	void setName(const MyString &name);
	void setNote(const MyString &note);
	void setPoint(int x, int y);

	double getDist(const Point &point) const;
};