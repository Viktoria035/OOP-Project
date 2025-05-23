#pragma once
#include "User.h"
#include "Address.h"

enum class StatusDriver
{
	Free,
	Driving
};

class Driver : public User
{
	MyString carNumber = "XX0000YY"; // where X -> province code; N -> the serial code Y -> series
	MyString phoneNumber = "0000000000";
	Address address;
	double rating = 1;
	StatusDriver status = StatusDriver::Free;

public:
	Driver();

	Driver(const MyString &username, const MyString &password,
		   const MyString &firstname, const MyString &lastname,
		   const MyString &carNumber, const MyString &phoneNumber, const Address &address);

	void setCarNumber(const MyString &carNumber);
	void setPhoneNumber(const MyString &phoneNumber);

	void setAddress(const MyString &origin, const MyString &note, int x, int y);
	void setAddress(const Address &address);

	void setRating(double rate);
	void addRating(short rate);

	void setStatus(int status);
	void setStatus(const StatusDriver &status);

	const MyString &getCarNumber() const;
	const MyString &getPhoneNumber() const;
	const Address &getAddress() const;
	const StatusDriver &getStatus() const;
	double getRating() const;

	void writeDriverInFile(std::ofstream &ofs) const;
	Driver readDriverFromFile(std::ifstream &ifs);

	User *clone() const override;
};