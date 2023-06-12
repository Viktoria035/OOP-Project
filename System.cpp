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

void System::createNewClient(Client& newClient)
{
	static char* messagesClient[] = { (char*)"Please select your username: ",(char*)"Please select your password: ",
	(char*)"Please select your first name: ",(char*)"Please select your last name: " };

	char buff[sizeof(messagesClient) / sizeof(char*)][1024];
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
	{
		std::cout << "Error while openning the file!";
		return;
	}
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
	{
		std::cout << "Error while openning the file!";
		return;
	}
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
	while (linesCount != 0)
	{
		Order order;
		order.readOrderFromFile(ifs,arrClients,arrDrivers);
		arrOrders.push_back(std::move(order));
		linesCount--;
	}

	ifs.close();
}

void System::checkOrder(size_t orderID) const
{
	if (currentUser->getType() == "client")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getClient()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry you do not have rights about this order!");
		(arrOrders[idx]).checkAllInfo();
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::checkCurrentClientOrders() const
{
	if (currentUser->getType() == "client")
	{
		bool isEmpty = true;
		std::cout << "OrderIDs: ";
		for (size_t i = 0; i < arrOrders.getSize(); i++)
		{
			if (arrOrders[i].getClient()->getUserName() == currentUser->getUserName())
			{
				std::cout << arrOrders[i].getID() << " ";
				isEmpty = false;
			}
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
			throw std::invalid_argument("Sorry you do not have rights about this order!");

		if ((arrOrders[idx]).getStatus() == StatusOrder::accepted)
			arrOrders[idx].getDriver()->addNotification("Order with ID: " + convertToStr(orderID) +
				" has been canceled! Your status is <Free>.");
		(arrOrders[idx]).clear();
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
			throw std::invalid_argument("Sorry you do not have rights about this order!");
		if ((arrOrders[idx]).getStatus() == StatusOrder::finished)
		{
			(arrOrders[idx]).withdrawMoneyFromClient(convertToCoins(amount));
			arrOrders[idx].setAmount(convertToCoins(amount));

			arrOrders[idx].getDriver()->addNotification("Client to order with ID: " + convertToStr(orderID) + " has just paid you " + convertToStr(amount) + " leva.");
		}
		else
			throw std::logic_error("Sorry this order is not finished,yet!");
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");

}

void System::rate(const MyString& nameOfDriver, double rating)//???
{
	if (currentUser->getType() == "client")
	{
		for (size_t i = 0; i < arrOrders.getSize(); i++)
		{
			if (arrOrders[i].getClient()->getUserName() == currentUser->getUserName() && ((arrOrders[i]).getStatus() == StatusOrder::finished))
			{
				for (size_t j = 0; j < arrDrivers.getSize(); j++)
				{
					if ((arrDrivers[j]).getFirstName() == nameOfDriver)
						(arrOrders[i]).setDriverRating(rating);
					else
					{
						throw std::invalid_argument("Sorry the name of the driver was not found!");
					}
				}
			}
			else
			{
				throw std::logic_error("Sorry your order is not finished yet, so you can not rate the driver!");
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
		//int coins = convertToCoins(amount);
		currentUser->addMoney(convertToCoins(amount));
	}
	else
		throw std::invalid_argument("You are not client! You do not have the rights for this command!");
}

void System::accept_order(size_t orderID, size_t minutes)
{
	if ((*currentUser).getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getDriver()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry you do not have rights about this order!");
		(arrOrders[idx]).setDriver(findDriver(arrDrivers,(*currentUser).getUserName()));
		(arrOrders[idx]).setMinutes(minutes);
		(arrOrders[idx]).setOrderStatus(StatusOrder::accepted);
		(arrOrders[idx]).setDriverStatus(StatusDriver::Driving);
		std::cout << "The order is accept!" << std::endl;

		(arrOrders[idx]).getClient()->addNotification("Order with ID: " + convertToStr(orderID) + ", has just been accepted!");
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
			throw std::invalid_argument("Sorry you do not have rights about this order!");
		(arrOrders[idx]).setDriverAddress((arrOrders[idx]).getDest());
		(arrOrders[idx]).setOrderStatus(StatusOrder::finished);

		arrOrders[idx].getClient()->addNotification("Order with ID: " + convertToStr(orderID) +
			", has been finished. Please pay the driver as soon as possible!");
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::accept_payment(size_t orderID)//?????
{
	if (currentUser->getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getAmount() == 0)
			throw std::logic_error("The client has not paid yet!");
		(arrOrders[idx]).addDriverAmount(arrOrders[idx].getAmount());
		arrOrders[idx].setOrderStatus(StatusOrder::paid);

		arrOrders[idx].getClient()->addNotification("Driver to order with ID: " + convertToStr(orderID) +
			" has accepted the payment. Please rate the driver!");
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
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
		if ((arrDrivers[i]).getStatus() == StatusDriver::Free)
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
		index = findClosestDriver(origin);
		Order newOrder;
		newOrder.setDriver(&arrDrivers[index]);
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

void System::decline_order(size_t orderID)//????
{
	if ((*currentUser).getType() == "driver")
	{
		size_t idx = findOrderByID(orderID);
		if (arrOrders[idx].getDriver()->getUserName() != currentUser->getUserName())
			throw std::invalid_argument("Sorry you do not have rights about this order!");
		sortDriversByAddress(arrOrders[idx].getOrigin(), arrDrivers.getSize());
		size_t index = 0;
		index = findClosestDriver(arrOrders[idx].getOrigin());
		if (arrDrivers[index].getUserName() == arrOrders[idx].getDriver()->getUserName())
			index++;
		if (index >= arrDrivers.getSize())
		{
			arrOrders[idx].getClient()->addNotification("Sorry your order with ID: " + convertToStr(orderID) +
				"can not be taken, there is no free drivers right now! Please wait!");
			arrOrders[idx].setOrderStatus(StatusOrder::declined);
			index = 0;
			arrOrders[idx].setDriver(&arrDrivers[index]);
			return;
		}
		arrOrders[idx].setDriver(&arrDrivers[index]);
	}
	else
		throw std::invalid_argument("You are not driver! You do not have the rights for this command!");
}

void System::check_messages() const
{
	if (currentUser->getType() == "driver")
	{
		bool isEmpty = true;
		for (size_t i = 0; i < arrOrders.getSize(); i++)
		{
			if (currentUser->getUserName() == arrOrders[i].getDriver()->getUserName())
			{
				(arrOrders[i]).checkOrderInfo();
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

const MyString& System::getDriverName(size_t orderID) const
{
	for (size_t i = 0; i < arrOrders.getSize(); i++)
	{
		if (arrOrders[i].getID() == orderID)
			return arrOrders[i].getDriver()->getFirstName();
	}
	throw std::out_of_range("Sorry there is not driver with that name!");
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
		std::cout << "Error while openning the file!";
		return;
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
		std::cout << "Error while openning the file!";
		return;
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
		std::cout << "Error while openning the file!" << std::endl;
		return;
	}

	for (size_t i = 0; i < arrOrders.getSize(); i++)
	{
		if (arrOrders[i].getStatus() == StatusOrder::paid)
			continue;
		arrOrders[i].writeOrderInFile(ofsOr);
	}

	ofsOr.close();
}

void System::SaveState() const
{
	writeClientsInFile();
	writeDriversInFile();
	writeOrdersInFile();
}


System::~System()
{
	SaveState();
}
