#include <cstring>
#include "../headers/Interface.h"

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
	std::cout << "7* Check created orders ID --> check_ordersid;" << std::endl;
	std::cout << "8* See notifications from your current log --> notifications;" << std::endl;
	std::cout << "9* Logout;" << std::endl;
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
	std::cout << "7* See notifications from your current log --> notifications;" << std::endl;
	std::cout << "8* Logout;" << std::endl;
	std::cout << ">>*------------------------------------------------------*<<" << std::endl;
}

namespace
{
	bool isClientCommandsCorrect(const MyString &command)
	{
		return command == "create_order" || command == "check_order" || command == "cancel_order" || command == "pay_driver" || command == "rate_driver" || command == "add_money" || command == "check_ordersid" || command == "notifications" || command == "logout";
	}

	bool isDriverCommandsCorrect(const MyString &command)
	{
		return command == "change_address" || command == "check_messages" || command == "accept_order" || command == "decline_order" || command == "finish_order" || command == "accept_payment" || command == "notifications" || command == "logout";
	}

	bool isLobbyCommandCorrect(const MyString &command)
	{
		return command == "login" || command == "register" || command == "exit";
	}

	void setAddress(Address &curr)
	{
		MyString name;
		char note[BUFF_SIZE];
		int x = 0;
		int y = 0;
		std::cout << "Please select your address name: ";
		std::cin >> name;
		std::cout << std::endl;

		std::cout << "Please select the coordinate ->x: ";
		std::cin >> x;
		std::cout << "Please select the coordinate ->y: ";
		std::cin >> y;
		std::cout << std::endl;

		std::cout << "Add note(not nesseccary,if you want to skip write the letter -> s): ";
		std::cin.ignore();
		std::cin.getline(note, 1024);
		std::cout << std::endl;

		curr.setName(name);
		curr.setPoint(x, y);
		if (strcmp(note, "s") != 0)
			curr.setNote(note);
	}
}

void Interface::chooseCommand(void (*func)(), MyString &command)
{
	func();
	std::cin >> command;
	toLower(command);
}

bool Interface::tryRegister(System &taxi)
{
	try
	{
		taxi.registration();
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Ragistration failed! Try again!" << std::endl;
		return false;
	}
	return true;
}

bool Interface::tryLogin(System &taxi)
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
		taxi.login(username, pass);
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Login failed! Try again!" << std::endl;
		return false;
	}
	return true;
}

void Interface::Order(System &taxi)
{
	Address origin;
	Address dest;
	size_t num = 0;
	std::cout << "Set the information for the start point: " << std::endl;
	setAddress(origin);
	std::cout << "Now set the information for the end point: " << std::endl;
	setAddress(dest);
	std::cout << "Please add number of passengers: ";
	std::cin >> num;
	try
	{
		taxi.order(origin, dest, num);
		std::cout << "Your order has been successfully created!" << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Your command can not be finished, try again!" << std::endl;
		return;
	}
}

void Interface::CheckOrder(System &taxi) const
{
	try
	{
		size_t orderID = 0;
		std::cout << "Please select order ID which you want to check: ";
		std::cin >> orderID;
		taxi.checkOrder(orderID);
		std::cout << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return;
	}
}

void Interface::CancelOrder(System &taxi)
{
	size_t orderID = 0;
	std::cout << "Please select order ID which you want to cancel: ";
	std::cin >> orderID;
	try
	{
		taxi.cancel_order(orderID);
		std::cout << "The order has been successfully canceled!" << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Have a problem! Try again!" << std::endl;
		return;
	}
}

void Interface::Payment(System &taxi)
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
	size_t orderID = 0;
	std::cout << "Please select order ID which you want to pay: ";
	std::cin >> orderID;
	try
	{
		taxi.pay(amount, orderID);
		std::cout << "Your payment is successfull!" << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return;
	}
}

void Interface::Rating(System &taxi)
{
	short rate = 0;
	std::cout << "Please select number from 1 to 5: ";
	std::cin >> rate;
	std::cout << std::endl;
	size_t orderID = 0;
	std::wcout << "Please select driver's order ID you want to rate: ";
	std::cin >> orderID;
	try
	{
		taxi.rate(orderID, rate);
		std::cout << "Thank you for your rating!" << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return;
	}
}

void Interface::AddingMoney(System &taxi)
{
	double amount;
	std::cout << "Please select how much money you want to add to your bank acount: ";
	std::cin >> amount;
	try
	{
		taxi.add_money(amount);
		std::cout << "Congrats, your transaction was successfull!" << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return;
	}
}

void Interface::CheckOrdersID(System &taxi) const
{
	try
	{
		taxi.checkCurrentClientOrders();
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::wcout << "Try again!" << std::endl;
	}
}

