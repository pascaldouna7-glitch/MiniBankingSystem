#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Account {
private:
    int pin;
    int accountNumber;
    string name;
    double balance;
    vector<string> transactions;

public:
    Account(int accNo, string accName, int accPin);

    bool verifyPin(int inputPin) const;
    void deposit(double amount);
    void withdraw(double amount);
    void display() const;
    void showTransactions() const;
    int getAccountNumber() const;
    string getName() const;
    double getBalance() const;
    int getPin() const;
};

class BankSystem {
private:
    vector<Account> accounts;

public:
    void createAccount();
    void deposit();
    void withdraw();
    void displayAccount();
    void saveToFile();
    void loadFromFile();
};

#endif