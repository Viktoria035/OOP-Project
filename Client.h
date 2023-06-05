#pragma once
#include "User.h"
#include "MyString.h"

class Client :public User
{
	//size_t coins = 0;// stotinki in BG
public:
	Client();
	Client(const MyString& username, const MyString& password,
		const MyString& firstname, const MyString& lastname);

	//void setMoney(double coins);
	//double getMoney() const;

	void withdraw(size_t coins);
	//void addMoney(double leva);

	friend std::istream& operator>>(std::istream& is, Client& client);
	friend std::ostream& operator<<(std::ostream& os, const Client& client);

	User* clone() const override;
};