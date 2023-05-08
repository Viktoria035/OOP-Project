#include "User.h"



User::User(const MyString& username, const MyString& firstName, const MyString& lastName, const MyString& password, const MyString& type)
{
	setUserName(username);
	setFirstName(firstName);
	setLastName(lastName);
	setPass(password);
	setType(type);
}

void User::setUserName(const MyString& name)
{
	_userName = name;
}

void User::setPass(const MyString& pass)
{
	_password = pass;
}

void User::setFirstName(const MyString& first)
{
	_firstName = first;
}

void User::setLastName(const MyString& last)
{
	_lastName = last;
}

void User::setType(const MyString& type)
{
	if (type != "client" && type != "driver")
		throw std::invalid_argument("This type does not exists!");
	_type = type;
}

const MyString& User::getUserName() const
{
	return _userName;
}

const MyString& User::getPass() const
{
	return _password;
}

const MyString& User::getFirstName() const
{
	return _firstName;
}

const MyString& User::getLastName() const
{
	return _lastName;
}

const MyString& User::getType() const
{
	return _type;
}

std::istream& operator>>(std::istream& is, User& user)
{
	is >> user._type;
	is >> user._userName;
	is >> user._password;
	is >> user._firstName;
	is >> user._lastName;
	return is;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << "Type: " << user._type << ", Username: " << user._userName << ", Pass: " << user._password
		<< ", FirstName: " << user._firstName << ", LastName: " << user._lastName << std::endl;
	return os;
}

void User::saveInFile(const MyString& filePath)
{
	std::ifstream ifs((const char*)&filePath);
	if (!ifs.is_open())
	{
		std::cout << "Error while openning the file";
		return;
	}
	ifs >> _type;
	ifs >> _userName;
	ifs >> _password;
	ifs >> _firstName;
	ifs >> _lastName;
}

void User::writeInFile(const MyString& filePath)
{
	std::ofstream ofs((const char*)&filePath);
	if (!ofs.is_open())
	{
		std::cout << "Error while openning the file";
		return;
	}
	ofs << _type << " ";
	ofs << _userName << " ";
	ofs << _password << " ";
	ofs << _firstName << " ";
	ofs << _lastName << " ";
}
