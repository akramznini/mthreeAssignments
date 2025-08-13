#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"
#include <string>
#include <map>
#include <iostream>
#include <iomanip>

// string constants
const char* HDR_DATE = "Date";
const char* HDR_DEBIT = "Debit";
const char* HDR_CREDIT = "Credit";
const char* HDR_BAL = "Balance";
const char* DATE_FORMAT = "%Y-%m-%d";

const char* ERR_START_BAL = "starting balance is less than ";
const char* ERR_NAME_LEN = "Customer name should be between 10 and 30 characters.";
const char* ERR_MAX_DEP = "deposit amount is more than 50000 limit.";
const char* ERR_LOW_BAL = "balance after withdrawal is less than ";

const char* LBL_ACC_INFO = "\nAccount Information:\n";
const char* LBL_ACC_NUM = "Account Number: ";
const char* LBL_NAME = "Name: ";
const char* LBL_PHONE = "Phone: ";
const char* LBL_ADDRESS = "Address: ";
const char* LBL_TYPE = "Type: ";
const char* LBL_BAL = "Balance: $";
const char* TYPE_CHEQ = "Chequing";
const char* TYPE_SAV = "Savings";

// ===== Static member init =====
int Account::accountNumberCounter = 1;
std::map<AccountType, int> Account::MIN_ACCOUNT_BALANCES = {
    {AccountType::CHEQUING, 1000},
    {AccountType::SAVINGS,  500}
};

void Account::printTransactions() {
    using std::cout;
    using std::setw;
    using std::left;
    using std::right;
    using std::fixed;
    using std::setprecision;
    using std::put_time;

    cout << "\n" << right
        << setw(10) << HDR_DATE << "|"
        << right << setw(23) << HDR_DEBIT << "|"
        << right << setw(12) << HDR_CREDIT << "|"
        << right << setw(12) << HDR_BAL << "\n";

    for (Transaction t : transactions) {
        const time_t time = t.getDate();
        std::tm* localTime = std::localtime(&time);

        cout << left << setw(12) << put_time(localTime, DATE_FORMAT) << "|"
            << right << setw(12) << fixed << setprecision(2)
            << (t.getType() == TransactionType::DEBIT ? t.getAmount() : 0.0) << "|"
            << right << setw(12) << fixed << setprecision(2)
            << (t.getType() == TransactionType::CREDIT ? t.getAmount() : 0.0) << "|"
            << right << setw(12) << fixed << setprecision(2)
            << t.getBalanceAfterTransaction() << "\n";
    }
}

Account::Account(const std::string& name, const std::string& phoneNumber, const std::string& address,
    AccountType accountType, double startingBalance)
    : name(name), phoneNumber(phoneNumber), address(address),
    accountNumber(Account::accountNumberCounter), accountType(accountType), accountBalance(0) {

    this->deposit(startingBalance);

    if (startingBalance < Account::MIN_ACCOUNT_BALANCES[this->accountType]) {
        throw InsufficientFundsException(std::string(ERR_START_BAL) + std::to_string(Account::MIN_ACCOUNT_BALANCES[this->accountType]));
    }
    if (name.size() > 30 || name.size() < 10) {
        throw CustomerNameException(ERR_NAME_LEN);
    }
    accountNumberCounter++;
}

void Account::deposit(double amount) {
    Transaction transaction(amount, TransactionType::CREDIT, accountBalance);
    if (amount > 50000) {
        throw MaxDepositException(ERR_MAX_DEP);
    }
    accountBalance += amount;
    transactions.push_back(transaction);
}

void Account::withdraw(double amount) {
    if (this->accountBalance - amount < Account::MIN_ACCOUNT_BALANCES[this->accountType]) {
        throw InsufficientFundsException(std::string(ERR_LOW_BAL) + std::to_string(Account::MIN_ACCOUNT_BALANCES[this->accountType]));
    }
    Transaction transaction(amount, TransactionType::DEBIT, accountBalance);
    accountBalance -= amount;
    transactions.push_back(transaction);
}

double Account::getBalance() { return accountBalance; }
int Account::getAccountNumber() { return accountNumber; }
std::string Account::getPhoneNumber() { return phoneNumber; }
std::string Account::getAddress() { return address; }
std::string Account::getName() { return name; }

std::ostream& operator<<(std::ostream& os, const Account& acc) {
    os << LBL_ACC_INFO
        << LBL_ACC_NUM << acc.accountNumber << "\n"
        << LBL_NAME << acc.name << "\n"
        << LBL_PHONE << acc.phoneNumber << "\n"
        << LBL_ADDRESS << acc.address << "\n"
        << LBL_TYPE << (acc.accountType == AccountType::CHEQUING ? TYPE_CHEQ : TYPE_SAV) << "\n"
        << LBL_BAL << acc.accountBalance << "\n";
    return os;
}