void Interface::ifClientLogged(System &taxi)
{
	MyString command;
	do
	{
		chooseCommand(clientMenu, command);
		if (!isClientCommandsCorrect(command))
			std::cout << "Not valid command! Please try again!" << std::endl;

		else if (command == "create_order")
			Order(taxi);

		else if (command == "check_order")
			CheckOrder(taxi);

		else if (command == "cancel_order")
			CancelOrder(taxi);

		else if (command == "pay_driver")
			Payment(taxi);

		else if (command == "rate_driver")
			Rating(taxi);

		else if (command == "add_money")
			AddingMoney(taxi);

		else if (command == "check_ordersid")
			CheckOrdersID(taxi);
		else if (command == "notifications")
			Notifications(taxi);
	} while (command != "logout");
	taxi.logout();
	std::cout << "You have successfully logout!" << std::endl;
}

void Interface::ChangeAddress(System &taxi)
{
	Address newAdd;
	setAddress(newAdd);
	try
	{
		taxi.change_address(newAdd);
		std::cout << "You have successfully changed your address!" << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return;
	}
}

void Interface::CheckMessages(System &taxi) const
{
	try
	{
		taxi.check_messages();
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
	}
}

void Interface::AcceptOrder(System &taxi)
{
	size_t minutes = 0;
	size_t orderID = 0;
	std::cout << "Please select minutes to arrival: ";
	std::cin >> minutes;
	std::cout << std::endl;
	std::cout << "Please select which order ID will you accept: ";
	std::cin >> orderID;
	try
	{
		taxi.accept_order(orderID, minutes);
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
	}
}

void Interface::DeclineOrder(System &taxi)
{
	size_t orderID = 0;
	std::cout << "Please select which order ID will you decline: ";
	std::cin >> orderID;
	try
	{
		taxi.decline_order(orderID);
		std::cout << "The order has been successfully decline!" << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return;
	}
}

void Interface::FinishOrder(System &taxi)
{
	size_t orderID = 0;
	std::cout << "Please select order ID: ";
	std::cin >> orderID;
	try
	{
		taxi.finish_order(orderID);
		std::cout << "You have successfully finished the order!" << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::wcout << "Try again!" << std::endl;
		return;
	}
}

void Interface::AcceptPayment(System &taxi)
{
	size_t orderID = 0;
	std::cout << "Please enter the order ID  which you want to accept payment from: ";
	std::cin >> orderID;
	try
	{
		taxi.accept_payment(orderID);
		std::cout << "You have successfully accepted the payment!" << std::endl;
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::cout << "Try again!" << std::endl;
		return;
	}
}

void Interface::ifDriverLogged(System &taxi)
{
	MyString command;
	do
	{
		chooseCommand(driverMenu, command);
		if (!isDriverCommandsCorrect(command))
			std::cout << "Not valid command! Please try again!" << std::endl;

		else if (command == "change_address")
			ChangeAddress(taxi);

		else if (command == "check_messages")
			CheckMessages(taxi);

		else if (command == "accept_order")
			AcceptOrder(taxi);

		else if (command == "decline_order")
			DeclineOrder(taxi);

		else if (command == "finish_order")
			FinishOrder(taxi);

		else if (command == "accept_payment")
			AcceptPayment(taxi);
		else if (command == "notifications")
			Notifications(taxi);
	} while (command != "logout");
	taxi.logout();
	std::cout << "You have successfully logout!" << std::endl;
}

void Interface::Notifications(System &taxi) const
{
	try
	{
		taxi.printNotifications();
	}
	catch (const std::exception &exc)
	{
		std::cout << exc.what() << std::endl;
		std::wcout << "Try again!" << std::endl;
	}
}

void Interface::run()
{
	System taxi;

	MyString buff;
	do
	{
		chooseCommand(lobbyMenu, buff);

		if (!isLobbyCommandCorrect(buff))
			std::cout << "Not valid command!" << std::endl;

		else if (buff == "register")
		{
			while (!tryRegister(taxi))
				;
			std::cout << "You have successfully registered! Please now login!" << std::endl;
			continue;
		}

		else if (buff == "login")
		{
			if (!tryLogin(taxi))
				continue;
			std::cout << "You have successfully logged in!" << std::endl;

			if (taxi.getCurrentUserType() == "client")
				ifClientLogged(taxi);
			else
				ifDriverLogged(taxi);
		}

	} while (buff != "exit" && buff != "logout");
	std::cout << ">>*------------------------------------------------------*<<" << std::endl;
	std::cout << "You have successfully exit! Have a nice day!" << std::endl;
}