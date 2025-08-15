#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>
#include <limits>
#include "Library.h"
#include "LoginManager.h"

const std::string STR_DATE_TIME_FORMAT = "%Y-%m-%d %H:%M:%S";
const std::string STR_DATE_FORMAT = "%Y-%m-%d";
const std::string STR_BOOK_TYPE_PROMPT = "Book type (1=physical, 2=ebook, 3=voice, 4=video): ";
const std::string STR_BOOK_NAME_PROMPT = "Book name: ";
const std::string STR_AUTHOR_PROMPT = "Author: ";
const std::string STR_PURCHASE_DATE_PROMPT = "Purchase date (YYYY-MM-DD): ";
const std::string STR_LIBRARY_TITLE = "\nLibrary Management System\n";
const std::string STR_MENU_OPTION_1 = "1. Login validation\n";
const std::string STR_MENU_OPTION_2 = "2. Add book\n";
const std::string STR_MENU_OPTION_3 = "3. List all books\n";
const std::string STR_MENU_OPTION_4 = "4. Update book\n";
const std::string STR_MENU_OPTION_5 = "5. Delete book\n";
const std::string STR_MENU_OPTION_6 = "6. Rent/issue a book\n";
const std::string STR_MENU_OPTION_7 = "7. Renew a book\n";
const std::string STR_MENU_OPTION_8 = "8. Display available & rented details\n";
const std::string STR_MENU_OPTION_9 = "9. Search by BookName\n";
const std::string STR_MENU_OPTION_10 = "10. Return a book\n";
const std::string STR_MENU_OPTION_0 = "0. Exit\n";
const std::string STR_MENU_CHOICE = "Choice: ";
const std::string STR_USERNAME_PROMPT = "Username: ";
const std::string STR_PASSWORD_PROMPT = "Password: ";
const std::string STR_LOGIN_SUCCESS = "Login successful.\n";
const std::string STR_LOGIN_FAIL = "Invalid credentials.\n";
const std::string STR_LOGIN_FIRST = "Please login first.\n";
const std::string STR_ADD_BOOK_MSG = "Adding a book.\n";
const std::string STR_BOOK_ADDED = "Book added.\n";
const std::string STR_BOOK_ADD_FAIL = "Failed to add book.\n";
const std::string STR_NO_BOOKS = "No books.\n";
const std::string STR_ENTER_BOOKCODE_UPDATE = "Enter BookCode to update: ";
const std::string STR_ENTER_NEW_DETAILS = "Enter new details (BookCode will remain the same):\n";
const std::string STR_UPDATED = "Updated.\n";
const std::string STR_NOT_FOUND = "Not found.\n";
const std::string STR_ENTER_BOOKCODE_DELETE = "Enter BookCode to delete: ";
const std::string STR_DELETED = "Deleted.\n";
const std::string STR_BOOKCODE_RENT = "BookCode to rent: ";
const std::string STR_LENDER_NAME = "Lender name: ";
const std::string STR_PHONE_NO = "Phone no: ";
const std::string STR_RENT_RECORDED = "Rent recorded.\n";
const std::string STR_RENT_FAIL = "Failed (book code not found or no copies available).\n";
const std::string STR_BOOKCODE_RENEW = "BookCode to renew: ";
const std::string STR_NEW_RETURN_DATE = "New return date (YYYY-MM-DD), leave empty to +7 days: ";
const std::string STR_RENEWED = "Renewed.\n";
const std::string STR_ALL_BOOKS = "\n--- All Books ---\n";
const std::string STR_RENTED_OUT = "\n--- Rented Out ---\n";
const std::string STR_NONE = "None.\n";
const std::string STR_SEARCH_BOOKNAME = "Enter BookName to search: ";
const std::string STR_BOOKS_FOUND_PREFIX = "\nBooks found for \"";
const std::string STR_RENTS_FOUND_PREFIX = "\nRents found for \"";
const std::string STR_AVAILABLE_QTY_PREFIX = "\nAvailable qty: ";
const std::string STR_TOTAL = "  (total ";
const std::string STR_RENTED = " - rented ";
const std::string STR_BOOKCODE_RETURN = "BookCode to return: ";
const std::string STR_RETURN_SUCCESS = "Book returned successfully.\n";
const std::string STR_RETURN_FAIL = "No active rental found for that BookCode.\n";
const std::string STR_INVALID_CHOICE = "Invalid choice.\n";
const std::string STR_GOODBYE = "Goodbye!\n";

