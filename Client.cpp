#include "Client.h"
#include "Utils.h"
#include <fstream>
#include <sstream>

Client::Client() :User("client") {}

Client::Client(const MyString& username, const MyString& password,
	const MyString& firstname, const MyString& lastname):
	User(username,password,firstname,lastname) {}

void Client::withdraw(int coins)
{
	if (coins > getCoins() || coins < 0)
		throw std::invalid_argument("Not valid amount!");
	setAmount(getCoins() - coins);
}

void Client::writeClientInFile(std::ofstream& ofs) const
{
	ofs << getUserName() << ",";
	ofs << getPass() << ",";
	ofs << getFirstName() << ",";
	ofs << getLastName() << ",";
	ofs << getCoins() << std::endl;
}

Client Client::readClientFromFile(std::ifstream& ifs)
{
	static char* messages[] = { (char*)"username: ",(char*)"password: ",
	(char*)"first name: ",(char*)"last name: ",(char*)"coins" };
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
	setAmount(fromStringToInt(buff[4]));
	return *this;
}

User* Client::clone() const
{
	return new Client(*this);
}
