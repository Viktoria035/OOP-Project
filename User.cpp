#include "User.h"
#include "Utils.h"

User::User(const MyString& type):_type(type) {}

User::User(const MyString& type, const MyString& username, const MyString& password,
	const MyString& firstName, const MyString& lastName)
{
	setType(type);
	setUserName(username);
	setPass(password);
	setFirstName(firstName);
	setLastName(lastName);
}

User::User(const MyString& username, const MyString& password,
	const MyString& firstName, const MyString& lastName)
{
	setUserName(username);
	setPass(password);
	setFirstName(firstName);
	setLastName(lastName);
}

void User::setType(const MyString& type)
{
	if (type != "client" && type != "driver")
		throw std::invalid_argument("This type does not exists!");
	_type = type;
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

void User::setAmount(double amount)
{
	if (amount < 0)
		throw std::invalid_argument("Not valid amount!");
	this->coins = convertToCoins(amount);
}

const MyString& User::getType() const
{
	return _type;
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

size_t User::getCoins() const
{
	return coins;
}

double User::getLeva() const
{
	return convertToLeva(coins);
}

void User::addMoney(size_t amount)
{
	if (amount < 0)
		throw std::invalid_argument("Not valid amount!");
	this->coins += amount;
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
		<< ", FirstName: " << user._firstName << ", LastName: " << user._lastName;
	return os;
}

//void User::readFromFile(const char* filePath)
//{
//	std::ifstream ifs(filePath);
//	if (!ifs.is_open())
//	{
//		std::cout << "Error while openning the file";
//		return;
//	}
//	ifs >> _type;
//	ifs >> _userName;
//	ifs >> _password;
//	ifs >> _firstName;
//	ifs >> _lastName;
//}
//
//void User::writeInFile(const char* filePath)
//{
//	std::ofstream ofs(filePath, std::ios::app);
//	if (!ofs.is_open())
//	{
//		std::cout << "Error while openning the file";
//		return;
//	}
//	ofs << _type << " ";
//	ofs << _userName << " ";
//	ofs << _password << " ";
//	ofs << _firstName << " ";
//	ofs << _lastName << " ";
//	ofs << std::endl;
//}
