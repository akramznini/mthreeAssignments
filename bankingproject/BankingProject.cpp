#include <iostream>
#include <iomanip>
#include <cctype>
#include "Account.h"
#include <algorithm>
#include <vector>
#include <limits>

// string constants
const char* WELCOME_MESSAGE = " Welcome to Mthree Bank ";
const char* MAIN_MENU = "\nPlease choose an option:\n1.open account\n2.login\n0.quit";
const char* SELECT_OPTION = "Please select a valid option:";
const char* BUSINESS_NAME_PROMPT = "Business name: ";
const char* PHONE_PROMPT = "\nPlease enter a valid phone number: ";
const char* ADDRESS_PROMPT = "\nAddress: ";
const char* ACCOUNT_TYPE_PROMPT = "\nPlease choose an account type: 1.Chequing 2.Savings";
const char* ACCOUNT_TYPE_INVALID = "\nPlease choose a valid type: ";
const char* START_BAL_PROMPT = "\nPlease enter your starting balance: ";
const char* ACCOUNT_NUMBER_PROMPT = "\nPlease enter account number: ";
const char* WELCOME_USER_PREFIX = "\nWelcome, ";
const char* LOGIN_MENU = "\nPlease choose an option:\n1.Deposit\n2.Withrawal\n3.Show Transactions\n4.Show Account Info\n0.Logout";
const char* DEPOSIT_PROMPT = "\nPlease enter deposit amount: ";
const char* BALANCE_LABEL = "\nBalance: ";
const char* WITHDRAW_PROMPT = "\nPlease enter withdrawal amount: ";
const char* ACCOUNT_NOT_FOUND = "\nAccount Not Found.\n";

bool isValidPhoneNumber(const std::string& phone) {
    return phone.size() == 10 &&
        std::all_of(phone.begin(), phone.end(), [](unsigned char ch) {
        return std::isdigit(ch);
            });
}

void generateMockAccounts(std::vector<Account>& accounts) {
    
    // account number 1
    Account account1("Gary Incorporated", "4399990909", "9702 Basil Street, Montreal", AccountType::CHEQUING, 1200);
    account1.deposit(500);
    account1.withdraw(600);
    account1.deposit(1000);

    accounts.push_back(account1);

    // account number 2
    Account account2("Bakery LLC", "1800989999", "8719 Sackville Street, Montreal", AccountType::SAVINGS, 800);
    account2.deposit(2300);
    account2.withdraw(897);
    account2.deposit(332);

    accounts.push_back(account2);

    // account number 3
    Account account3("Bookshop INC", "5564738790", "929 Lajeunesse Street, Montreal", AccountType::CHEQUING, 13000);
    account3.deposit(30000);
    account3.withdraw(17234);
    account3.deposit(98);

    accounts.push_back(account3);
}

int main() {
    std::vector<Account> accounts;
    generateMockAccounts(accounts);
    int action = -1;

    std::cout << std::setw(12) << std::setfill('-') << "";
    std::cout << WELCOME_MESSAGE;
    std::cout << std::setw(12) << std::setfill('-') << "" << std::endl;

    while (action != 0) {
        std::cout << MAIN_MENU << std::endl;
        std::cin >> action;
        if (action != 0 && action != 1 && action != 2) {
            std::cout << SELECT_OPTION << std::endl;
            continue;
        }
        if (action == 1) {
            std::string name;
            std::string phoneNumber;
            std::string address;
            AccountType accountType;
            double startingBalance;

            std::cout << BUSINESS_NAME_PROMPT;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, name);

            while (true) {
                std::cout << PHONE_PROMPT;
                std::getline(std::cin, phoneNumber);
                if (isValidPhoneNumber(phoneNumber)) break;
            }

            std::cout << ADDRESS_PROMPT;
            std::getline(std::cin, address);

            int type;
            std::cout << ACCOUNT_TYPE_PROMPT;
            std::cin >> type;
            while (type != 1 && type != 2) {
                std::cout << ACCOUNT_TYPE_INVALID;
                std::cin >> type;
            }
            accountType = (type == 1) ? AccountType::CHEQUING : AccountType::SAVINGS;

            std::cout << START_BAL_PROMPT;
            std::cin >> startingBalance;

            try {
                Account account(name, phoneNumber, address, accountType, startingBalance);
                accounts.push_back(account);
                std::cout << account << std::endl;
            }
            catch (BankingException exception) {
                std::cout << exception.what() << std::endl;
                continue;
            }

        }
        else if (action == 2) {
            int accountNumber;
            std::cout << ACCOUNT_NUMBER_PROMPT;
            std::cin >> accountNumber;
            try {
                Account& account = accounts.at(accountNumber - 1);
                int innerAction = -1;

                std::cout << WELCOME_USER_PREFIX << account.getName() << "!\n";

                while (innerAction != 0) {
                    std::cout << LOGIN_MENU;
                    std::cin >> innerAction;
                    if (innerAction < 0 || innerAction > 4) {
                        std::cout << SELECT_OPTION << std::endl;
                        continue;
                    }
                    if (innerAction == 0) break;
                    if (innerAction == 1) {
                        std::cout << DEPOSIT_PROMPT;
                        int depositAmount;
                        std::cin >> depositAmount;
                        try {
                            account.deposit(depositAmount);
                            std::cout << BALANCE_LABEL << account.getBalance();
                        }
                        catch (BankingException e) {
                            std::cout << e.what() << std::endl;
                            continue;
                        }
                    }

                    if (innerAction == 2) {
                        std::cout << WITHDRAW_PROMPT;
                        int withdrawalAmount;
                        std::cin >> withdrawalAmount;
                        try {
                            account.withdraw(withdrawalAmount);
                            std::cout << BALANCE_LABEL << account.getBalance() << "\n";
                        }
                        catch (BankingException e) {
                            std::cout << e.what() << std::endl;
                            continue;
                        }
                    }

                    if (innerAction == 3) {
                        account.printTransactions();
                    }

                    if (innerAction == 4) {
                        std::cout << '\n' << account;
                    }
                    innerAction = -1;
                }
            }
            catch (...) {
                std::cout << ACCOUNT_NOT_FOUND;
            }
        }
        action = -1;
    }
}
