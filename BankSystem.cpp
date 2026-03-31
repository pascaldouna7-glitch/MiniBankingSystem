#include "BankSystem.h"
#include <fstream>

// Constructor
Account::Account(int accNo, string accName, int accPin) {
    accountNumber = accNo;
    name = accName;
    pin = accPin;
    balance = 0;
}

// Verify PIN
bool Account::verifyPin(int inputPin) const
{
    return inputPin == pin;
}
string Account::getName() const {
    return name;
}

double Account::getBalance() const {
    return balance;
}

int Account::getPin() const {
    return pin;
}
// Deposit
void Account::deposit(double amount)
{
    balance += amount;
    transactions.push_back("Deposited: " + to_string(amount));
    cout << "\033[32m✔ Deposit Successful!\033[0m\n";
}

// Withdraw
void Account::withdraw(double amount)
{
    if (amount > balance)
    {
        cout << "\033[31m✘ Insufficient Balance!\033[0m\n";
        return;
    }
    balance -= amount;
    transactions.push_back("Withdrawn: " + to_string(amount));
    cout << "\033[32m✔ Withdrawal Successful!\033[0m\n";
}

// Display Account
void Account::display() const
{
    cout << "\033[36m\n--- Account Details ---\033[0m\n";
    cout << "Account No: " << accountNumber << endl;
    cout << "Name: " << name << endl;
    cout << "Balance: " << balance << endl;
}

// Transactions
void Account::showTransactions() const
{
    cout << "\033[33m\nTransaction History:\033[0m\n";
    if (transactions.empty())
    {
        cout << "No transactions yet.\n";
    }
    else
    {
        for (auto t : transactions)
        {
            cout << "- " << t << endl;
        }
    }
}

int Account::getAccountNumber() const
{
    return accountNumber;
}

// ================= BANK SYSTEM =================

void BankSystem::createAccount()
{
    int accNo, pin;
    string name;

    cout << "Enter Account Number: ";
    cin >> accNo;

    // Check if account already exists
    for (auto &acc : accounts)
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "\033[31m✘ Account Already Exists!\033[0m\n";
            return;
        }
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Set PIN: ";
    cin >> pin;

    accounts.push_back(Account(accNo, name, pin));
    cout << "\033[32m✔ Account Created Successfully!\033[0m\n";
}

void BankSystem::deposit()
{
    int accNo, pin;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    for (auto &acc : accounts)
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "Enter PIN: ";
            cin >> pin;

            if (!acc.verifyPin(pin))
            {
                cout << "\033[31m✘ Wrong PIN!\033[0m\n";
                return;
            }

            cout << "Enter Amount: ";
            cin >> amount;
            if (amount <= 0)
            {
                cout << "\033[31m✘ Invalid amount!\033[0m\n";
                return;
            }
            acc.deposit(amount);
            return;
        }
    }
    cout << "\033[31m✘ Account Not Found!\033[0m\n";
}

void BankSystem::withdraw()
{
    int accNo, pin;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;

    for (auto &acc : accounts)
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "Enter PIN: ";
            cin >> pin;

            if (!acc.verifyPin(pin))
            {
                cout << "\033[31m✘ Wrong PIN!\033[0m\n";
                return;
            }

            cout << "Enter Amount: ";
            cin >> amount;
            if (amount <= 0)
            {
                cout << "\033[31m✘ Invalid amount!\033[0m\n";
                return;
            }
            acc.withdraw(amount);
            return;
        }
    }
    cout << "\033[31m✘ Account Not Found!\033[0m\n";
}

void BankSystem::displayAccount()
{
    int accNo, pin;

    cout << "Enter Account Number: ";
    cin >> accNo;

    for (auto &acc : accounts)
    {
        if (acc.getAccountNumber() == accNo)
        {
            cout << "Enter PIN: ";
            cin >> pin;

            if (!acc.verifyPin(pin))
            {
                cout << "\033[31m✘ Wrong PIN!\033[0m\n";
                return;
            }

            acc.display();
            acc.showTransactions();
            return;
        }
    }
    cout << "\033[31m✘ Account Not Found!\033[0m\n";
}

void BankSystem::saveToFile() {
    ofstream file("accounts.txt");

    for (auto &acc : accounts) {
        file << acc.getAccountNumber() << ","
             << acc.getName() << ","
             << acc.getPin() << ","
             << acc.getBalance() << endl;
    }

    file.close();
}

void BankSystem::loadFromFile() {
    ifstream file("accounts.txt");
    string line;

    accounts.clear(); // Clear existing accounts

    while (getline(file, line)) {
        if (line.empty()) continue;

        // Check if it's CSV format (contains commas)
        if (line.find(',') != string::npos) {
            // Parse CSV format: accNo,name,pin,balance
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                int accNo = stoi(line.substr(0, pos1));
                string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                int pin = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
                double balance = stod(line.substr(pos3 + 1));

                accounts.push_back(Account(accNo, name, pin));
                // Set the balance by depositing the saved amount
                if (balance > 0) {
                    accounts.back().deposit(balance);
                }
            }
        } else {
            // Parse space-separated format: accNo name pin balance
            stringstream ss(line);
            int accNo, pin;
            string name;
            double balance;

            if (ss >> accNo >> name >> pin >> balance) {
                accounts.push_back(Account(accNo, name, pin));
                // Set the balance by depositing the saved amount
                if (balance > 0) {
                    accounts.back().deposit(balance);
                }
            }
        }
    }

    file.close();
}