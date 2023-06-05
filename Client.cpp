#include "Client.h"
#include "Utils.h"
namespace
{
	/*double convertToLeva(size_t amount)
	{
		return amount / 100.0;
	}

	size_t convertToCoins(double amount)
	{
		return amount * 100;
	}*/
}

Client::Client() :User("client") {}

Client::Client(const MyString& username, const MyString& password,
	const MyString& firstname, const MyString& lastname):
	User(username,password,firstname,lastname) {}

//void Client::setMoney(double leva)
//{
//	size_t coins = convertToCoins(leva);
//	this->coins = coins;
//}

//double Client::getMoney() const
//{
//	return convertToLeva(coins);
//}

void Client::withdraw(size_t coins)
{
	if (coins > getCoins())
		throw std::invalid_argument("Not valid amount!");
	setAmount(convertToLeva(getCoins() - coins));
}

User* Client::clone() const
{
	return new Client(*this);
}
//void Client::addMoney(double leva)
//{
//	size_t coins = convertToCoins(leva);
//	if (coins < 0)
//		throw std::invalid_argument("Not valid amount!");
//	this->coins += coins;
//}