#pragma once
#include "User.h"
#include "Client.h"
#include "Driver.h"
#include "Order.h"
#include "Vector.hpp"

class System
{
	Vector<Client> arrClients;
	Vector<Driver> arrDrivers;
	Vector<Order> arrOrders;
	User *currentUser;

public:
	System();

	const MyString &getCurrentUserType() const;

	void login(const MyString &username, const MyString &password);
	void logout();
	void registration();

	void createNewClient(Client &newClient);
	void createNewDriver(Driver &newDriver);

	void load();
	void loadClients();
	void loadDrivers();
	void loadOrders();

	void order(const Address &origin, const Address &dest, size_t passengersCount);
	void pay(double amount, size_t orderID);
	void cancel_order(size_t orderID);
	void checkOrder(size_t orderID) const;
	void rate(size_t orderID, short rating);
	void add_money(double amount);
	void checkCurrentClientOrders() const;

	void change_address(const Address &address);
	void check_messages();
	void decline_order(size_t orderID);
	void accept_order(size_t orderID, size_t minutes);
	void finish_order(size_t orderID);
	void accept_payment(size_t orderID);

	void handOutOrders();
	void printNotifications() const;

	size_t findOrderByID(size_t ID) const;

	void sortDriversByAddress(const Address &adr, size_t size);
	size_t findClosestDriver(const Address &adr);

	void writeClientsInFile() const;
	void writeDriversInFile() const;
	void writeOrdersInFile() const;
	void SaveState() const;

	~System();
};