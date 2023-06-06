#pragma once
#include "User.h"
#include "Client.h"
#include "Driver.h"
#include "Order.h"
//#include "Shared_ptr.hpp"
#include "Vector.hpp"
#include "Pointer.hpp"

class System
{
	Vector<Client> arrClients;
	Vector<Driver> arrDrivers;
	Vector<Order> arrOrders;
	User* currentUser;

public:
	System();

	const MyString& getCurrentUserType() const;
	const MyString& getDriverName(size_t orderID) const;

	void login(const MyString& username, const MyString& password);
	void logout();
	void registration();

	void createNewClient(Client& newClient);
	void createNewDriver(Driver& newDriver);
	//void createNewOrder(Order& newOrder);<---------------------------------------------------------------------

	void writeDriverInFile(std::ofstream& ofs,const Driver& newDriver) const;
	void writeClientInFile(std::ofstream& ofs,const Client& newClient) const;
	void writeOrderInFile(std::ofstream& ofs,const Order& newOrder) const;//<--------------------------------------------------------------

	void load();

	void loadClients();
	void loadDrivers();
	void loadOrders();

	void pay(double amount, size_t orderID);//READY!!!
	void cancel_order(size_t orderID);//READYYYYYY!!!!!
	void checkOrder(size_t orderID) const;//READYYYY!!!!!!
	void rate(const MyString& nameOfDriver, double rating);//READYYYY!!!!!!
	void add_money(double amount);//READY!!!!!

	//Functions that I don't know how to make 
	void order(const Address& origin, const Address& dest, size_t passengersCount);//READYYYY!!!!
	void change_address(const Address& address);//READYYYY!!!
	void check_messages() const;//?????
	void decline_order(size_t orderID);//??????
	//void acceptOrDecline();

	void accept_order(size_t orderID, size_t minutes);//READYYY!!!!!
	void finish_order(size_t orderID);//READYYYY!!!!!!
	void accept_payment(size_t orderID,double amount);//READYYYY!!!!!!!

	void print() const;

	Client* findClient(const MyString& username);
	Driver* findDriver(const MyString& username);
	size_t findOrderByID(size_t ID) const;
	size_t findOrderByClientUsername() const;

	void sortDriversByAddress(const Address& adr,size_t size);
	size_t findClosestDriver(const Address& adr);

	void SaveState();
	~System();
};

//static char* messages[] = { (char*)"username", (char*)"password", (char*)"firstName", (char*)"lastName" };
//char buffer3[sizeof(messages) / sizeof(char*)][BUFFER_SIZE];
//for (int i = 0; i < sizeof(messages) / sizeof(char*); i++) {
//	ss.getline(buffer3[i], BUFFER_SIZE, ',');
//	if (ss.eof()) {
//		throw std::runtime_error("Not enough data!");
//	}
//}
////this is client
//Client client;
//client.setUsername(buffer3[0]);
//client.setPassword(buffer3[1]);
//client.setFirstName(buffer3[2]);
//client.setLastName(buffer3[3]);
//users.add(std::move(client));
//if (!ss.eof()) {
//	throw std::runtime_error("Invalid file!");
//}
