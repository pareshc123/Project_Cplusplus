#include "BankAccount.h"

// Default constructor
BankAccount::BankAccount() {

	accountHolder = "Unknown";
	accountNumber = 0;
	balance = 0.0;
	cout << "\nDefalut Constructor called for Account: " << accountHolder << endl;
}

// Parameterized constructor
BankAccount::BankAccount(const string& accHolder, int accNumber, double initialBalance) {

	accountHolder = accHolder;
	accountNumber = accNumber;
	balance = initialBalance;
	cout << "\nParameterized constructor called for account: " << accountHolder << endl;
}

// Destructor
BankAccount::~BankAccount() {
	cout << "\nDestructor was called for account: " << accountHolder << endl;
}

//Member functions

// Deposit function
void BankAccount::Deposit(double amount) {
	balance += amount;
	cout << "\nHello " << accountHolder << ". New Transaction alert !!" << endl;
	cout << amount << " credited to your account. New Balance: " << balance << endl;
}

// Withdraw function
void BankAccount::Withdraw(double amount) {

	cout << "\nHello " << accountHolder << ". New Transaction alert !!" << endl;
	cout << "New Withdraw Request initiated." << endl;
	
	if (balance < amount) {
		cout << "Request not possible. Insufficient Balance !! Please request a lower amount." << endl;
		cout << "Current balance: " << balance << endl;
		return ;
	}
	else {
		balance -= amount;
		cout << amount << " debited from users account. New Balance: " << balance << endl;
	}
	
}

// Display method
void BankAccount::DisplayBankDetials() const {

	cout << "\nDisplaying the Current Bank Details for " << accountHolder << endl;
	cout << "Account Holder: " << accountHolder << endl;
	cout << "Account Number: " << accountNumber << endl;
	cout << "Balance: " << balance << endl;

}

