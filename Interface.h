#pragma once
#include "System.h"
#include "Utils.h"

class Interface
{
	bool tryRegister(System& taxi);
	bool tryLogin(System& taxi);

	void ifClientLogged(System& taxi);
	void ifDriverLogged(System& taxi);

	bool IsOrderSuccess(System& taxi);
	bool isCheckOrderSuccess(System& taxi);
	bool isCancelOrderSuccess(System& taxi);
	bool isPaymentSuccess(System& taxi);
	bool isRatingSuccess(System& taxi);
	bool isAddingMoneySuccess(System& taxi);

	void chooseCommand(void (*func) (),MyString& command);
public:
	/*void lobbyMenu() const;
	void clientMenu() const;
	void driverMenu() const;*/
	void run();
};

static void lobbyMenu()
{
	std::cout << "       Welcome to our system! Please choose a command :       " << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << "<1.> Login;" << std::endl;
	std::cout << "<2.> Register;" << std::endl;
	std::cout << "<3.> Exit;" << std::endl;
}

static void clientMenu()
{
	std::cout << "Hello, you are login as <client>! Here are your commands: " << std::endl;
	std::cout << ">>*------------------------------------------------------*<<" << std::endl;
	std::cout << "1* Create order --> create_order;" << std::endl;
	std::cout << "2* Check order --> check_order;" << std::endl;
	std::cout << "3* Cancel order --> cancel_order;" << std::endl;
	std::cout << "4* Pay to driver --> pay_driver;" << std::endl;
	std::cout << "5* Rate driver's skills --> rate_driver;" << std::endl;
	std::cout << "6* Add money to your bank card --> add_money;" << std::endl;
	std::cout << "7* Logout;" << std::endl;
	std::cout << ">>*------------------------------------------------------*<<" << std::endl;
}

static void driverMenu()
{
	std::cout << "Hello, you are login as <driver>! Here are your commands: " << std::endl;
	std::cout << ">>*------------------------------------------------------*<<" << std::endl;
	std::cout << "1* Change address --> change_address;" << std::endl;
	std::cout << "2* Check messages --> check_messages;" << std::endl;
	std::cout << "3* Accept order --> accept_order;" << std::endl;
	std::cout << "4* Decline order --> decline_order;" << std::endl;
	std::cout << "5* Finish order --> finish_order;" << std::endl;
	std::cout << "6* Accept payment --> accept_payment;" << std::endl;
	std::cout << "7* Logout;" << std::endl;
	std::cout << ">>*------------------------------------------------------*<<" << std::endl;
}

void Interface::chooseCommand(void(*func)(), MyString& command)
{
	func();
	std::cin >> command;
	toLower(command);
}

bool Interface::tryRegister(System& taxi)
{
	try
	{
		taxi.registration();
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Not successed registration! Try again!" << std::endl;
		return false;
	}
	return true;
}

bool Interface::tryLogin(System& taxi)
{
	try
	{
		MyString username;
		MyString pass;
		std::cout << "Please select your username: ";
		std::cin >> username;
		std::cout << std::endl;
		std::cout << "Please select your password: ";
		std::cin >> pass;
		taxi.login(username,pass);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Not successed login! Try again!" << std::endl;
		return false;
	}
	return true;
}

bool isClientCommandsCorrect(const MyString& command)
{
	return command == "create_order" || command == "check_order" || command == "cancel_order"
		|| command == "pay_driver" || command == "rate_driver" || command == "add_money" || command == "logout";
}

bool isDriverCommandsCorrect(const MyString& command)
{
	return command == "change_address" || command == "check_messages" || command == "accept_order"
		|| command == "decline_order" || command == "finish_order" || command == "accept_payment" || command == "logout";
}

void setAddress(Address& curr,MyString name,char* note,int x,int y)
{
	std::cout << "Please select your address name: ";
	std::cin >> name;
	std::cout << std::endl;

	std::cout << "Please select the coordinate ->x: ";
	std::cin >> x;
	std::cout << "Please select the coordinate ->y: ";
	std::cin >> y;
	std::cout << std::endl;

	std::cout << "Add note(not nesseccary,if you want skip write <s>): ";
	std::cin.ignore();
	std::cin.getline(note,1024);
	std::cout << std::endl;

	curr.setName(name);
	curr.setPoint(x, y);
	if (strcmp(note, "s") != 0)
		curr.setNote(note);
}

bool Interface::IsOrderSuccess(System& taxi)
{
	Address origin;
	Address dest;
	MyString name;
	char note[1024];
	int x = 0;
	int y = 0;
	size_t num = 0;
	std::cout << "Set the information for the start point: " << std::endl;
	setAddress(origin, name, note, x, y);
	std::cout << "Now set the information for the end point: " << std::endl;
	setAddress(dest, name, note, x, y);
	std::cout << "Please add number of passengers: ";
	std::cin >> num;
	try
	{
		taxi.order(origin, dest, num);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Your command can not be finished, try again!" << std::endl;
		return false;
	}
	std::cout << "Your order has been successfully created!" << std::endl;
	return true;
}

bool Interface::isCheckOrderSuccess(System& taxi)
{
	size_t orderID = taxi.findOrderByClientUsername();
	try
	{
		taxi.checkOrder(orderID);
		std::cout << std::endl;
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "There is a problem! Try again!";
		return false;
	}
	return true;
}

bool Interface::isCancelOrderSuccess(System& taxi)
{
	size_t orderID = taxi.findOrderByClientUsername();
	try
	{
		taxi.cancel_order(orderID);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Have a problem! Try again!" << std::endl;
		return false;
	}
	std::cout << "Your order has just been successfully canceled!" << std::endl;
	return true;
}

