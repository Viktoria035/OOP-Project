#include "../headers/User.h"
#include "../headers/Utils.h"

User::User(const MyString &type) : _type(type) {}

User::User(const MyString &username, const MyString &password,
		   const MyString &firstName, const MyString &lastName)
{
	setUserName(username);
	setPass(password);
	setFirstName(firstName);
	setLastName(lastName);
}

void User::setUserName(const MyString &name)
{
	_userName = name;
}

void User::setPass(const MyString &pass)
{
	_password = pass;
}

void User::setFirstName(const MyString &first)
{
	_firstName = first;
}

void User::setLastName(const MyString &last)
{
	_lastName = last;
}

void User::setAmount(int amount)
{
	if (amount < 0)
		throw std::invalid_argument("Not valid amount!");
	this->coins = amount;
}

const MyString &User::getType() const
{
	return _type;
}

const MyString &User::getUserName() const
{
	return _userName;
}

const MyString &User::getPass() const
{
	return _password;
}

const MyString &User::getFirstName() const
{
	return _firstName;
}

const MyString &User::getLastName() const
{
	return _lastName;
}

int User::getCoins() const
{
	return coins;
}

void User::addMoney(int amount)
{
	if (amount < 0)
		throw std::invalid_argument("Not valid amount!");
	this->coins += amount;
}

std::istream &operator>>(std::istream &is, User &user)
{
	is >> user._type;
	is >> user._userName;
	is >> user._password;
	is >> user._firstName;
	is >> user._lastName;
	return is;
}

std::ostream &operator<<(std::ostream &os, const User &user)
{
	os << "Type: " << user._type << ", Username: " << user._userName << ", Pass: " << user._password
	   << ", FirstName: " << user._firstName << ", LastName: " << user._lastName;
	return os;
}

void User::addNotification(const MyString &str)
{
	notifications.push_back(str);
}

void User::printAllNotifications() const
{
	if (notifications.getSize() == 0)
		std::cout << "<Empty>" << std::endl;
	else
	{
		for (size_t i = 0; i < notifications.getSize(); i++)
		{
			std::cout << notifications[i] << std::endl;
		}
	}
}