#pragma once
#include <fstream>
#include "MyString.h"
#include <iostream>

class User
{
	MyString _userName = "";
	MyString _password = "";
	MyString _lastName = "";
	MyString _firstName = "";
	MyString _type = "";

public:
	User() = default;
	User(const MyString& username, const MyString& firstName, const MyString& lastName, const MyString& password, const MyString& type);

	void setUserName(const MyString& name);
	void setPass(const MyString& pass);
	void setFirstName(const MyString& first);
	void setLastName(const MyString& last);
	void setType(const MyString& type);

	const MyString& getUserName() const;
	const MyString& getPass() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	const MyString& getType() const;

	void saveInFile(const MyString& filePath);
	void writeInFile(const MyString& filePath);

	friend std::istream& operator>>(std::istream& is, User& user);
	friend std::ostream& operator<<(std::ostream& os, const User& user);
};
void registration(User& user);
bool doesUserExists(const MyString& username,const MyString& type);
//void findUser(User& user);
