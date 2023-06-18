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

	User* clone() const override;
};
