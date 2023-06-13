#pragma once
#include "Client.h"
#include "Driver.h"
#include "Vector.hpp"

enum class StatusOrder
{
	awaitingDriver,
	inProgress,
	accepted,
	finished,
	canceled,
	declined,
	paid,
	rated,
};

class Order
{
	Client* client = nullptr;
	int passengersCount = 1;

	Driver* driver = nullptr;
	int minutes = 0;

	int orderID;
	static int count;

	int amount = 0;//???

	Address origin;
	Address destination;

	StatusOrder status = StatusOrder::awaitingDriver;

	Vector<const Driver*> declinedBy;
public:
	Order();
	Order(const MyString& origin, int addressX, int addressY,
		const MyString& dest, int destX, int destY, int countPassengers);

	Order(const MyString& origin, int addressX, int addressY,const MyString& noteAddress,
		const MyString& dest, int destX, int destY, int countPassengers);

	Order(const MyString& origin, int addressX, int addressY,
		const MyString& dest, int destX, int destY,const MyString& destNote,
		int countPassengers);

	Order(const MyString& origin, int addressX, int addressY,const MyString& addressNote,
		const MyString& dest, int destX, int destY,const MyString& destNote, int countPassengers);

	//void setID(int ID);

	void setClient(Client* somebody);
	void setDriver(Driver* somebody);
	void setAmount(int amount);//????
	void setDriverRating(short rate);
	void setMinutes(int minutes);

	void setStatusByInt(int num);
	void setOrderStatus(const StatusOrder& status);

	void setAddress(const MyString& name,const MyString& note, int x, int y);
	void setAddress(const Address& address);

	void setDestination(const MyString& name,const MyString& note, int x, int y);
	void setDestination(const Address& address);

	void setPassengersCount(int count);

	void setDriverStatus(const StatusDriver& curr);
	void setDriverAddress(const Address& add);
	void addDriverAmount(int amount);

	int getPassengersCount() const;
	int getMinutes() const;

	void getStatusOfOrder() const;
	const StatusOrder& getStatus() const;

	int getAmount() const;//????

	const Client* getClient() const;
	Client* getClient();
	const Driver* getDriver() const;
	Driver* getDriver();

	const Address& getOrigin() const;
	const Address& getDest() const;

	size_t getID() const;

	void writeOrderInFile(std::ofstream& ofs) const;
	Order readOrderFromFile(std::ifstream& ifs, Vector<Client>& clients, Vector<Driver>& drivers);

	void withdrawMoneyFromClient(size_t amount);//MUST TRY!!!!!!
	void clear();//MUST TRY!!!!
	void checkOrderInfo() const;
	void checkAllInfo() const;//READYYYY!!!!!!

	void addDeclinedDriver(const Driver* driver);
	bool hasDriverDeclined(const Driver* driver) const;
};
