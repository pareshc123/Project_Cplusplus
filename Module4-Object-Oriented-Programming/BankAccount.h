#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <iostream>

using namespace std;

class BankAccount {

private:
	string accountHolder;
	int accountNumber;
	double balance;

public:

	// defualt Constructor
	BankAccount();

	// Parameterized  Constructor
	BankAccount(const string& accHolder, int accNumber, double initialBalance);

	// Destructor
	~BankAccount();

	// Member
	void Deposit(double amount);
	void Withdraw(double amount);
	void DisplayBankDetials() const;

};

#endif
