#pragma once
#include <ctime>;
enum TransactionType {
	DEBIT,
	CREDIT
};

class Transaction {
public:
	Transaction(double amount, TransactionType type, double accountBalance);
	double getAmount();
	TransactionType getType();
	const time_t getDate();
	double getBalanceAfterTransaction();
private:
	double balanceAfterTransaction;
	double amount;
	TransactionType type;
	const time_t date = time(0);
};