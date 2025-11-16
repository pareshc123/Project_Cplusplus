#include "BankAccount.h"

// Default constructor
BankAccount::BankAccount() {

	accountNumber = 0;
	balance = 0.0;
	customer = { "Unknown", "N/A", "N/A" };
	cout << "\nDefalut Constructor called for Account: " << customer.name << endl;
}

// Parameterized constructor
BankAccount::BankAccount(const CustomerInfo& cust, int accNumber, double initialBalance) {

	customer = cust;
	accountNumber = accNumber;
	balance = initialBalance;
	cout << "\nParameterized constructor called for account: " << customer.name << endl;
}

// Destructor
BankAccount::~BankAccount() {
	cout << "\nDestructor was called for account: " << customer.name << endl;
}

//Member functions

// Deposit function
void BankAccount::Deposit(double amount) {
	balance += amount;
	cout << "\nHello " << customer.name << ". New Transaction alert !!" << endl;
	cout << amount << " credited to your account. New Balance: " << balance << endl;
}

// Withdraw function
void BankAccount::Withdraw(double amount) {

	cout << "\nHello " << customer.name << ". New Transaction alert !!" << endl;
	cout << "New Withdraw Request initiated." << endl;
	
	if (balance < amount) {
		cout << "Request not possible. Insufficient Balance !! Please request a lower amount." << endl;
		cout << "Current balance: " << balance << endl;
		return ;
	}
	else {
		balance -= amount;
		cout << amount << " debited from  account. New Balance: " << balance << endl;
	}
	
}

// Display method
void BankAccount::DisplayBankDetials() const {

	cout << "\nDisplaying the Customer Bank Details ... " << endl;

	cout << "Account Holder: " << customer.name << endl;
	cout << "  Address: " << customer.address << endl;
	cout << "  Phone:   " << customer.phonenumber << endl;
	cout << "  Account Number: " << accountNumber << endl;
	cout << "  Balance: " << balance << endl;

}

