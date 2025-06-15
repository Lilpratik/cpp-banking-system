// we'll define:
// Account struct
// Array of accounts
// Function declaration

#ifndef BANK_H
#define BANK_H

#include <iostream>
using namespace std;

struct Account {
  string name;
  int accountNumber;
  float balance;
  int pin;
  bool isActive;
};


const int MAX_ACCOUNTS = 100;
extern Account account[MAX_ACCOUNTS];
extern int accountCount;

// Function Declarations
void createAccount();
void deposit();
void withdraw();
void checkBalance();
int login(int enteredAccountNumber, int enteredPin);

void saveAccountsToFile();
void loadAccountsFromFile();

void changePin();
void deleteAccount();

#endif
