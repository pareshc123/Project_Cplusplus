#include "BankAccount.h"

int main() {

    // Object using default constructor
    BankAccount acc1;
    acc1.DisplayBankDetials();
    acc1.Deposit(500);
    acc1.Withdraw(200);
    acc1.DisplayBankDetials();

    // Object using parameterized constructor
    BankAccount acc2("Alice", 12345, 1000.0);
    acc2.DisplayBankDetials();
    acc2.Deposit(300);
    acc2.Withdraw(1500); // should show insufficient balance
    acc2.Withdraw(200);
    acc2.DisplayBankDetials();

    return 0;
}
