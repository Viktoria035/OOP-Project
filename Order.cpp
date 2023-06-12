#include "Order.h"
#include "Utils.h"
#include <fstream>
#include <sstream>

int Order::count = 0;

Order::Order()
{
	this->orderID = count;
	count++;
}

Order::Order(const MyString& origin, int addressX, int addressY,
	const MyString& dest, int destX, int destY, int countPassengers):
	origin(origin,addressX,addressY),destination(dest,destX,destY),
	passengersCount(countPassengers) 
{
	this->orderID = count;
	count++;
}

Order::Order(const MyString& origin, int addressX, int addressY, const MyString& noteAddress,
	const MyString& dest, int destX, int destY, int countPassengers):
	origin(origin,noteAddress,addressX,addressY),destination(dest,destX,destY),
	passengersCount(countPassengers) 
{
	this->orderID = count;
	count++;
}

Order::Order(const MyString& origin, int addressX, int addressY,
	const MyString& dest, int destX, int destY, const MyString& destNote,
	int countPassengers):origin(origin,addressX,addressY),destination(dest,destNote,destX,destY),
	passengersCount(countPassengers) 
{
	this->orderID = count;
	count++;
}

Order::Order(const MyString& origin, int addressX, int addressY, const MyString& addressNote,
	const MyString& dest, int destX, int destY, const MyString& destNote, int countPassengers):
	origin(origin,addressNote,addressX,addressY),destination(dest,destNote,destX,destY),
	passengersCount(countPassengers) 
{
	this->orderID = count;
	count++;
}

void Order::setAmount(int amount)
{
	if (amount < 0)
		throw std::invalid_argument("Not valid order amount!");
	this->amount = amount;
}

void Order::setMinutes(int minutes)
{
	if (minutes < 0)
		minutes = 0;
	this->minutes = minutes;
}

void Order::setDriverRating(short rate)
{
	(*driver).setRating(rate);
}

void Order::setStatusByInt(int num)
{
	if (num == 0)
		this->status = StatusOrder::inProgress;
	else if (num == 1)
		this->status = StatusOrder::accepted;
	else if (num == 2)
		this->status = StatusOrder::finished;
	else if (num == 3)
		this->status = StatusOrder::canceled;
	else if (num == 4)
		this->status = StatusOrder::declined;
	else if (num == 5)//not sure because this will never happen probably
		this->status = StatusOrder::paid;
	else
		throw std::invalid_argument("Not valid number for order status!");
}

void Order::setOrderStatus(const StatusOrder& status)
{
	this->status = status;
}

void Order::getStatusOfOrder() const
{
	if (this->status == StatusOrder::accepted)
		std::cout << " accepted." << std::endl;
	else if (this->status == StatusOrder::canceled)
		std::cout << " canceled." << std::endl;
	else if (this->status == StatusOrder::finished)
		std::cout << " finished." << std::endl;
	else if (this->status == StatusOrder::inProgress)
		std::cout << " in progress." << std::endl;
	else if (this->status == StatusOrder::declined)
		std::cout << " declined." << std::endl;
	else if (this->status == StatusOrder::paid)
		std::cout << " paid." << std::endl;
	else
	{
		std::cout << "Not valid status!" << std::endl;
		return;
	}
}

const StatusOrder& Order::getStatus() const
{
	return status;
}

void Order::setClient(Client* somebody)
{
	client = somebody;
}

void Order::setDriver(Driver* somebody)
{
	driver = somebody;
}

size_t Order::getID() const
{
	return orderID;
}

void Order::checkAllInfo() const
{
	std::cout << "The status of the order is: ";
	getStatusOfOrder();
	std::cout << "The car which your are waiting is: " << (*driver).getCarNumber() << '.' << std::endl;
	std::cout << "Driver first name is: " << (*driver).getFirstName() << ", last name: " << (*driver).getLastName() <<
		", phone number: " << (*driver).getPhoneNumber() << ", rating: " << (*driver).getRating() << '.' << std::endl;
	std::cout << "He will be on the address after: " << minutes << " minutes." << std::endl;
}

