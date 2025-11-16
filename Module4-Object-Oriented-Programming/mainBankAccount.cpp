#include "BankAccount.h"

int main() {

    // Display the total number of customers
    BankAccount::DisplayTotalCustomers();

    // Object using parameterized constructor
    CustomerInfo cust;
    cust.name = "Alice Wonderland";
    cust.address = "Wallstreet 159753, Unites States";
    cust.phonenumber = "1234567890";

    BankAccount acc2(cust, 12345, 1000.0, 753.5);
    acc2.DisplayBankDetials();
    acc2.Deposit(300);
    acc2.Withdraw(1500); // should show insufficient balance
    acc2.Withdraw(200);
    acc2.DisplayBankDetials();

    // Create an object from copy constructor
    BankAccount acc3 = acc2;
    acc3.DisplayBankDetials();

    // Display the total number of customers
    BankAccount::DisplayTotalCustomers();

    return 0;
}
