#pragma once
#include "User.h"
#include "Address.h"

enum class StatusDriver
{
	Free,
	Driving
};

class Driver :public User
{
	MyString carNumber = "XX0000YY";//where X -> province code; N -> the serial code Y -> series
	MyString phoneNumber = "0000000000";
	size_t currAmount = 0;
	Address address;
	double rating = 1;
	StatusDriver status = StatusDriver::Free;
public:
	Driver();

	Driver(const MyString& type, const MyString& username, const MyString& password,
		const MyString& firstname,const MyString& lastname,
		const MyString& carNumber, const MyString& phoneNumber,const Address& address);

	void setCarNumber(const MyString& carNumber);
	void setPhoneNumber(const MyString& phoneNumber);

	void setAddress(const MyString& origin,const MyString& note, int x, int y);
	void setAddress(const Address& address);

	//void setAmount(double amount);
	void setRating(double rate);

	void setStatus(int status);
	void setStatus(const StatusDriver& status);

	const MyString& getCarNumber() const;
	const MyString& getPhoneNumber() const;
	const Address& getAddress() const;
	const StatusDriver& getStatus() const;
	double getRating() const;
	//size_t getAmount() const;

	void giveRating(double rate);
	User* clone() const override;
	//void addMoney(double leva);
};