static std::string nowDateTime() {
    using namespace std::chrono;
    std::time_t t = system_clock::to_time_t(system_clock::now());
    std::tm tm;
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[32];
    std::strftime(buf, sizeof(buf), STR_DATE_TIME_FORMAT.c_str(), &tm);
    return std::string(buf);
}

static std::string plusDays(int days) {
    using namespace std::chrono;
    std::time_t t = system_clock::to_time_t(system_clock::now() + hours(24 * days));
    std::tm tm;
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[16];
    std::strftime(buf, sizeof(buf), STR_DATE_FORMAT.c_str(), &tm);
    return std::string(buf);
}

static BookType askBookType() {
    std::cout << STR_BOOK_TYPE_PROMPT;
    int ch; std::cin >> ch;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch (ch) {
    case 1: return BookType::Physical;
    case 2: return BookType::Ebook;
    case 3: return BookType::Voice;
    case 4: return BookType::Video;
    default: return BookType::Unknown;
    }
}

static Book promptBookNoCode() {
    Book b;
    std::cout << STR_BOOK_NAME_PROMPT; std::getline(std::cin, b.name);
    std::cout << STR_AUTHOR_PROMPT; std::getline(std::cin, b.author);
    std::cout << STR_PURCHASE_DATE_PROMPT; std::getline(std::cin, b.purchaseDate);
    b.type = askBookType();
    return b;
}

static void printBook(const Book& b) {
    std::cout << b.code << " | " << b.name << " | " << b.author
        << " | " << b.purchaseDate << " | " << Book::toString(b.type) << "\n";
}

static void printRent(const RentRecord& r) {
    std::cout << r.bookCode << " | " << r.bookName << " | " << r.bookAuthor
        << " | " << Book::toString(r.type) << " | Lender: " << r.lenderName
        << " | Rent: " << r.rentDateTime << " | Return: " << r.returnDate
        << " | Phone: " << r.phone << "\n";
}

static void menu() {
    std::cout << STR_LIBRARY_TITLE
        << STR_MENU_OPTION_1
        << STR_MENU_OPTION_2
        << STR_MENU_OPTION_3
        << STR_MENU_OPTION_4
        << STR_MENU_OPTION_5
        << STR_MENU_OPTION_6
        << STR_MENU_OPTION_7
        << STR_MENU_OPTION_8
        << STR_MENU_OPTION_9
        << STR_MENU_OPTION_10
        << STR_MENU_OPTION_0
        << STR_MENU_CHOICE;
}

