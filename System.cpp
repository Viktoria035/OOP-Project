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

#pragma warning (disable:4996)

System::System()
{
	load();
}

const MyString& System::getCurrentUserType() const
{
	return currentUser->getType();
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

	if (findUser == nullptr) 
	{
		throw std::invalid_argument("Nonexistent user!");
	}

	if (findUser->getPass() != password) 
	{
		throw std::invalid_argument("Wrong password!");
	}

	currentUser = findUser;
}

void System::logout()
{
	currentUser = nullptr;
}

void System::createNewClient(Client& newClient)
{
	static char* messagesClient[] = { (char*)"Please select your username: ",(char*)"Please select your password: ",
	(char*)"Please select your first name: ",(char*)"Please select your last name: " };

	char buff[sizeof(messagesClient) / sizeof(char*)][BUFF_SIZE];
	for (size_t i = 0; i < sizeof(messagesClient) / sizeof(char*); i++)
	{
		std::cout << messagesClient[i] << " ";
		std::cin >> buff[i];
		std::cout << std::endl;

	}

	int i = 0;
	while (i != arrClients.getSize())
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
	static char* messagesDriver[] = { (char*)"Please select your username: ",(char*)"Please select your password: ",
	(char*)"Please select your first name: ",(char*)"Please select your last name: ",
		(char*)"Please select your car number: ",(char*)"Please select your phone number: " };

	char buff[sizeof(messagesDriver) / sizeof(char*)][BUFF_SIZE];
	for (size_t i = 0; i < sizeof(messagesDriver) / sizeof(char*); i++)
	{
		std::cout << messagesDriver[i] << " ";
		std::cin >> buff[i];
		std::cout << std::endl;
	}

	for (size_t i = 0; i < arrDrivers.getSize(); i++)
	{
		while (strcmp(buff[0], arrDrivers[i].getUserName().c_str()) == 0)
		{
			std::cout << "Sorry there is already driver with this username. Try again: ";
			std::cin >> buff[0];
		}
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
		arrClients.push_back(std::move(newClient));

	}
	else if (type == "driver")
	{
		Driver newDriver;
		createNewDriver(newDriver);
		arrDrivers.push_back(std::move(newDriver));
	}
}

void System::loadClients()
{
	std::ifstream ifs(CLIENTS_FILE);
	if (!ifs.is_open())
		throw std::runtime_error("Error while openning client file!");

	size_t linesCount = getLinesCount(ifs) - 1;
	int idx = 0;
	while (linesCount != 0)
	{
		Client client;
		client.readClientFromFile(ifs);
		arrClients.push_back(std::move(client));
		linesCount--;
	}

	ifs.close();
}

void System::loadDrivers()
{
	std::ifstream ifs(DRIVERS_FILE);
	if (!ifs.is_open())
		throw std::runtime_error("Error while openning driver file!");

	size_t linesCount = getLinesCount(ifs) - 1;
	while (linesCount != 0)
	{
		Driver driver;
		driver.readDriverFromFile(ifs);
		arrDrivers.push_back(std::move(driver));
		linesCount--;
	}

	ifs.close();
}

void System::loadOrders()
{
	std::ifstream ifs(ORDERS_FILE);
	if (!ifs.is_open())
		throw std::runtime_error("Error while openning order file!");

	size_t linesCount = getLinesCount(ifs) - 1;
	while (linesCount != 0)
	{
		Order order;
		order.readOrderFromFile(ifs, arrClients, arrDrivers);
		arrOrders.push_back(std::move(order));
		linesCount--;
	}

	ifs.close();
}

