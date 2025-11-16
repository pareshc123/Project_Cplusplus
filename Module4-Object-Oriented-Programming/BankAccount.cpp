#include "BankAccount.h"

// Initialize the static data members
int BankAccount::totalCustomers = 0; // Defualt is always set to zero, since data type is int

// Default constructor
BankAccount::BankAccount() {
	
	// Increment the count of number of customers when the constructor is called
	++totalCustomers;

	// allcoation of memory in constructor
	creditScorePtr = new float(0);

	// Non-Static member initializers handles the data members 
	cout << "\nDefalut Constructor called for Account: " << customer.name << endl;
}

// Parameterized constructor
BankAccount::BankAccount(const CustomerInfo& cust, int accNumber, double initialBalance, float creditScore) {

	// Increment the count of number of customers when the constructor is called
	++totalCustomers;

	// allcoation of memory in constructor
	creditScorePtr = new float(creditScore);

	// Constructor overrides default non-static members values
	customer = cust;
	accountNumber = accNumber;
	balance = initialBalance;
	cout << "\nParameterized constructor called for account: " << customer.name << endl;
}

// Copy Constructor
BankAccount::BankAccount(const BankAccount& other) {

	customer = other.customer;
	accountNumber = other.accountNumber;
	balance = other.balance;
	creditScorePtr = new float(*(other.creditScorePtr));   // deep copy

	++totalCustomers; // increment total customers for the new copy
	cout << "\nCopy Construtctor was initiated for " << customer.name << endl;

}


// Destructor
BankAccount::~BankAccount() {
	
	// Decrement the count of number of customers when the destructor is called
	--totalCustomers;

	// Free memory in destructor	
	delete creditScorePtr;
	creditScorePtr = nullptr;

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
	cout << "  Credit Score: " << *creditScorePtr << endl;

}

// Static Member:
void BankAccount::DisplayTotalCustomers() {

	cout << "\nTotal Customers associated with the bank: " << totalCustomers << endl;
}
