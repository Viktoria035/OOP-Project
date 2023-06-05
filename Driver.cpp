#include "Driver.h"
#include <iostream>
#include <exception>
#include <sstream>
#include "Utils.h"

Driver::Driver():User("driver") {}

Driver::Driver(const MyString& type,const MyString& username, const MyString& password,
	const MyString& firstname, const MyString& lastname,
	const MyString& carNumber, const MyString& phoneNumber,const Address& address):
	User(type,username, password,firstname,lastname)
{
	setCarNumber(carNumber);
	setPhoneNumber(phoneNumber);
	setAddress(address);
}

void Driver::setCarNumber(const MyString& carNumber)
{
	if (!isValidCarNumber(carNumber))
		throw std::invalid_argument("Not valid car number!");
	this->carNumber = carNumber;
}

void Driver::setPhoneNumber(const MyString& phoneNumber)
{
	if (!isValidPhoneNumber(phoneNumber))
		throw std::invalid_argument("Phone number must be with digits from 0 to 9!");
	this->phoneNumber = phoneNumber;
}

void Driver::setAddress(const MyString& origin,const MyString& note, int x, int y)
{
	address.setName(origin);
	address.setNote(note);
	address.setPoint(x, y);
}

void Driver::setAddress(const Address& address)
{
	this->address = address;
}

//void Driver::setAmount(double amount)
//{
//	if (amount < 0)
//		throw std::invalid_argument("Not valid amount!");
//
//	currAmount = convertToCoins(amount);
//}

void Driver::setRating(double rate)
{
	if (rate < 1 || rate > 5)
		throw std::invalid_argument("Not valid rating!");
	rating = rate;
	//round(rating);
}

const MyString& Driver::getCarNumber() const
{
	return carNumber;
}

const MyString& Driver::getPhoneNumber() const
{
	return phoneNumber;
}

const Address& Driver::getAddress() const
{
	return address;
}

//Driver::Driver(const Driver& other):User(other)
//{
//	carNumber = other.carNumber;
//	phoneNumber = other.phoneNumber;
//	currAmount = other.currAmount;
//	status = other.status;
//	address = other.address;
//	rating = other.rating;
//}

//size_t Driver::getAmount() const
//{
//	return currAmount;
//}

void Driver::setStatus(int status)
{
	if (status == 0)
		this->status = StatusDriver::Free;
	else if (status == 1)
		this->status = StatusDriver::Driving;
	else
		throw std::invalid_argument("Not valid driver status!");
}

void Driver::setStatus(const StatusDriver& status)
{
	this->status = status;
}

const StatusDriver& Driver::getStatus() const
{
	return status;
}

double Driver::getRating() const
{
	return rating;
}

//void Driver::addMoney(double leva)//
//{
//	size_t coins = convertToCoins(leva);
//	if (coins < 0)
//		throw std::invalid_argument("Not valid amount!");
//	currAmount += coins;
//}

void Driver::giveRating(double rate)
{
	if (rate < 1 || rate > 5)
		throw std::invalid_argument("Not valid rating!");
	rating += rate;
	rating /= 2;
	//round(rating);
}

User* Driver::clone() const
{
	return new Driver(*this);
}
