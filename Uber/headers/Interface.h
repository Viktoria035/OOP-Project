#pragma once
#include "System.h"
#include "Utils.h"

class Interface
{
	bool tryRegister(System &taxi);
	bool tryLogin(System &taxi);

	void ifClientLogged(System &taxi);
	void ifDriverLogged(System &taxi);

	// client functions
	void Order(System &taxi);
	void CheckOrder(System &taxi) const;
	void CancelOrder(System &taxi);
	void Payment(System &taxi);
	void Rating(System &taxi);
	void AddingMoney(System &taxi);
	void CheckOrdersID(System &taxi) const;

	// driver functions
	void ChangeAddress(System &taxi);
	void CheckMessages(System &taxi) const;
	void AcceptOrder(System &taxi);
	void DeclineOrder(System &taxi);
	void FinishOrder(System &taxi);
	void AcceptPayment(System &taxi);

	void Notifications(System &taxi) const;
	void chooseCommand(void (*func)(), MyString &command);

public:
	void run();
};