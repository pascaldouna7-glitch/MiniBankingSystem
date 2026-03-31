#include "BankSystem.h"

int main() {
    cout << "\033[1;32m";
    cout << "=====================================\n";
    cout << "   WELCOME TO MINI BANKING SYSTEM\n";
    cout << "=====================================\n";
    cout << "\033[0m";

    BankSystem bank;
    int choice;

    // Load accounts at startup
    bank.loadFromFile();

    do {
        cout << "\033[1;34m";
        cout << "\n╔══════════════════════════════╗\n";
        cout << "║   🏦 MINI BANKING SYSTEM     ║\n";
        cout << "╠══════════════════════════════╣\n";
        cout << "║ 1. Create Account           ║\n";
        cout << "║ 2. Deposit                  ║\n";
        cout << "║ 3. Withdraw                 ║\n";
        cout << "║ 4. View Account             ║\n";
        cout << "║ 5. Exit                     ║\n";
        cout << "╚══════════════════════════════╝\n";
        cout << "\033[0m";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: bank.createAccount(); bank.saveToFile(); break;
            case 2: bank.deposit(); bank.saveToFile(); break;
            case 3: bank.withdraw(); bank.saveToFile(); break;
            case 4: bank.displayAccount(); break;
            case 5: bank.saveToFile(); cout << "\033[32mThank you!\033[0m\n"; break;
            default: cout << "\033[31mInvalid Choice!\033[0m\n";
        }

    } while(choice != 5);

    return 0;
}