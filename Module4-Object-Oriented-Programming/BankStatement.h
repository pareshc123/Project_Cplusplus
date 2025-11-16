#ifndef BANKSTATEMENT_H
#define BANKSTATEMENT_H

#include <iostream>
#include <string>

using namespace std;

class BankStatement {

private:
	double amount;
	string type;         // Credit or Debit
	string timestamp;

public:

	// Parametrized Constructor
	BankStatement(double amt, const string& t, const string& time)
		: amount(amt), type(t), timestamp(time) {}

	// Display function
	void ShowBankStatement() const{
		cout << "$" << amount << " " << type << " on " << timestamp << endl;
	}

	// Getters
	double getAmount() const { return amount; }
	string gettype() const { return type; }
	string gettimestamp() const {return timestamp;}

};


#endif