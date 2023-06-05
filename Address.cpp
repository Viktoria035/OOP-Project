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

//std::ostream& operator<<(std::ostream& os, const Address& ad)
//{
//	if (ad.getNote() != "")
//	{
//		os << ad.getName() << ',' << ad.getNote() << ',' << ad.getCoordinates().x << "," << ad.getCoordinates().y;
//	}
//	else if (ad.getNote() == "")
//	{
//		os << ad.getName() << ',' << ad.getNote() << ',' << ad.getCoordinates().x << "," << ad.getCoordinates().y;
//	}
//	return os;
//}

//std::istream& operator>>(std::istream& is, Address& a)
//{
//	is >> a.coordinates.x;
//	is >> a.coordinates.y;
//	is >> a.name;
//	is >> a.note;
//	return is;
//}
//
//std::ostream& operator<<(std::ostream& os, const Address& a)
//{
//	std::cout << "(" << a.coordinates.x << "," << a.coordinates.y << ")" << " " << a.name << " " << a.note;
//	return os;
//}

//void registration(const MyString& type)
//{
//	if (type == "client")
//	{
//		MyString type;
//		MyString username;
//		MyString password;
//		MyString firstname;
//		MyString lastname;
//
//		Client user;
//
//		std::cin >> type >> username >> password >> firstname >> lastname;
//		user.setType(type);
//		user.setUserName(username);
//		user.setFirstName(firstname);
//		user.setLastName(lastname);
//		user.setPass(password);
//		user.writeInFile();
//	}
//	else if (type == "driver")
//		user.writeInFile();
//}

//bool doesUserExists(const MyString& username, const MyString& type)
//{
//	if (type == "client")
//	{
//		std::ifstream ifs(CLIENTS_FILE);
//		if (!ifs.is_open())
//		{
//			std::cout << "Error while openning the file";
//			return false;
//		}
//		MyString curr;
//		while (!ifs.eof())
//		{
//			ifs >> curr;
//			if (curr == username)
//				return true;
//		}
//		return false;
//	}
//	else if (type == "driver")
//	{
//		std::ifstream ifs(DRIVERS_FILE);
//		if (!ifs.is_open())
//		{
//			std::cout << "Error while openning the file";
//			return false;
//		}
//		MyString curr;
//		while (!ifs.eof())
//		{
//			ifs >> curr;
//			if (curr == username)
//				return true;
//		}
//		return false;
//	}
//	return false;
//}
