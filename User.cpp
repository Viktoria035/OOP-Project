#include "User.h"
const char* CLIENTS_FILE = "clients.txt";
const char* DRIVERS_FILE = "drivers.txt";


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

void User::saveInFile(const char* filePath)
{
	std::ifstream ifs(filePath);
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

void User::writeInFile(const char* filePath)
{
	std::ofstream ofs(filePath);
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

void registration(User& user)
{
	MyString type;
	MyString username;
	MyString password;
	MyString firstname;
	MyString lastname;

	std::cin >> type >> username >> password >> firstname >> lastname;
	user.setType(type);
	user.setUserName(username);
	user.setFirstName(firstname);
	user.setLastName(lastname);
	user.setPass(password);
	if (type == "client")
		user.writeInFile(CLIENTS_FILE);
	else if (type == "driver")
		user.writeInFile(DRIVERS_FILE);
}

bool doesUserExists(const MyString& username, const MyString& type)
{
	if (type == "client")
	{
		std::ifstream ifs(CLIENTS_FILE);
		if (!ifs.is_open())
		{
			std::cout << "Error while openning the file";
			return false;
		}
		MyString curr;
		while (!ifs.eof())
		{
			ifs >> curr;
			if (curr == username)
				return true;
		}
		return false;
	}
	else if (type == "driver")
	{
		std::ifstream ifs(DRIVERS_FILE);
		if (!ifs.is_open())
		{
			std::cout << "Error while openning the file";
			return false;
		}
		MyString curr;
		while (!ifs.eof())
		{
			ifs >> curr;
			if (curr == username)
				return true;
		}
		return false;
	}
}

void findUser(User& user)
{
	
}