bool Interface::isPaymentSuccess(System& taxi)
{
	double amount = 0;
	std::cout << "Please select how much money would you pay: ";
	std::cin >> amount;
	while (amount < 0)
	{
		std::cout << "The amount must be more than zero! Try again: ";
		std::cin >> amount;
	}
	std::cout << std::endl;
	size_t orderID = taxi.findOrderByClientUsername();
	try
	{
		taxi.pay(amount, orderID);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return false;
	}
	std::cout << "Your payment is successfull!" << std::endl;
	return true;
}

bool Interface::isRatingSuccess(System& taxi)
{
	double rate = 1;
	std::cout << "Please select rate from 1 to 5: ";
	std::cin >> rate;
	MyString nameOfDriver = taxi.getDriverName(taxi.findOrderByClientUsername());
	try
	{
		taxi.rate(nameOfDriver, rate);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return false;
	}
	std::cout << "Thank you for your rating!" << std::endl;
	return true;
}

bool Interface::isAddingMoneySuccess(System& taxi)
{
	double amount;
	std::cout << "Please select how much money do you want to add to your bank card: ";
	std::cin >> amount;
	try
	{
		taxi.add_money(amount);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return false;
	}
	std::cout << "Congrats, your transaction was successfull!" << std::endl;
	return true;
}

void Interface::ifClientLogged(System& taxi)
{
	MyString command;
	chooseCommand(clientMenu, command);
	while (command != "logout")
	{
		if (!isClientCommandsCorrect(command))
		{
			std::cout << "Not valid command! Please try again!" << std::endl;
			chooseCommand(clientMenu, command);
			continue;
		}

		if (command == "create_order")
		{
			if (!IsOrderSuccess(taxi))
			{
				chooseCommand(clientMenu, command);
				continue;
			}
			chooseCommand(clientMenu, command);
		}

		if (command == "check_order")
		{
			if (!isCheckOrderSuccess(taxi))
			{
				chooseCommand(clientMenu, command);
				continue;
			}
			chooseCommand(clientMenu, command);
		}

		if (command == "cancel_order")
		{
			if (!isCancelOrderSuccess(taxi))
			{
				chooseCommand(clientMenu, command);
				continue;
			}
			chooseCommand(clientMenu, command);
		}

		if (command == "pay_driver")
		{
			if (!isPaymentSuccess(taxi))
			{
				chooseCommand(clientMenu, command);
				continue;
			}
			chooseCommand(clientMenu, command);
		}

		if (command == "rate_driver")
		{
			if (!isRatingSuccess(taxi))
			{
				chooseCommand(clientMenu, command);
				continue;
			}
			chooseCommand(clientMenu, command);
		}

		if (command == "add_money")
		{
			if (!isAddingMoneySuccess(taxi))
			{
				chooseCommand(clientMenu, command);
				continue;
			}
			chooseCommand(clientMenu, command);
		}
		//TODO: OPTIMIZATION NEEDED
	}
	taxi.logout();
	std::cout << "You have successfully logout!" << std::endl;
}

void Interface::ifDriverLogged(System& taxi)
{
	MyString command;
	chooseCommand(driverMenu, command);
	while (command != "logout")
	{
		if (!isDriverCommandsCorrect(command))
		{
			std::cout << "Not valid command! Please try again!" << std::endl;
			chooseCommand(driverMenu, command);
			continue;
		}
		/*if (command == "change_address")
		{
			MyString name;
			MyString note;
			int x = 0;
			int y = 0;
			std::cout << "Please set: " << std::endl;
			std::cout << "Name of the new address: ";
			std::cin >> name;
			std::cout << std::endl;
			std::cout << "Coordinates x-> ";
			std::cin >> x;
			std::cout << std::endl;
			std::cout << ", y-> ";
			std::cin >> y;
			std::cout << std::endl;
			std::cout << "Note (not neccessary): ";
			std::cin >> note;
			std::cout << std::endl;

			Address newAdd(name, note, x, y);
			taxi.change_address(newAdd);
		}*/
		//TODO: Driver list of functions
	}
	taxi.logout();
	std::cout << "You have successfully logout!" << std::endl;
}

void Interface::run()
{
	System taxi;
	MyString buff;
	chooseCommand(lobbyMenu, buff);
	/*lobbyMenu();
	std::cin >> buff;
	toLower(buff);*/
	while (buff != "exit" && buff != "logout")
	{
		if (buff != "login" && buff != "register" && buff != "exit")
		{
			std::cout << "Not valid command!" << std::endl;
			chooseCommand(lobbyMenu, buff);
			/*lobbyMenu();
			std::cin >> buff;
			toLower(buff);*/
			continue;
		}

		if (buff == "register")
		{
			while (!tryRegister(taxi));
			std::cout << "Successed registration! Please now write <login>!" << std::endl;
			std::cin >> buff;
			toLower(buff);
			while (buff != "login")
			{
				std::cout << "Please enter the correct command! Try again: ";
				std::cin >> buff;
			}
			continue;
		}

		else if (buff == "login")
		{
			while (!tryLogin(taxi));
			if (buff == "exit")
				continue;
			std::cout << "Successed Login!" << std::endl;
			if (taxi.getCurrentUserType() == "client")
			{
				ifClientLogged(taxi);
				chooseCommand(lobbyMenu, buff);
			}
			else //if (taxi.getCurrentUserType() == "driver")
			{
				ifDriverLogged(taxi);
				chooseCommand(lobbyMenu, buff);
			}
		}
	} 
	std::cout << ">>*------------------------------------------------------*<<" << std::endl;
	std::cout << "You have just exit successed! Have a nice day!" << std::endl;
}