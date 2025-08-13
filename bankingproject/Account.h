#pragma once
#include <string>
#include <ctime>
#include "Transaction.h"
#include <vector>
#include "BankingExceptions.h"
#include <iostream>
#include <map>
using namespace std;

enum AccountType {
	SAVINGS,
	CHEQUING
};

class Account {
public:
	static map<AccountType, int> MIN_ACCOUNT_BALANCES;
	const static int MIN_BALANCE_SAVINGS = 500;
	const static int MIN_BALANCE_CHEQUING = 1000;
	Account(const string& name, const string& phoneNumber, const string& address,
	AccountType accountType, double startingBalance);
	void deposit(double amount);
	void withdraw(double amount);
	double getBalance();
	int getAccountNumber();
	string getPhoneNumber();
	string getAddress();
	string getName();
	void printTransactions();
	friend ostream& operator<<(ostream& os, const Account& acc);
private:
	static int accountNumberCounter;
	string name;
	string phoneNumber;
	string address;
	const time_t creationDate = time(0);
	const int accountNumber;
	const AccountType accountType;
	double accountBalance;
	vector<Transaction> transactions;
};