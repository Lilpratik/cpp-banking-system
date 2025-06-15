#include <iostream>
#include <string>
#include "bank.h"
#include <fstream>
using namespace std;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;


int main() {
    int choice;

    // calling funcs
    loadAccountsFromFile();

    while (true) {
        cout << "\n=== Simple Banking System ===\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Change PIN\n";
	cout << "6. Delete Account\n";
	cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
	    case 5: changePin(); break;
  	    case 6: deleteAccount(); break;
	case 7: cout << "Thank you for using the system!\n"; saveAccountsToFile(); return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }
    saveAccountsToFile();
}



void createAccount() {
  if (accountCount >= MAX_ACCOUNTS) {
    cout << "Bank is full. Cannot create more accounts.\n";
    return;
  }

  Account newAccount;

  cout << "Enter your name: ";
  cin.ignore(); // clear input buffer before getline
  getline(cin, newAccount.name);

  cout << "Enter account number: ";
  cin >> newAccount.accountNumber;

  // Check is acount number already exists
  for (int i = 0; i < accountCount; ++i) {
    if (accounts[i].accountNumber == newAccount.accountNumber) {
      cout << "Account number already exists. Try again.\n";
      return;
    }
  }

  cout << "Enter initial deposit: ";
  cin >> newAccount.balance;

  if (newAccount.balance < 0) {
    cout << "Initial deposit cannot be negative.\n";
    newAccount.balance = 0;
  }

  cout << "Set a 4-digit PIN: ";
  cin >> newAccount.pin;

  if (newAccount.pin < 1000 || newAccount.pin > 9999) {
    cout << "Invaild PIN. Must be a 4-digit number.\n";
    return;
  }

  newAccount.isActive = true;

  // save to global accounts array
  accounts[accountCount] = newAccount;
  accountCount++;

  cout << "Account created successfully!\n";
}

int login(int enteredAccountNumber, int enteredPin) {
  for (int i = 0; i < accountCount; ++i) {
    if (accounts[i].accountNumber == enteredAccountNumber) {
      if (accounts[i].pin == enteredPin) {
	return i; // successfully login
      } else {
	cout << "Incorrect PIN.\n";
	return -1;
      }
    }
  }
  cout << "Account not found.\n";
  return -1;
}

void deposit() {
  int accNo, pin;
  cout << "Enter your account number: ";
  cin >> accNo;
  cout << "Enter your 4-digit PIN: ";
  cin >> pin;

  int index = login(accNo, pin);

  if (index == -1) {
    cout << "Login failed. Cannot proceed.\n";
    return;
  }

  float amount;
  cout << "Enter amount to deposit: ";
  cin >> amount;

  if (amount <= 0) {
    cout << "Invalid amount. Please enter a positive number.\n";
    return;
  }

  accounts[index].balance += amount;
  cout << "Amount deposited successfully!\n";
  cout << "New Balance: ₹" << accounts[index].balance << endl;
}

void withdraw() {
  int accNo, pin;
  cout << "Enter your account number: ";
  cin >> accNo;
  cout << "Enter your 4-digit PIN: ";
  cin >> pin;

  int index = login(accNo, pin);

  if (index == -1) {
    cout << "Login failed. Cannot proceed.\n";
    return;
  }

  float amount;
  cout << "Enter amount to withdraw: ";
  cin >> amount;

  if (amount <= 0) {
    cout << "Invaild amount. Please enter a positive number.\n";
    return;
  }

  if (amount > accounts[index].balance) {
    cout << "Insufficient balance. Transaction cancelled.\n";
    return;
  }

  accounts[index].balance -= amount;
  cout << "Amount withdrawn successfully!\n";
  cout << "Remaining Balance: ₹" << accounts[index].balance << endl;
}


void checkBalance() {
  int accNo, pin;
  cout << "Enter your account number: ";
  cin >> accNo;
  cout << "Enter your 4-digit PIN: ";
  cin >> pin;

  int index = login(accNo, pin);

  if (index == -1) {
    cout << "Login failed. Cannot proceed.\n";
    return;
  }

  cout << "\n==== Account Details ====\n";
  cout << "Name: " << accounts[index].name << endl;
  cout << "Account Number: " << accounts[index].accountNumber << endl;
  cout << "Current Balance: ₹" << accounts[index].balance << endl;
}


void saveAccountsToFile() {
  ofstream file("accounts.txt");
  if (!file) {
    cout << "Error saving accounts to file.\n";
    return;
  }

  for (int i = 0; i < accountCount; ++i) {
    if (accounts[i].isActive) {
      file << accounts[i].name << endl;
      file << accounts[i].accountNumber << endl;
      file << accounts[i].balance << endl;
      file << accounts[i].pin << endl;
      file << accounts[i].isActive << endl;
    }
  }

  file.close();
  cout << "Accounts saved successfully!\n";
}

void loadAccountsFromFile() {
  ifstream file("accounts.txt");
  if (!file) {
    cout << "No saved accounts found.\n";
    return;
  }

  accountCount = 0;
  while (file && accountCount < MAX_ACCOUNTS) {
    Account acc;
    getline(file, acc.name);
    file >> acc.accountNumber;
    file >> acc.balance;
    file >> acc.pin;
    file >> acc.isActive;
    file.ignore();   // skip newline before next name
    accounts[accountCount++] = acc;
  }

  file.close();
  cout << "Accounts loaded successfully!\n";
}


void changePin() {
  int accNo, pin;
  cout << "Enter your account number: ";
  cin >> accNo;
  cout << "Enter current 4-digit PIN: ";
  cin >> pin;

  int index = login(accNo, pin);
  if (index == -1) {
    cout << "Login failed. Cannot change PIN.\n";
    return;
  }

  int newPin;
  cout << "Enter new 4-digit PIN: ";
  cin >> newPin;

  if (newPin < 1000 || newPin > 9999) {
    cout << "Invalid PIN. Must be a 4-digit number.\n";
    return;
  }

  accounts[index].pin = newPin;
  cout << "PIN changed successfully!\n";
}

void deleteAccount() {
  int accNo, pin;
  cout << "Enter your account number: ";
  cin >> accNo;
  cout << "Enter your 4-digit PI: ";
  cin >> pin;

  int index = login(accNo, pin);
  if (index == -1) {
    cout << "Login failed. Cannot delete account.\n";
    return;
  }

  char confirm;
  cout << "Are you sure you want to delete this accoun? (y/n): ";
  cin >> confirm;
  if (confirm == 'y' || confirm == 'Y') {
    accounts[index].isActive = false;
    cout << "Account deactivated successfully.\n";
  } else {
    cout << "Account deletion cancelled.\n";
  }
}
