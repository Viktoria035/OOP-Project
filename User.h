#pragma once
#include <fstream>
#include "MyString.h"
#include <iostream>
#include "Address.h"
class User
{
	MyString _type = "Unknown";
	MyString _userName = "Unknown";
	MyString _password = "Unknown";
	MyString _firstName = "Unknown";
	MyString _lastName = "Unknown";

	size_t coins = 0;
public:
	User() = default;
	User(const MyString& type);
	User(const MyString& type,const MyString& username, const MyString& password, 
		const MyString& firstName, const MyString& lastName);
	User(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName);

	void setType(const MyString& type);
	void setUserName(const MyString& name);
	void setPass(const MyString& pass);
	void setFirstName(const MyString& first);
	void setLastName(const MyString& last);
	void setAmount(double amount);

	const MyString& getType() const;
	const MyString& getUserName() const;
	const MyString& getPass() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;

	size_t getCoins() const;
	double getLeva() const;

	void addMoney(size_t amount);

	friend std::istream& operator>>(std::istream& is, User& user);
	friend std::ostream& operator<<(std::ostream& os, const User& user);
	virtual User* clone() const = 0;
};
