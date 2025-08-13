#include "Transaction.h";
using namespace std;

Transaction::Transaction(double amount, TransactionType type, double accountBalance) :
	amount(amount), type(type), balanceAfterTransaction((type == TransactionType::CREDIT) ? accountBalance + amount : accountBalance - amount) {}

double Transaction::getAmount() {
	return amount;
}
TransactionType Transaction::getType() {
	return type;
}
const time_t Transaction::getDate() {
	return date;
}
double Transaction::getBalanceAfterTransaction() {
	return balanceAfterTransaction;
}