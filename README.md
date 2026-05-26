# Nishant-ATM

A simple C++ ATM console project with separate files for easy collaboration.

## Features

- PIN-based login
- Multiple user accounts
- Balance checking
- Deposit and withdrawal
- Transaction history
- Simple `Makefile` for building

## Sample users

- Nishant / 1234
- Yana / 5678
- Aarav / 9999

## How to build and run

```bash
make
./atm
```

## Example usage

```text
Enter username: Nishant
Enter PIN: 1234

1. Check Balance
2. Deposit Money
3. Withdraw Money
4. View Transaction History
5. Logout
6. Exit

Enter your choice: 2
Enter amount to deposit: 50
Successfully deposited $50

Enter your choice: 4

===== Transaction History =====
Initial balance: $1000.00
Deposited $50.00

Enter your choice: 5
Logged out successfully.
```

## Project files

- `main.cpp` : program entry point
- `ATM.h` / `ATM.cpp` : ATM flow and menu logic
- `BankAccount.h` / `BankAccount.cpp` : account logic and transaction history
- `Makefile` : build command