void System::load()
{
	try 
	{
		loadClients();
		loadDrivers();
		loadOrders();
	}
	catch (const std::runtime_error& exc)
	{
		std::cout << exc.what() << std::endl;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

void System::checkOrder(size_t orderID) const
{
	if (currentUser->getType() == "client")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getClient()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry, but you do not have the rights for this order!");
		(arrOrders[idx]).checkOrderForClient();
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::checkCurrentClientOrders() const//look for ','
{
	if (currentUser->getType() == "client")
	{
		size_t ordersSize = arrOrders.getSize();
		bool isEmpty = true;
		std::cout << "OrderIDs: ";
		for (size_t i = 0; i < ordersSize - 1; i++)
		{
			if (arrOrders[i].getClient()->getUserName() == currentUser->getUserName())
			{
				std::cout << arrOrders[i].getID() << ", ";
				isEmpty = false;
			}
		}
		if (arrOrders[ordersSize - 1].getClient()->getUserName() == currentUser->getUserName())
		{
			std::cout << arrOrders[ordersSize - 1].getID();
			isEmpty = false;
		}

		if (isEmpty)
			std::cout << " <empty>";
		std::cout << std::endl;
	}
}

void System::cancel_order(size_t orderID)
{
	if (currentUser->getType() == "client")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getClient()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry, but you do not have the rights for this order!");

		if (arrOrders[idx].getStatus() == StatusOrder::awaitingDriver 
			|| arrOrders[idx].getStatus() == StatusOrder::accepted 
			|| arrOrders[idx].getStatus() == StatusOrder::inProgress)
		{
			if (arrOrders[idx].getStatus() == StatusOrder::accepted)
			{
				arrOrders[idx].setDriverStatus(StatusDriver::Free);
				arrOrders[idx].getDriver()->addNotification("Order with ID: " + convertToStr(orderID) +
					" has been canceled! Your status is <Free>.");
			}
			arrOrders[idx].clear();
		}
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::pay(double amount, size_t orderID)
{
	if (currentUser->getType() == "client")
	{
		if (amount <= 0)
			throw std::invalid_argument("The amount should be more than zero!");
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getClient()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry, but you do not have the rights for this order!");
		if (arrOrders[idx].getStatus() == StatusOrder::finished)
		{
			arrOrders[idx].withdrawMoneyFromClient(convertToCoins(amount));
			arrOrders[idx].setAmount(convertToCoins(amount));

			arrOrders[idx].getDriver()->addNotification("Client with order ID: " + convertToStr(orderID) + " has just paid you "
				+ convertToStr(amount) + " leva.");
		}
		else
			throw std::logic_error("Sorry, but this order is not finished yet!");
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");

}

void System::rate(size_t orderID, short rating)
{
	if (currentUser->getType() == "client")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getClient()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry, but you do not have the rights for this order!");
		if (arrOrders[idx].getStatus() != StatusOrder::paid)
			throw std::logic_error("Sorry, but the order is not paid yet! Try again latter!");
		arrOrders[idx].setDriverRating(rating);
		arrOrders[idx].setOrderStatus(StatusOrder::rated);
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::add_money(double amount)
{
	if (currentUser->getType() == "client")
	{
		currentUser->addMoney(convertToCoins(amount));
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::accept_order(size_t orderID, size_t minutes)
{
	if (currentUser->getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getDriver()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry, but you do not have the rights for this order!");
		arrOrders[idx].setDriver(findDriver(arrDrivers,currentUser->getUserName()));
		arrOrders[idx].setMinutes(minutes);
		arrOrders[idx].setOrderStatus(StatusOrder::accepted);
		arrOrders[idx].setDriverStatus(StatusDriver::Driving);
		std::cout << "The order is accept!" << std::endl;

		arrOrders[idx].getClient()->addNotification("Order with ID: " + convertToStr(orderID) + ", has just been accepted!");
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::finish_order(size_t orderID)
{
	if (currentUser->getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getDriver()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry,but you do not have the rights for this order!");
		(arrOrders[idx]).setDriverAddress(arrOrders[idx].getDest());
		(arrOrders[idx]).setOrderStatus(StatusOrder::finished);
		arrOrders[idx].setDriverStatus(StatusDriver::Free);
		arrOrders[idx].getClient()->addNotification("Order with ID: " + convertToStr(orderID) +
			", has been finished. Please pay the driver as soon as possible!");
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::accept_payment(size_t orderID)
{
	if (currentUser->getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getAmount() == 0)
			throw std::logic_error("The client has not paid yet!");
		if (arrOrders[idx].getStatus() == StatusOrder::paid)
			throw std::logic_error("Your have already accept the payment!");
		arrOrders[idx].addDriverAmount(arrOrders[idx].getAmount());
		arrOrders[idx].setOrderStatus(StatusOrder::paid);

		arrOrders[idx].getClient()->addNotification("Driver to order with ID: " + convertToStr(orderID) +
			" has just accepted the payment. Please rate the driver!");
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::sortDriversByAddress(const Address& adr, size_t size)
{
	double* dist = new double[size];
	for (size_t i = 0; i < size; i++)
	{
		dist[i] = arrDrivers[i].getAddress().getDist(adr.getCoordinates());
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
	if (size == 0)
		throw std::out_of_range("Sorry there is no drivers!");
	sortDriversByAddress(adr, size);
	size_t i = 0;
	for (; i < arrDrivers.getSize(); i++)
	{
		if (arrDrivers[i].getStatus() == StatusDriver::Free)
			return i;
	}
	if (i >= size)
		throw std::out_of_range("Sorry there is no free driver!");
}

void System::handOutOrders()
{
	int indexForDriver = 0;
	for (size_t i = 0; i < arrOrders.getSize(); i++)
	{
		if (arrOrders[i].getStatus() == StatusOrder::awaitingDriver)
		{
			bool noDriver = false;
			try 
			{
				indexForDriver = findClosestDriver(arrOrders[i].getOrigin());
			}
			catch (const std::exception&)
			{
				arrOrders[i].setDriver(nullptr);
				continue;
			}
			while (arrOrders[i].hasDriverDeclined(&arrDrivers[indexForDriver]))
			{
				indexForDriver++;
				if (indexForDriver >= arrDrivers.getSize())
					noDriver = true;
			}
			if (noDriver)
				continue;
			arrOrders[i].setDriver(&arrDrivers[indexForDriver]);
			arrOrders[i].setOrderStatus(StatusOrder::inProgress);
		}
	}
}

void System::order(const Address& origin, const Address& dest, size_t passengersCount)
{
	if (currentUser->getType() == "client")
	{
		Order newOrder;
		newOrder.setAddress(origin);
		newOrder.setDestination(dest);
		newOrder.setClient(findClient(arrClients,currentUser->getUserName()));
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
		findDriver(arrDrivers,currentUser->getUserName())->setAddress(address);
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::decline_order(size_t orderID)
{
	if (currentUser->getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getDriver()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry,but you do not have the rights for this order!");
		arrOrders[idx].setOrderStatus(StatusOrder::awaitingDriver);
		arrOrders[idx].addDeclinedDriver(static_cast<Driver*>(currentUser));
		arrOrders[idx].setDriver(nullptr);
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::check_messages()
{
	if (currentUser->getType() == "driver")
	{
		handOutOrders();
		bool isEmpty = true;
		for (size_t i = 0; i < arrOrders.getSize(); i++)
		{
			if(arrOrders[i].getDriver() == nullptr)
				continue;
			if (currentUser->getUserName() == arrOrders[i].getDriver()->getUserName())
			{
				arrOrders[i].checkOrderForDriver();
				isEmpty = false;
			}
			std::cout << std::endl;
		}
		if (isEmpty)
			std::cout << "Sorry there is no orders offered to you!" << std::endl;
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

size_t System::findOrderByID(size_t ID) const
{
	for (size_t i = 0; i < arrOrders.getSize(); i++)
	{
		if (arrOrders[i].getID() == ID)
			return i;
	}
	throw std::invalid_argument("Not such an order ID!");
}

void System::printNotifications() const
{
	currentUser->printAllNotifications();
}

void System::writeClientsInFile() const
{
	std::ofstream ofsCl(CLIENTS_FILE, std::ios::out);
	if (!ofsCl.is_open())
	{
		throw std::runtime_error("Error while openning client file!");
	}

	for (size_t i = 0; i < arrClients.getSize(); i++)
	{
		arrClients[i].writeClientInFile(ofsCl);
	}

	ofsCl.close();
}

void System::writeDriversInFile() const
{
	std::ofstream ofsDr(DRIVERS_FILE, std::ios::out);
	if (!ofsDr.is_open())
	{
		throw std::runtime_error("Error while openning driver file!");
	}
	for (size_t i = 0; i < arrDrivers.getSize(); i++)
	{
		arrDrivers[i].writeDriverInFile(ofsDr);
	}

	ofsDr.close();
}

void System::writeOrdersInFile() const
{
	std::ofstream ofsOr(ORDERS_FILE, std::ios::out);
	if (!ofsOr.is_open())
	{
		throw std::runtime_error("Error while openning order file!");
	}

	for (size_t i = 0; i < arrOrders.getSize(); i++)
	{
		if (arrOrders[i].getStatus() == StatusOrder::rated || arrOrders[i].getStatus() == StatusOrder::canceled)
			continue;
		arrOrders[i].writeOrderInFile(ofsOr);
	}

	ofsOr.close();
}

void System::SaveState() const
{
	try
	{
		writeClientsInFile();
		writeDriversInFile();
		writeOrdersInFile();
	}
	catch (const std::runtime_error& exc)
	{
		std::cout << exc.what() << std::endl;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

System::~System()
{
	SaveState();
}
