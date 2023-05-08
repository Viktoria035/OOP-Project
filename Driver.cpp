#include "Driver.h"
#include <iostream>
#include <exception>

namespace
{
	bool isNumberF(char ch)
	{
		return ch >= '0' && ch <= '9';
	}

	bool isValidNumber(const MyString& arr)
	{
		bool isNumber = true;
		for (size_t i = 0; i < arr.length(); i++)
		{
			if (!isNumberF(arr[i]))
			{
				isNumber = false;
			}
		}
		return isNumber;
	}
}

Driver::Driver(const MyString& username, const MyString& password,
	const MyString& lastname, const MyString& firstname,
	const MyString& type, const MyString& carNumber, const MyString& phoneNumber):
	User(username,firstname,lastname,password,type)
{
	setCarNumber(carNumber);
	setPhoneNumber(phoneNumber);
}

void Driver::setCarNumber(const MyString& carNumber)
{
	if (carNumber.length() != MAX_CAR_NUMBER)
		throw std::length_error("Car number must be from 4 numbers!");
	if (!isValidNumber(carNumber))
		throw std::invalid_argument("Car number must be with numbers from 0 to 9!");
	this->carNumber = carNumber;
}

void Driver::setPhoneNumber(const MyString& phoneNumber)
{
	if (phoneNumber.length() != MAX_PHONE_NUMBER)
		throw std::length_error("Phone number must be from 10 numbers!");
	if (!isValidNumber(phoneNumber))
		throw std::invalid_argument("Phone number must be with numbers from 0 to 9!");
	this->phoneNumber = phoneNumber;
}

const MyString& Driver::getCarNumber() const
{
	return carNumber;
}

const MyString& Driver::getPhoneNumber() const
{
	return phoneNumber;
}