#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <iostream>
#include "CustomerInfo.h"

using namespace std;

class BankAccount {

private:

	int accountNumber = 0;     // non static data member initializer
	double balance = 0.0;     // non-static data member initializer

	// Default struct initialization
	CustomerInfo customer = {
		"Unknown",
		"Not-Available",
		"0000-0000"
	};    

public:

	// defualt Constructor
	BankAccount();

	// Parameterized  Constructor
	BankAccount(const CustomerInfo& cust, int accNumber, double initialBalance);

	// Destructor
	~BankAccount();

	// Member
	void Deposit(double amount);
	void Withdraw(double amount);
	void DisplayBankDetials() const;

};

#endif
