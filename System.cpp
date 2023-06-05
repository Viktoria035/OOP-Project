#include "System.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "User.h"
#include "Utils.h"
#include "Order.h"
const char* CLIENTS_FILE = "clients.txt";
const char* DRIVERS_FILE = "drivers.txt";
const char* ORDERS_FILE = "orders.txt";

static char* messagesClient[] = { (char*)"Please select your username: ",(char*)"Please select your password: ",
	(char*)"Please select your first name: ",(char*)"Please select your last name: " };

static char* messagesDriver[] = { (char*)"Please select your username: ",(char*)"Please select your password: ",
	(char*)"Please select your first name: ",(char*)"Please select your last name: ",
		(char*)"Please select your car number: ",(char*)"Please select your phone number: " };

Client* System::findClient(const MyString& username)
{
	for (size_t i = 0; i < arrClients.getSize(); i++)
	{
		if ((arrClients[i]).getUserName() == username)
			return &arrClients[i];
	}
	throw std::invalid_argument("Not existing client with that username!");
}

Driver* System::findDriver(const MyString& username)
{
	for (size_t i = 0; i < arrDrivers.getSize(); i++)
	{
		if ((arrDrivers[i]).getUserName() == username)
			return &arrDrivers[i];
	}
	throw std::invalid_argument("Not existing driver with that username!");
}

void System::login(const MyString& username, const MyString& password)
{
	User* findUser = nullptr;
	for (int i = 0; i < arrDrivers.getSize(); i++)
	{
		if ((arrDrivers[i]).getUserName() == username)
		{
			findUser = (&arrDrivers[i]);
			break;
		}
	}

	if (findUser == nullptr)
	{
		for (int i = 0; i < arrClients.getSize(); i++)
		{
			if ((arrClients[i]).getUserName() == username)
			{
				findUser = (&arrClients[i]);
				break;
			}
		}
	}
	if (findUser == nullptr) {
		throw std::invalid_argument("Nonexistent user!");
	}

	if (findUser->getPass() != password) {
		throw std::invalid_argument("Wrong password!");
	}
	currentUser = findUser;
}

void System::logout()
{
	currentUser = nullptr;
}

void System::writeClientInFile(std::ofstream& ofs, const Client& newClient) const
{
	ofs << newClient.getUserName() << ",";
	ofs << newClient.getPass() << ",";
	ofs << newClient.getFirstName() << ",";
	ofs << newClient.getLastName() << ",";
	ofs << newClient.getLeva() << std::endl;
}

void System::writeDriverInFile(std::ofstream& ofs, const Driver& newDriver) const
{
	ofs << newDriver.getUserName() << ",";
	ofs << newDriver.getPass() << ",";
	ofs << newDriver.getFirstName() << ",";
	ofs << newDriver.getLastName() << ",";
	ofs << newDriver.getCarNumber() << ",";
	ofs << newDriver.getPhoneNumber() << ",";
	ofs << newDriver.getLeva() << ",";
	ofs << (int)newDriver.getStatus() << ",";
	ofs << newDriver.getRating() << ",";
	ofs << newDriver.getAddress().getCoordinates().x << ","
		<< newDriver.getAddress().getCoordinates().y << ","
		<< newDriver.getAddress().getName() << std::endl;
}

void System::writeOrderInFile(std::ofstream& ofs, const Order& newOrder) const
{
	ofs << newOrder.getOrigin().getName() << ",";
	ofs << newOrder.getOrigin().getCoordinates().x << ",";
	ofs << newOrder.getOrigin().getCoordinates().y << ",";
	ofs << newOrder.getOrigin().getNote() << ",";
	ofs << newOrder.getDest().getName() << ",";
	ofs << newOrder.getDest().getCoordinates().x << ",";
	ofs << newOrder.getDest().getCoordinates().y << ",";
	ofs << newOrder.getDest().getNote() << ",";
	ofs << newOrder.getPassengersCount() << ",";
	ofs << (*newOrder.getClient()).getUserName() << ",";
	ofs << (*newOrder.getDriver()).getUserName() << ",";
	ofs << newOrder.getMinutes() << ",";
	ofs << (int)newOrder.getStatus() << std::endl;
}

