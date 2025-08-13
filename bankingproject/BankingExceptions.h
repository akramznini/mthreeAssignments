#pragma once
#include <stdexcept>
#include <string>

// string constants
static const char* PREFIX_CUSTOMER_NAME = "CustomerNameException: ";
static const char* PREFIX_INSUFFICIENT_FUNDS = "InsufficientFundsException: ";
static const char* PREFIX_MAX_DEPOSIT = "MaxDepositException: ";

class BankingException : public std::runtime_error {
public:
    explicit BankingException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class CustomerNameException : public BankingException {
public:
    explicit CustomerNameException(const std::string& detail)
        : BankingException(std::string(PREFIX_CUSTOMER_NAME) + detail) {}
};

class InsufficientFundsException : public BankingException {
public:
    explicit InsufficientFundsException(const std::string& detail)
        : BankingException(std::string(PREFIX_INSUFFICIENT_FUNDS) + detail) {}
};

class MaxDepositException : public BankingException {
public:
    explicit MaxDepositException(const std::string& detail)
        : BankingException(std::string(PREFIX_MAX_DEPOSIT) + detail) {}
};
