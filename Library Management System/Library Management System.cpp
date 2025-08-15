#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>
#include <limits>
#include "Library.h"
#include "LoginManager.h"

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
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
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
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
    return std::string(buf);
}

static BookType askBookType() {
    std::cout << "Book type (1=physical, 2=ebook, 3=voice, 4=video): ";
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
    std::cout << "Book name: "; std::getline(std::cin, b.name);
    std::cout << "Author: "; std::getline(std::cin, b.author);
    std::cout << "Purchase date (YYYY-MM-DD): "; std::getline(std::cin, b.purchaseDate);
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
    std::cout << "\nLibrary Management System\n"
        << "1. Login validation\n"
        << "2. Add book\n"
        << "3. List all books\n"
        << "4. Update book\n"
        << "5. Delete book\n"
        << "6. Rent/issue a book\n"
        << "7. Renew a book\n"
        << "8. Display available & rented details\n"
        << "9. Search by BookName\n"
        << "10. Return a book\n"
        << "0. Exit\n"
        << "Choice: ";
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
            std::cout << "Username: "; std::getline(std::cin, u);
            std::cout << "Password: "; std::getline(std::cin, p);
            loggedIn = auth.login(u, p);
            std::cout << (loggedIn ? "Login successful.\n" : "Invalid credentials.\n");
            break;
        }
        case 2: {
            if (!loggedIn) { std::cout << "Please login first.\n"; break; }
            std::cout << "Adding a book.\n";
            Book b = promptBookNoCode();
            if (lib.addBook(b)) std::cout << "Book added.\n";
            else std::cout << "Failed to add book.\n";
            break;
        }
        case 3: {
            const std::vector<Book>& v = lib.getAllBooks();
            if (v.empty()) std::cout << "No books.\n";
            for (size_t i = 0; i < v.size(); ++i) printBook(v[i]);
            break;
        }
        case 4: {
            if (!loggedIn) { std::cout << "Please login first.\n"; break; }
            std::string code;
            std::cout << "Enter BookCode to update: ";
            std::getline(std::cin, code);

            std::cout << "Enter new details (BookCode will remain the same):\n";
            Book updated = promptBookNoCode();
            std::cout << (lib.updateBook(code, updated) ? "Updated.\n" : "Not found.\n");
            break;
        }
        case 5: {
            if (!loggedIn) { std::cout << "Please login first.\n"; break; }
            std::string code;
            std::cout << "Enter BookCode to delete: ";
            std::getline(std::cin, code);
            std::cout << (lib.deleteBook(code) ? "Deleted.\n" : "Not found.\n");
            break;
        }
        case 6: {
            if (!loggedIn) { std::cout << "Please login first.\n"; break; }
            std::string code, lender, phone;
            std::cout << "BookCode to rent: "; std::getline(std::cin, code);
            std::cout << "Lender name: "; std::getline(std::cin, lender);
            std::cout << "Phone no: "; std::getline(std::cin, phone);

            const std::string rentAt = nowDateTime();
            const std::string due = plusDays(14); // default 2 weeks

            if (lib.rentBook(code, lender, phone, rentAt, due))
                std::cout << "Rent recorded.\n";
            else
                std::cout << "Failed (book code not found or no copies available).\n";
            break;  
        }
        case 7: {
            if (!loggedIn) { std::cout << "Please login first.\n"; break; }
            std::string code;
            std::cout << "BookCode to renew: ";
            std::getline(std::cin, code);
            std::string newDate;
            std::cout << "New return date (YYYY-MM-DD), leave empty to +7 days: ";
            std::getline(std::cin, newDate);
            if (newDate.empty()) newDate = plusDays(7);
            std::cout << (lib.renewBook(code, newDate) ? "Renewed.\n" : "Not found.\n");
            break;
        }
        case 8: {
            const std::vector<Book>& allBooks = lib.getAllBooks();
            const std::vector<RentRecord>& allRents = lib.getAllRents();
            std::cout << "\n--- All Books ---\n";
            for (size_t i = 0; i < allBooks.size(); ++i) printBook(allBooks[i]);

            std::cout << "\n--- Rented Out ---\n";
            if (allRents.empty()) std::cout << "None.\n";
            for (size_t i = 0; i < allRents.size(); ++i) printRent(allRents[i]);
            break;
        }
        case 9: {
            std::string target;
            std::cout << "Enter BookName to search: ";
            std::getline(std::cin, target);

            std::vector<Book> books = lib.searchBooksByName(target);
            std::vector<RentRecord> rents = lib.searchRentsByName(target);
            std::cout << "\nBooks found for \"" << target << "\": " << books.size() << "\n";
            for (size_t i = 0; i < books.size(); ++i) printBook(books[i]);

            std::cout << "\nRents found for \"" << target << "\": " << rents.size() << "\n";
            for (size_t i = 0; i < rents.size(); ++i) printRent(rents[i]);

            int available = lib.availableCountByName(target);
            std::cout << "\nAvailable qty: " << available << "  (total "
                << lib.totalCountByName(target) << " - rented "
                << lib.rentedCountByName(target) << ")\n";
            break;
        }
        case 10: { 
            if (!loggedIn) { std::cout << "Please login first.\n"; break; }
            std::string code;
            std::cout << "BookCode to return: ";
            std::getline(std::cin, code);
            if (lib.returnBook(code))
                std::cout << "Book returned successfully.\n";
            else
                std::cout << "No active rental found for that BookCode.\n";
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