void System::createNewClient(Client& newClient)
{
	char buff[sizeof(messagesClient) / sizeof(char*)][1024];
	for (size_t i = 0; i < sizeof(messagesClient) / sizeof(char*); i++)
	{
		std::cout << messagesClient[i] << " ";
		std::cin >> buff[i];
		std::cout << std::endl;

	}

	int i = 0;
	while (i!= arrClients.getSize())
	{
		if (strcmp(buff[0], (arrClients[i]).getUserName().c_str()) == 0)
		{
			std::cout << "Sorry this username is already taken. Please select new one: ";
			std::cin >> buff[0];
			i = 0;
			continue;
		}
		i++;
	}

	newClient.setUserName(buff[0]);
	newClient.setPass(buff[1]);
	newClient.setFirstName(buff[2]);
	newClient.setLastName(buff[3]);
}

void System::createNewDriver(Driver& newDriver)
{
	char buff[sizeof(messagesDriver) / sizeof(char*)][1024];
	for (size_t i = 0; i < sizeof(messagesDriver) / sizeof(char*); i++)
	{
		std::cout << messagesDriver[i] << " ";
		std::cin >> buff[i];
		std::cout << std::endl;
	}

	for (size_t i = 0; i < arrDrivers.getSize(); i++)
	{
		while (strcmp(buff[0], arrDrivers[i].getUserName().c_str()) == 0)
			std::cin >> buff[0];
	}

	newDriver.setUserName(buff[0]);
	newDriver.setPass(buff[1]);
	newDriver.setFirstName(buff[2]);
	newDriver.setLastName(buff[3]);
	newDriver.setCarNumber(buff[4]);
	newDriver.setPhoneNumber(buff[5]);
}

void System::registration()
{
	MyString type;
	std::cout << "Please select type: ";
	std::cin >> type;
	while (type != "client" && type != "driver")
	{
		std::cout << "Please add valid type -> client or -> driver!" << std::endl;
		std::cin >> type;
	}
	if (type == "client")
	{
		Client newClient;
		createNewClient(newClient);
		//writeClientInFile(newClient);
		arrClients.push_back(std::move(newClient));

	}
	else if (type == "driver")
	{
		Driver newDriver;
		createNewDriver(newDriver);
		//writeDriverInFile(newDriver);
		arrDrivers.push_back(std::move(newDriver));
	}
}

void System::loadClients()
{
	std::ifstream ifs(CLIENTS_FILE);
	if (!ifs.is_open())
	{
		std::cout << "Error while openning the file!";
		return;
	}

	size_t linesCount = getLinesCount(ifs) - 1;
	static char* messages[] = { (char*)"username: ",(char*)"password: ",
	(char*)"first name: ",(char*)"last name: ",(char*)"coins" };
	char buff[sizeof(messages) / sizeof(char*)][1024];
	char buff2[1024];
	while (linesCount != 0)
	{
		ifs.getline(buff2, 1024);
		std::stringstream ss(buff2);
		for (int i = 0; i < sizeof(messages) / sizeof(char*); i++)
		{
			ss.getline(buff[i], 1024, ',');
			/*if (ss.eof())
			{
				throw std::runtime_error("Not enough data!");
			}*/
		}
		Client client;
		client.setUserName(buff[0]);
		client.setPass(buff[1]);
		client.setFirstName(buff[2]);
		client.setLastName(buff[3]);
		client.setAmount(stringToDouble(buff[4]));
		arrClients.push_back(std::move(client));
		/*if (!ss.eof()) {
			throw std::runtime_error("Invalid file!");
		}*/
		linesCount--;
	}

	ifs.close();
}

void System::loadDrivers()
{
	std::ifstream ifs(DRIVERS_FILE);
	if (!ifs.is_open())
	{
		std::cout << "Error while openning the file!";
		return;
	}
	size_t linesCount = getLinesCount(ifs) - 1;
	static char* messeges[] = { (char*)"username",(char*)"pass",(char*)"first name",(char*)"last name",
	(char*)"car number",(char*)"phone number",(char*)"amount",(char*)"status driver" ,(char*)"rating",(char*)"coordinates X",
		(char*)"coordinates Y",(char*)"address name",(char*)"note" };
	char buff[sizeof(messeges) / sizeof(char*)][1024];
	char buff2[1024];
	while (linesCount != 0)
	{
		ifs.getline(buff2, 1024);
		std::stringstream ss(buff2);
		for (int i = 0; i < sizeof(messeges) / sizeof(char*); i++)
		{
			ss.getline(buff[i], 1024, ',');
			/*if (ss.eof())//loookkkkkk
			{
				throw std::runtime_error("Not enough data!");
			}*/
		}
		Driver driver;
		driver.setUserName(buff[0]);
		driver.setPass(buff[1]);
		driver.setFirstName(buff[2]);
		driver.setLastName(buff[3]);
		driver.setCarNumber(buff[4]);
		driver.setPhoneNumber(buff[5]);
		driver.setAmount(fromStringToInt(buff[6]));
		driver.setStatus(fromStringToInt(buff[7]));
		driver.setRating(stringToDouble(buff[8]));
		driver.setAddress(buff[11], buff[12], fromStringToInt(buff[9]), fromStringToInt(buff[10]));
		arrDrivers.push_back(std::move(driver));
		/*if (!ss.eof()) {
			throw std::runtime_error("Invalid file!");
		}*/
		linesCount--;
	}

	ifs.close();
}

