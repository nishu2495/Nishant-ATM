#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>

class BankAccount {
private:
    std::string ownerName;
    double balance;
    std::string pin;
    std::vector<std::string> transactionHistory;

public:
    BankAccount(const std::string& owner, double initialBalance = 1000.0, const std::string& pinCode = "1234");
    std::string getOwnerName() const;
    double getBalance() const;
    bool authenticate(const std::string& enteredPin) const;
    bool deposit(double amount);
    bool withdraw(double amount);
    std::vector<std::string> getTransactionHistory() const;
};

#endif
