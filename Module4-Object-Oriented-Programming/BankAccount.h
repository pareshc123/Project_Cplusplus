#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <iostream>
#include "CustomerInfo.h"

using namespace std;

class BankAccount {

private:
	string accountHolder;
	int accountNumber;
	double balance;

	CustomerInfo customer;

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
