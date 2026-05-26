#include "ATM.h"

#include <algorithm>
#include <iostream>
#include <limits>

ATM::ATM() : accounts{BankAccount("Nishant", 1000.0, "1234"), BankAccount("Yana", 1500.0, "5678"), BankAccount("Aarav", 1200.0, "9999")}, currentAccount(nullptr), loggedIn(false) {}

void ATM::showMenu() const {
    std::cout << "\n===== ATM Machine =====\n";
    if (currentAccount != nullptr) {
        std::cout << "Logged in as: " << currentAccount->getOwnerName() << "\n";
    }
    std::cout << "1. Check Balance\n";
    std::cout << "2. Deposit Money\n";
    std::cout << "3. Withdraw Money\n";
    std::cout << "4. View Transaction History\n";
    std::cout << "5. Logout\n";
    std::cout << "6. Exit\n";
    std::cout << "========================\n";
    std::cout << "Enter your choice: ";
}

void ATM::run() {
    int choice;

    while (true) {
        if (!hasActiveSession() && !login()) {
            continue;
        }

        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInput();
            std::cout << "Invalid input. Please enter a number from 1 to 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                showTransactionHistory();
                break;
            case 5:
                loggedIn = false;
                currentAccount = nullptr;
                std::cout << "Logged out successfully.\n";
                break;
            case 6:
                std::cout << "Thank you for using the ATM. Goodbye!\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

bool ATM::login() {
    std::string username;
    std::string pin;

    std::cout << "\n===== Secure Login =====\n";
    std::cout << "Enter username: ";
    std::cin >> username;

    if (std::cin.fail()) {
        clearInput();
        std::cout << "Invalid username input. Please try again.\n";
        return false;
    }

    std::cout << "Enter PIN: ";
    std::cin >> pin;

    if (std::cin.fail()) {
        clearInput();
        std::cout << "Invalid PIN input. Please try again.\n";
        return false;
    }

    BankAccount* account = findAccount(username);
    if (account == nullptr) {
        std::cout << "Username not found. Please try again.\n";
        return false;
    }

    if (!account->authenticate(pin)) {
        std::cout << "Incorrect PIN. Access denied.\n";
        return false;
    }

    currentAccount = account;
    loggedIn = true;
    std::cout << "Login successful. Welcome, " << currentAccount->getOwnerName() << "!\n";
    return true;
}

BankAccount* ATM::findAccount(const std::string& username) {
    auto it = std::find_if(accounts.begin(), accounts.end(), [&](const BankAccount& account) {
        return account.getOwnerName() == username;
    });

    if (it == accounts.end()) {
        return nullptr;
    }

    return &(*it);
}

const BankAccount* ATM::findAccount(const std::string& username) const {
    auto it = std::find_if(accounts.begin(), accounts.end(), [&](const BankAccount& account) {
        return account.getOwnerName() == username;
    });

    if (it == accounts.end()) {
        return nullptr;
    }

    return &(*it);
}

void ATM::checkBalance() const {
    if (!hasActiveSession()) {
        std::cout << "No active session. Please login first.\n";
        return;
    }

    std::cout << "Current balance: $" << currentAccount->getBalance() << "\n";
}

void ATM::depositMoney() {
    if (!hasActiveSession()) {
        std::cout << "No active session. Please login first.\n";
        return;
    }

    double amount;
    std::cout << "Enter amount to deposit: ";
    std::cin >> amount;

    if (std::cin.fail() || amount <= 0) {
        clearInput();
        std::cout << "Invalid amount. Please enter a positive number.\n";
        return;
    }

    if (currentAccount->deposit(amount)) {
        std::cout << "Successfully deposited $" << amount << "\n";
    } else {
        std::cout << "Deposit failed. Please try again.\n";
    }
}

void ATM::withdrawMoney() {
    if (!hasActiveSession()) {
        std::cout << "No active session. Please login first.\n";
        return;
    }

    double amount;
    std::cout << "Enter amount to withdraw: ";
    std::cin >> amount;

    if (std::cin.fail() || amount <= 0) {
        clearInput();
        std::cout << "Invalid amount. Please enter a positive number.\n";
        return;
    }

    if (currentAccount->withdraw(amount)) {
        std::cout << "Successfully withdrew $" << amount << "\n";
    } else {
        std::cout << "Insufficient balance or invalid amount.\n";
    }
}

void ATM::showTransactionHistory() const {
    if (!hasActiveSession()) {
        std::cout << "No active session. Please login first.\n";
        return;
    }

    const auto history = currentAccount->getTransactionHistory();
    std::cout << "\n===== Transaction History =====\n";

    if (history.empty()) {
        std::cout << "No transactions yet.\n";
        return;
    }

    for (const auto& entry : history) {
        std::cout << entry << "\n";
    }
}

bool ATM::hasActiveSession() const {
    return loggedIn && currentAccount != nullptr;
}

void ATM::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
