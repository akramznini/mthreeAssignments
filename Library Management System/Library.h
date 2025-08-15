#pragma once
#include <vector>
#include <string>
#include "Book.h"
#include "RentRecord.h"


class Library {
public:
    explicit Library(const std::string& booksFile = "Books.txt",
        const std::string& rentsFile = "rents.txt");

    bool addBook(Book b);
    bool updateBook(const std::string& code, const Book& updated);
    bool deleteBook(const std::string& code);

    
    const std::vector<Book>& getAllBooks();
    const std::vector<RentRecord>& getAllRents();

    std::vector<Book> searchBooksByName(const std::string& bookName);
    std::vector<RentRecord> searchRentsByName(const std::string& bookName);

   
    bool rentBook(const std::string& bookCode,
        const std::string& lenderName,
        const std::string& phone,
        const std::string& rentDateTime,
        const std::string& returnDate);
    bool renewBook(const std::string& bookCode, const std::string& newReturnDate);

    bool returnBook(const std::string& bookCode);
   
    int totalCountByName(const std::string& bookName);
    int rentedCountByName(const std::string& bookName);
    int availableCountByName(const std::string& bookName);

private:
    std::string booksPath;
    std::string rentsPath;

    std::vector<Book> booksCache;
    std::vector<RentRecord> rentsCache;
    bool booksLoaded = false;
    bool rentsLoaded = false;

    
    void loadBooks();
    void loadRents();
    bool saveBooks() const;
    bool saveRents() const;

    
    size_t findBookIndexByCode(const std::string& code, bool& found);

    std::string nextBookCode() const; 
};
