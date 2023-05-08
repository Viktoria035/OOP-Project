#pragma once
#include "User.h"
#include "MyString.h"

const size_t MAX_PHONE_NUMBER = 10;
const size_t MAX_CAR_NUMBER = 4;

class Driver :public User
{
	MyString carNumber = "0000";
	MyString phoneNumber = "0000000000";
public:
	Driver() = default;
	Driver(const MyString& username, const MyString& password,
		const MyString& lastname, const MyString& firstname,
		const MyString& type, const MyString& carNumber, const MyString& phoneNumber);

	void setCarNumber(const MyString& carNumber);
	void setPhoneNumber(const MyString& phoneNumber);

	const MyString& getCarNumber() const;
	const MyString& getPhoneNumber() const;
};