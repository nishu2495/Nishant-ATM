#ifndef ATM_H
#define ATM_H

#include "BankAccount.h"

#include <string>
#include <vector>

class ATM {
private:
    std::vector<BankAccount> accounts;
    BankAccount* currentAccount;
    bool loggedIn;

public:
    ATM();
    void showMenu() const;
    void run();

private:
    bool login();
    BankAccount* findAccount(const std::string& username);
    const BankAccount* findAccount(const std::string& username) const;
    void checkBalance() const;
    void depositMoney();
    void withdrawMoney();
    void showTransactionHistory() const;
    bool hasActiveSession() const;
    void clearInput();
};

#endif
