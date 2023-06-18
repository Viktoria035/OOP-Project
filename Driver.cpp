#include "Driver.h"
#include <iostream>
#include <exception>
#include <sstream>
#include "Utils.h"

Driver::Driver():User("driver") {}

Driver::Driver(const MyString& username, const MyString& password,
	const MyString& firstname, const MyString& lastname,
	const MyString& carNumber, const MyString& phoneNumber,const Address& address):
	User(username, password,firstname,lastname)
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
		throw std::invalid_argument("Not valid phone number!");
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

void Driver::setRating(double rate)
{
	if (rate < 1 || rate > 5)
		throw std::invalid_argument("Not valid rating!");
	rating = rate;
}

void Driver::addRating(short rate)
{
	if(rate < 1 || rate > 5)
		throw std::invalid_argument("Not valid rating!");
	rating += rate;
	rating /= 2.0;
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

void Driver::writeDriverInFile(std::ofstream& ofs) const
{
	ofs << getUserName() << ",";
	ofs << getPass() << ",";
	ofs << getFirstName() << ",";
	ofs << getLastName() << ",";
	ofs << getCarNumber() << ",";
	ofs << getPhoneNumber() << ",";
	ofs << getCoins() << ",";
	ofs << (int)getStatus() << ",";
	ofs << getRating() << ",";
	ofs << getAddress().getCoordinates().x << ","
		<< getAddress().getCoordinates().y << ","
		<< getAddress().getName() << std::endl;
}

Driver Driver::readDriverFromFile(std::ifstream& ifs)
{
	static char* messages[] = { (char*)"username",(char*)"pass",(char*)"first name",(char*)"last name",
	(char*)"car number",(char*)"phone number",(char*)"amount",(char*)"status driver" ,(char*)"rating",(char*)"coordinates X",
		(char*)"coordinates Y",(char*)"address name",(char*)"note" };
	char buff[sizeof(messages) / sizeof(char*)][1024];
	char buff2[BUFF_SIZE];
	ifs.getline(buff2, BUFF_SIZE);
	std::stringstream ss(buff2);
	for (int i = 0; i < sizeof(messages) / sizeof(char*); i++)
	{
		ss.getline(buff[i], BUFF_SIZE, ',');
	}
	setUserName(buff[0]);
	setPass(buff[1]);
	setFirstName(buff[2]);
	setLastName(buff[3]);
	setCarNumber(buff[4]);
	setPhoneNumber(buff[5]);
	setAmount(fromStringToInt(buff[6]));
	setStatus(fromStringToInt(buff[7]));
	setRating(stringToDouble(buff[8]));
	setAddress(buff[11], buff[12], fromStringToInt(buff[9]), fromStringToInt(buff[10]));
	return(*this);
}

User* Driver::clone() const
{
	return new Driver(*this);
}
