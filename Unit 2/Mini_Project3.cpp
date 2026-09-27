#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
    int accountNumber;
    string holderName;
    double balance;

public:
    Account(int number, string name, double amount) {
        accountNumber = number;
        holderName = name;
        balance = amount;
    }

    void deposit(double amount) {
        balance = balance + amount;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance = balance - amount;
            cout << "Withdrawal successful." << endl;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    virtual void calculateInterest() = 0;

    virtual void display() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Holder Name: " << holderName << endl;
        cout << "Balance: Rs. " << balance << endl;
    }

    virtual ~Account() {}
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int number, string name, double amount)
        : Account(number, name, amount) {
    }

    void calculateInterest() override {
        double interest = balance * 0.04;
        cout << "Savings Interest: Rs. " << interest << endl;
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(int number, string name, double amount)
        : Account(number, name, amount) {
    }

    void calculateInterest() override {
        cout << "Current Account: No interest." << endl;
    }
};

class FixedDepositAccount : public Account {
public:
    FixedDepositAccount(int number, string name, double amount)
        : Account(number, name, amount) {
    }

    void calculateInterest() override {
        double interest = balance * 0.07;
        cout << "Fixed Deposit Interest: Rs. "
             << interest << endl;
    }
};

int main() {

    SavingsAccount savings(101, "Aayush", 10000);
    CurrentAccount current(102, "Rahul", 15000);
    FixedDepositAccount fixed(103, "Priya", 20000);

    cout << "=== Savings Account ===" << endl;
    savings.deposit(2000);
    savings.withdraw(1000);
    savings.display();
    savings.calculateInterest();

    cout << endl;

    cout << "=== Current Account ===" << endl;
    current.deposit(5000);
    current.display();
    current.calculateInterest();
    cout << endl;

    cout << "=== Fixed Deposit Account ===" << endl;
    fixed.display();
    fixed.calculateInterest();

    return 0;
}
