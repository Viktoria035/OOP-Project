#include "Address.h"
#include <iostream>
#include <exception>

Address::Address(const MyString& name, int x, int y)
{
	setName(name);
	setPoint(x, y);
}

Address::Address(const MyString& name, const MyString& note, int x, int y)
{
	setName(name);
	setNote(note);
	setPoint(x, y);
}

const MyString& Address::getName() const
{
	return name;
}

const MyString& Address::getNote() const
{
	return note;
}
const Point& Address::getCoordinates() const
{
	return coordinates;
}

void Address::setName(const MyString& name)
{
	this->name = name;
}

void Address::setNote(const MyString& note)
{
	this->note = note;
}

void Address::setPoint(int x, int y)
{
	coordinates.x = x;
	coordinates.y = y;
}

double Address::getDist(const Point& point) const
{
	double dx = coordinates.x - point.x;
	double dy = coordinates.y - point.y;

	return sqrt(dx * dx + dy * dy);
}