void System::load()
{
	loadClients();
	loadDrivers();
	loadOrders();
}

void System::loadOrders()
{
	std::ifstream ifs(ORDERS_FILE);
	if (!ifs.is_open())
	{
		std::cout << "Error while openning the file!";
		return;
	}
	size_t linesCount = getLinesCount(ifs) - 1;
	static char* messegesOrders[] = { (char*)"address",(char*)"coordinates X",(char*)"coordinates Y",(char*)"noteOrigin",(char*)"destination",
	(char*)"coordinates X",(char*)"coordinates Y",(char*)"noteDest",(char*)"passengers count",(char*)"client username",(char*)"driver username",
	(char*)"minutes",(char*)"status" };

	char buff[sizeof(messegesOrders) / sizeof(char*)][1024];
	char buff2[1024];
	while (linesCount != 0)
	{
		ifs.getline(buff2, 1024);
		std::stringstream ss(buff2);
		for (int i = 0; i < sizeof(messegesOrders) / sizeof(char*); i++)
		{
			ss.getline(buff[i], 1024, ',');
		}
		Order order;
		order.setAddress(buff[0], buff[3], fromStringToInt(buff[1]), fromStringToInt(buff[2]));
		order.setDestination(buff[4], buff[7], fromStringToInt(buff[5]), fromStringToInt(buff[6]));
		order.setPassengersCount(fromStringToInt(buff[8]));
		order.setClient(findClient(buff[9]));
		order.setDriver(findDriver(buff[10]));
		//order.setAmount(fromStringToInt(buff[11]));
		order.setMinutes(fromStringToInt(buff[11]));
		order.setStatusByInt(fromStringToInt(buff[12]));
		arrOrders.push_back(std::move(order));
		/*if (!ss.eof()) {
			throw std::runtime_error("Invalid file!");
		}*/
		linesCount--;
	}

	ifs.close();
}

