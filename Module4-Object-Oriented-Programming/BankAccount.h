#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <iostream>
#include "CustomerInfo.h"

using namespace std;

class BankAccount {

private:

	int accountNumber = 0;				  // non static data member initializer
	double balance = 0.0;				 // non-static data member initializer
	static int totalCustomers;			// Stati data member

	float* creditScorePtr;

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
	BankAccount(const CustomerInfo& cust, int accNumber, double initialBalance, float creditScore);

	// Copy Constructor
	BankAccount(const BankAccount& other);

	// Copy Assignment operator
	BankAccount& operator=(const BankAccount& other);

	// Destructor
	~BankAccount();

	// Non static Member functions
	void Deposit(double amount);
	void Withdraw(double amount);
	void DisplayBankDetials() const;

	// Static member functions
	static void DisplayTotalCustomers();
};

#endif
