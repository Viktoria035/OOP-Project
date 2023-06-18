#pragma once
#include <fstream>
#include <iostream>
#include "MyString.h"
#include "Vector.hpp"

class User
{
	int coins = 0;

	MyString _type = "Unknown";
	MyString _userName = "Unknown";
	MyString _password = "Unknown";
	MyString _firstName = "Unknown";
	MyString _lastName = "Unknown";

	Vector<MyString> notifications;
public:
	User() = default;
	User(const MyString& type);
	User(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName);

	void setUserName(const MyString& name);
	void setPass(const MyString& pass);
	void setFirstName(const MyString& first);
	void setLastName(const MyString& last);
	void setAmount(int amount);

	const MyString& getType() const;
	const MyString& getUserName() const;
	const MyString& getPass() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;

	int getCoins() const;

	void addMoney(int amount);
	void addNotification(const MyString& str);
	void printAllNotifications() const;

	friend std::istream& operator>>(std::istream& is, User& user);
	friend std::ostream& operator<<(std::ostream& os, const User& user);
	virtual User* clone() const = 0;
};