void System::checkOrder(size_t orderID) const
{
	if (currentUser->getType() == "client")
	{
		size_t idx = findOrderByID(orderID);
		(arrOrders[idx]).check();
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::print() const
{
	for (size_t i = 0; i < arrClients.getSize(); i++)
	{
		std::cout << (arrClients[i]).getUserName() << " " << (arrClients[i]).getPass()
			<< " " << (arrClients[i]).getFirstName() << " " << (arrClients[i]).getLastName() << " " << (arrClients[i]).getLeva() << std::endl;
	}
	std::cout << std::endl;
	for (size_t i = 0; i < arrDrivers.getSize(); i++)
	{
		std::cout << (arrDrivers[i]).getUserName() << " " << (arrDrivers[i]).getPass()
			<< " " << (arrDrivers[i]).getFirstName() << " " << (arrDrivers[i]).getLastName() << " " <<
			(arrDrivers[i]).getCarNumber() << " " << (arrDrivers[i]).getPhoneNumber() << " " <<
			(arrDrivers[i]).getLeva() << " " << (int)(arrDrivers[i]).getStatus() << " " << (arrDrivers[i]).getRating() << " " <<
			(arrDrivers[i]).getAddress().getName() << " " << (arrDrivers[i]).getAddress().getCoordinates().x << " "
			<< (arrDrivers[i]).getAddress().getCoordinates().y << " " << std::endl;
	}
	std::cout << std::endl;
	for (size_t i = 0; i < arrOrders.getSize(); i++)
	{
		(arrOrders[i]).check();
		std::cout << std::endl;
		std::cout << (arrOrders[i]).getID() << " " << (arrOrders[i]).getOrigin().getName() << " " << (arrOrders[i]).getOrigin().getNote() << " "
			<< (arrOrders[i]).getOrigin().getCoordinates().x << " " << (arrOrders[i]).getOrigin().getCoordinates().y << " " <<
			(arrOrders[i]).getDest().getName() << " " << (arrOrders[i]).getDest().getNote() << " "
			<< (arrOrders[i]).getDest().getCoordinates().x << " " << (arrOrders[i]).getDest().getCoordinates().y << " " << std::endl;

	}
}

void System::cancel_order(size_t orderID)
{
	if (currentUser->getType() == "client")
	{
		size_t idx = findOrderByID(orderID);
		if ((arrOrders[idx]).getStatus() == StatusOrder::accepted)
		{
			std::cout << "Order with number: " << orderID << "has just been canceled!" << std::endl;
			std::cout << "Driver: " << (*(arrOrders[idx]).getDriver()).getUserName() << "your status is Free." << std::endl;
		}
		(arrOrders[idx]).clear();
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::pay(double amount, size_t orderID)
{
	if (currentUser->getType() == "client")
	{
		size_t idx = findOrderByID(orderID);
		if ((arrOrders[idx]).getStatus() == StatusOrder::finished)
		{
			std::cout << "Your order has been finished! Driver: " << (*(arrOrders[idx]).getDriver()).getUserName() << " has been paid: " << amount << " leva." << std::endl;
			(arrOrders[idx]).giveDriverMoneyFromClient(convertToCoins(amount));
		}
		else
		{
			std::cout << "Sorry this order is not finished,yet!" << std::endl;
		}
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");

}

void System::rate(const MyString& nameOfDriver, double rating)
{
	if (currentUser->getType() == "client")
	{
		for (size_t i = 0; i < arrOrders.getSize(); i++)
		{
			if ((*(arrOrders[i]).getClient()).getUserName() == currentUser->getUserName() && ((arrOrders[i]).getStatus() == StatusOrder::finished))
			{
				for (size_t i = 0; i < arrDrivers.getSize(); i++)
				{
					if ((arrDrivers[i]).getFirstName() == nameOfDriver)
						(arrOrders[i]).setDriverRating(rating);
					else
					{
						std::cout << "Sorry the name of the driver was not found in the finished orders! Please try again!" << std::endl;
					}
				}
			}
			else
			{
				std::cout << "A client with order thar the driver: " << nameOfDriver << " was not found! Please check if it is correct!" << std::endl;
			}
		}
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::add_money(double amount)
{
	if (currentUser->getType() == "client")
	{
		size_t coins = convertToCoins(amount);
		currentUser->addMoney(amount);
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::accept_order(size_t orderID, size_t minutes)
{
	if ((*currentUser).getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		(arrOrders[idx]).setDriver(findDriver((*currentUser).getUserName()));
		(arrOrders[idx]).setMinutes(minutes);
		(arrOrders[idx]).setOrderStatus(StatusOrder::accepted);
		(arrOrders[idx]).setDriverStatus(StatusDriver::Driving);
		std::cout << "The order is accept!" << std::endl;
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::finish_order(size_t orderID)
{
	if (currentUser->getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		(arrOrders[idx]).setDriverAddress((arrOrders[idx]).getDest());
		(arrOrders[idx]).setOrderStatus(StatusOrder::finished);
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::accept_payment(size_t orderID, double amount)
{
	if (currentUser->getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		(arrOrders[idx]).addDriverAmount(amount);
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::SaveState()
{
	std::ofstream ofsCl(CLIENTS_FILE, std::ios::out);
	if (!ofsCl.is_open())
	{
		std::cout << "Error while openning the file!";
		return;
	}

	for (size_t i = 0; i < arrClients.getSize(); i++)
	{
		writeClientInFile(ofsCl, (arrClients[i]));
	}

	ofsCl.close();

	std::ofstream ofsDr(DRIVERS_FILE, std::ios::out);
	if (!ofsDr.is_open())
	{
		std::cout << "Error while openning the file!";
		return;
	}
	for (size_t i = 0; i < arrDrivers.getSize(); i++)
	{
		writeDriverInFile(ofsDr, (arrDrivers[i]));
	}

	ofsDr.close();

	std::ofstream ofsOr(ORDERS_FILE, std::ios::out);
	if (!ofsOr.is_open())
	{
		std::cout << "Error while openning the file!" << std::endl;
		return;
	}

	for (size_t i = 0; i < arrOrders.getSize(); i++)
	{
		writeOrderInFile(ofsOr, (arrOrders[i]));
	}

	ofsOr.close();
}

void System::sortDriversByAddress(const Address& adr, size_t size)
{
	double* dist = new double[size];
	for (size_t i = 0; i < size; i++)
	{
		dist[i] = (arrDrivers[i]).getAddress().getDist(adr.getCoordinates());
	}
	for (size_t i = 0; i < size - 1; i++)
	{
		int minDistIndex = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (dist[j] < dist[minDistIndex])
				minDistIndex = j;
		}
		if (minDistIndex != i)
		{
			std::swap(arrDrivers[i], arrDrivers[minDistIndex]);
			std::swap(dist[i], dist[minDistIndex]);
		}
	}
	delete[] dist;
}

size_t System::findClosestDriver(const Address& adr)
{
	size_t size = arrDrivers.getSize();
	sortDriversByAddress(adr, size);
	size_t i = 0;
	for (; i < arrDrivers.getSize(); i++)
	{
		if ((arrDrivers[i]).getStatus() != StatusDriver::Free)
			i++;
		else
			return i;
	}
	if (i > size)
		throw std::out_of_range("Sorry there is no free driver!");
}

void System::order(const Address& origin, const Address& dest, size_t passengersCount)
{
	if (currentUser->getType() == "client")
	{
		size_t index = 0;
		try
		{
			index = findClosestDriver(origin);
		}
		catch (std::out_of_range& exc)
		{
			std::cout << exc.what() << std::endl;
			return;
		}
		Order newOrder;
		newOrder.setDriver(&arrDrivers[index]);
		newOrder.setAddress(origin);
		newOrder.setDestination(dest);
		newOrder.setClient(findClient(currentUser->getUserName()));
		newOrder.setPassengersCount(passengersCount);
		arrOrders.push_back(std::move(newOrder));
	}
	else
		throw std::invalid_argument("You are not client! You do not have the right for this command!");
}

void System::change_address(const Address& address)
{
	if (currentUser->getType() == "driver")
	{
		Pointer<Driver> currDriver = findDriver(currentUser->getUserName());
		(*currDriver).setAddress(address);
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::decline_order(size_t orderID)//????
{
	if ((*currentUser).getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		sortDriversByAddress(arrOrders[idx].getOrigin(), arrDrivers.getSize());
		size_t index = 0;
		try
		{
			index = findClosestDriver(arrOrders[idx].getOrigin());
		}
		catch (std::out_of_range& exc)
		{
			std::cout << exc.what() << std::endl;
			return;
		}
		if (arrDrivers[idx].getUserName() == arrOrders[idx].getDriver()->getUserName())
			idx++;
		if (idx >= arrDrivers.getSize())
			throw std::out_of_range("There is not free driver!");
		arrOrders[idx].setDriver(&arrDrivers[idx]);
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::check_messages() const
{
	if (currentUser->getType() == "driver")
	{
		//size_t* arrID = new size_t[arrOrders.getSize()]{ 0 };
		for (size_t i = 0; i < arrOrders.getSize(); i++)
		{
			if (currentUser->getUserName() == arrOrders[i].getDriver()->getUserName())
			{
				(arrOrders[i]).checkInfo();
				//arrID[i] = arrOrders[i].getID();
			}
			std::cout << std::endl;
		}

		//delete[] arrID;
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

//void System::acceptOrDecline()
//{
//	char command;
//	char id;
//	unsigned  minutes = 0;
//	std::cout << "Please select order to accept('A') or decline('D'): ";
//	std::cout << "OrderID: ";
//	std::cin >> id;
//	size_t convertToNum = id - '0';
//	for (size_t i = 0; i < arrOrders.getSize(); i++)
//	{
//		if (convertToNum != arrID[i])
//			throw std::invalid_argument("Not valid ID order!");
//	}
//	std::cout << "Command: ";
//	std::cin >> command;
//	switch (command)
//	{
//	case 'A':std::cout << "Please select how minutes will it takes to you get to the address: ";
//		std::cin >> minutes;
//		accept_order(id - '0', minutes); break;
//	case 'D': decline_order(id - '0'); break;
//	default:"There is no such a command!"; break;
//	}
//}

size_t System::findOrderByID(size_t ID) const
{
	for (size_t i = 0; i < arrOrders.getSize(); i++)
	{
		if (arrOrders[i].getID() == ID)
			return i;
	}
	throw std::invalid_argument("Not such an ID for order!");
}

System::~System()
{
	SaveState();
}

//for (size_t i = 0; i < arrOrders.getSize(); i++)
//{
//	int idx = 0;
//	try
//	{
//		idx = findClosestDriver(arrOrders[i].getOrigin());
//	}
//	catch (std::out_of_range& exc)
//	{
//		std::cout << exc.what() << std::endl;
//		continue;
//	}
//	arrOrders[i].setDriver(&arrDrivers[idx]);
//}