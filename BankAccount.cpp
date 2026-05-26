#include "BankAccount.h"

#include <iomanip>
#include <sstream>

namespace {
std::string formatAmount(double amount) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << amount;
    return "$" + stream.str();
}
} // namespace

BankAccount::BankAccount(const std::string& owner, double initialBalance, const std::string& pinCode)
    : ownerName(owner), balance(initialBalance), pin(pinCode) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << initialBalance;
    transactionHistory.push_back("Initial balance: $" + stream.str());
}

std::string BankAccount::getOwnerName() const {
    return ownerName;
}

double BankAccount::getBalance() const {
    return balance;
}

bool BankAccount::authenticate(const std::string& enteredPin) const {
    return enteredPin == pin;
}

bool BankAccount::deposit(double amount) {
    if (amount <= 0) {
        return false;
    }

    balance += amount;
    transactionHistory.push_back("Deposited " + formatAmount(amount));
    return true;
}

bool BankAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) {
        return false;
    }

    balance -= amount;
    transactionHistory.push_back("Withdrawn " + formatAmount(amount));
    return true;
}

std::vector<std::string> BankAccount::getTransactionHistory() const {
    return transactionHistory;
}