void Order::checkOrderInfo() const
{
	std::cout << "Client: " << client->getFirstName() << " " << client->getLastName() << " has made an order from: "
		<< origin.getName() << ", coordinates: (" << origin.getCoordinates().x << "," << origin.getCoordinates().y << "), note(not neccessery): "
		<< origin.getNote() << std::endl;
	std::cout << "To driver: " << driver->getFirstName() << " " << driver->getLastName() << std::endl;
	std::cout << "Destionation is: " << destination.getName() << ", coordinates: (" << destination.getCoordinates().x << "," << destination.getCoordinates().y << "), note(not neccessery): "
		<< destination.getNote() << std::endl;
	std::cout << "The orderID is: " << getID() << ", with status: ";
	getStatusOfOrder();
}

void Order::setAddress(const MyString& name,const MyString& note, int x, int y)
{
	origin.setName(name);
	origin.setNote(note);
	origin.setPoint(x, y);
}

void Order::setAddress(const Address& address)
{
	origin = address;
}

void Order::setDestination(const MyString& name,const MyString& note, int x, int y)
{
	destination.setName(name);
	destination.setNote(note);
	destination.setPoint(x, y);
}

void Order::setDestination(const Address& address)
{
	destination = address;
}

void Order::setPassengersCount(int count)
{
	if (count < 0 || count > 6)
		throw std::invalid_argument("Sorry the amount of passengers should be between 1-6!");
	this->passengersCount = count;
}

const Client* Order::getClient() const
{
	return client;
}

Client* Order::getClient()
{
	return client;
}

const Driver* Order::getDriver() const
{
	return driver;
}

Driver* Order::getDriver()
{
	return driver;
}

const Address& Order::getOrigin() const
{
	return origin;
}

const Address& Order::getDest() const
{
	return destination;
}

int Order::getAmount() const
{
	return amount;
}

int Order::getMinutes() const
{
	return minutes;
}

int Order::getPassengersCount() const
{
	return passengersCount;
}

void Order::clear()
{
	driver->setStatus(StatusDriver::Free);
	status = StatusOrder::canceled;
}

void Order::withdrawMoneyFromClient(size_t amount)
{
	(*client).withdraw(amount);
}

void Order::setDriverStatus(const StatusDriver& curr)
{
	driver->setStatus(curr);
}

void Order::setDriverAddress(const Address& ad)
{
	driver->setAddress(ad);
}

void Order::addDriverAmount(int amount)
{
	driver->addMoney(amount);
}

void Order::writeOrderInFile(std::ofstream& ofs) const
{
	ofs << getOrigin().getName() << ",";
	ofs << getOrigin().getCoordinates().x << ",";
	ofs << getOrigin().getCoordinates().y << ",";
	ofs << getOrigin().getNote() << ",";
	ofs << getDest().getName() << ",";
	ofs << getDest().getCoordinates().x << ",";
	ofs << getDest().getCoordinates().y << ",";
	ofs << getDest().getNote() << ",";
	ofs << getPassengersCount() << ",";
	ofs << getClient()->getUserName() << ",";
	ofs << getDriver()->getUserName() << ",";
	ofs << getMinutes() << ",";
	ofs << (int)getStatus() << ",";
	ofs << getAmount() << std::endl;
}

Order Order::readOrderFromFile(std::ifstream& ifs,Vector<Client>& clients, Vector<Driver>& drivers)
{
	static char* messegesOrders[] = { (char*)"address",(char*)"coordinates X",(char*)"coordinates Y",(char*)"noteOrigin",(char*)"destination",
	(char*)"coordinates X",(char*)"coordinates Y",(char*)"noteDest",(char*)"passengers count",(char*)"client username",(char*)"driver username",
	(char*)"minutes",(char*)"status" ,(char*)"amount" };
	char buff[sizeof(messegesOrders) / sizeof(char*)][1024];
	char buff2[BUFF_SIZE];
	ifs.getline(buff2, 1024);
	std::stringstream ss(buff2);
	for (int i = 0; i < sizeof(messegesOrders) / sizeof(char*); i++)
	{
		ss.getline(buff[i], 1024, ',');
	}
	setAddress(buff[0], buff[3], fromStringToInt(buff[1]), fromStringToInt(buff[2]));
	setDestination(buff[4], buff[7], fromStringToInt(buff[5]), fromStringToInt(buff[6]));
	setPassengersCount(fromStringToInt(buff[8]));
	setClient(findClient(clients,buff[9]));
	setDriver(findDriver(drivers,buff[10]));
	setMinutes(fromStringToInt(buff[11]));
	setStatusByInt(fromStringToInt(buff[12]));
	setAmount(fromStringToInt(buff[13]));
	return (*this);
}
