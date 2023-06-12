#pragma once
#include "User.h"
#include "MyString.h"

class Client :public User
{
public:
	Client();
	Client(const MyString& username, const MyString& password,
		const MyString& firstname, const MyString& lastname);

	void withdraw(int coins);

	void writeClientInFile(std::ofstream& ofs) const;
	Client readClientFromFile(std::ifstream& ifs);

	friend std::istream& operator>>(std::istream& is, Client& client);
	friend std::ostream& operator<<(std::ostream& os, const Client& client);

	User* clone() const override;
};