int main() {
    Library lib;
    LoginManager auth;
    bool loggedIn = false;
    while (true) {
        menu();
        int choice;
        if (!(std::cin >> choice)) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 0) break;
        switch (choice) {
        case 1: {
            std::string u, p;
            std::cout << STR_USERNAME_PROMPT; std::getline(std::cin, u);
            std::cout << STR_PASSWORD_PROMPT; std::getline(std::cin, p);
            loggedIn = auth.login(u, p);
            std::cout << (loggedIn ? STR_LOGIN_SUCCESS : STR_LOGIN_FAIL);
            break;
        }
        case 2: {
            if (!loggedIn) { std::cout << STR_LOGIN_FIRST; break; }
            std::cout << STR_ADD_BOOK_MSG;
            Book b = promptBookNoCode();
            std::cout << (lib.addBook(b) ? STR_BOOK_ADDED : STR_BOOK_ADD_FAIL);
            break;
        }
        case 3: {
            const std::vector<Book>& v = lib.getAllBooks();
            if (v.empty()) std::cout << STR_NO_BOOKS;
            for (size_t i = 0; i < v.size(); ++i) printBook(v[i]);
            break;
        }
        case 4: {
            if (!loggedIn) { std::cout << STR_LOGIN_FIRST; break; }
            std::string code;
            std::cout << STR_ENTER_BOOKCODE_UPDATE;
            std::getline(std::cin, code);
            std::cout << STR_ENTER_NEW_DETAILS;
            Book updated = promptBookNoCode();
            std::cout << (lib.updateBook(code, updated) ? STR_UPDATED : STR_NOT_FOUND);
            break;
        }
        case 5: {
            if (!loggedIn) { std::cout << STR_LOGIN_FIRST; break; }
            std::string code;
            std::cout << STR_ENTER_BOOKCODE_DELETE;
            std::getline(std::cin, code);
            std::cout << (lib.deleteBook(code) ? STR_DELETED : STR_NOT_FOUND);
            break;
        }
        case 6: {
            if (!loggedIn) { std::cout << STR_LOGIN_FIRST; break; }
            std::string code, lender, phone;
            std::cout << STR_BOOKCODE_RENT; std::getline(std::cin, code);
            std::cout << STR_LENDER_NAME; std::getline(std::cin, lender);
            std::cout << STR_PHONE_NO; std::getline(std::cin, phone);
            const std::string rentAt = nowDateTime();
            const std::string due = plusDays(14);
            std::cout << (lib.rentBook(code, lender, phone, rentAt, due) ? STR_RENT_RECORDED : STR_RENT_FAIL);
            break;
        }
        case 7: {
            if (!loggedIn) { std::cout << STR_LOGIN_FIRST; break; }
            std::string code;
            std::cout << STR_BOOKCODE_RENEW;
            std::getline(std::cin, code);
            std::string newDate;
            std::cout << STR_NEW_RETURN_DATE;
            std::getline(std::cin, newDate);
            if (newDate.empty()) newDate = plusDays(7);
            std::cout << (lib.renewBook(code, newDate) ? STR_RENEWED : STR_NOT_FOUND);
            break;
        }
        case 8: {
            const std::vector<Book>& allBooks = lib.getAllBooks();
            const std::vector<RentRecord>& allRents = lib.getAllRents();
            std::cout << STR_ALL_BOOKS;
            for (size_t i = 0; i < allBooks.size(); ++i) printBook(allBooks[i]);
            std::cout << STR_RENTED_OUT;
            if (allRents.empty()) std::cout << STR_NONE;
            for (size_t i = 0; i < allRents.size(); ++i) printRent(allRents[i]);
            break;
        }
        case 9: {
            std::string target;
            std::cout << STR_SEARCH_BOOKNAME;
            std::getline(std::cin, target);
            std::vector<Book> books = lib.searchBooksByName(target);
            std::vector<RentRecord> rents = lib.searchRentsByName(target);
            std::cout << STR_BOOKS_FOUND_PREFIX << target << "\": " << books.size() << "\n";
            for (size_t i = 0; i < books.size(); ++i) printBook(books[i]);
            std::cout << STR_RENTS_FOUND_PREFIX << target << "\": " << rents.size() << "\n";
            for (size_t i = 0; i < rents.size(); ++i) printRent(rents[i]);
            int available = lib.availableCountByName(target);
            std::cout << STR_AVAILABLE_QTY_PREFIX << available
                << STR_TOTAL << lib.totalCountByName(target)
                << STR_RENTED << lib.rentedCountByName(target) << ")\n";
            break;
        }
        case 10: {
            if (!loggedIn) { std::cout << STR_LOGIN_FIRST; break; }
            std::string code;
            std::cout << STR_BOOKCODE_RETURN;
            std::getline(std::cin, code);
            std::cout << (lib.returnBook(code) ? STR_RETURN_SUCCESS : STR_RETURN_FAIL);
            break;
        }
        default:
            std::cout << STR_INVALID_CHOICE;
        }
    }
    std::cout << STR_GOODBYE;
    return 0;
}
