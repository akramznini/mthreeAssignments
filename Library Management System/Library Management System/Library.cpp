#include "Library.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdio> 
#include <cctype>
#include <sstream>
#include <iomanip>

Library::Library(const std::string& booksFile, const std::string& rentsFile)
    : booksPath(booksFile), rentsPath(rentsFile) {}

void Library::loadBooks() {
    if (booksLoaded) return;
    booksLoaded = true;
    booksCache.clear();

    std::ifstream in(booksPath.c_str());
    if (!in) return; 

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        Book b;
        if (Book::fromCsv(line, b)) booksCache.push_back(b);
    }
}

void Library::loadRents() {
    if (rentsLoaded) return;
    rentsLoaded = true;
    rentsCache.clear();

    std::ifstream in(rentsPath.c_str());
    if (!in) return;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        RentRecord r;
        if (RentRecord::fromCsv(line, r)) rentsCache.push_back(r);
    }
}

bool Library::saveBooks() const {
    std::ofstream out(booksPath.c_str(), std::ios::trunc);
    if (!out) return false;
    for (size_t i = 0; i < booksCache.size(); ++i) {
        out << booksCache[i].toCsv() << "\n";
    }
    return true;
}

bool Library::saveRents() const {
    std::ofstream out(rentsPath.c_str(), std::ios::trunc);
    if (!out) return false;
    for (size_t i = 0; i < rentsCache.size(); ++i) {
        out << rentsCache[i].toCsv() << "\n";
    }
    return true;
}

std::string Library::nextBookCode() const {
    int maxNum = 0;

    for (size_t i = 0; i < booksCache.size(); ++i) {
        const std::string& c = booksCache[i].code;

        
        if (c.size() == 9 && c.compare(0, 3, "BK-") == 0) {
            const std::string numPart = c.substr(3, 6);

            
            const bool allDigits =
                !numPart.empty() &&
                std::find_if(numPart.begin(), numPart.end(),
                    [](unsigned char ch) { return !std::isdigit(ch); }) == numPart.end();

            if (allDigits) {
                
                int n = 0;
                for (size_t j = 0; j < numPart.size(); ++j) {
                    n = n * 10 + (numPart[j] - '0');
                }
                if (n > maxNum) maxNum = n;
            }
        }
    }

    const int next = maxNum + 1;

    
    std::ostringstream oss;
    oss << "BK-" << std::setw(6) << std::setfill('0') << next;
    return oss.str();
}

bool Library::addBook(Book b) {
    loadBooks();

    b.code = nextBookCode();

 
    booksCache.push_back(b);
    return saveBooks();
}

size_t Library::findBookIndexByCode(const std::string& code, bool& found) {
    loadBooks();
    for (size_t i = 0; i < booksCache.size(); ++i) {
        if (booksCache[i].code == code) {
            found = true;
            return i;
        }
    }
    found = false;
    return 0;
}

bool Library::updateBook(const std::string& code, const Book& updated) {
    bool found = false;
    size_t idx = findBookIndexByCode(code, found);
    if (!found) return false;

   
    Book copy = updated;
    copy.code = booksCache[idx].code;
    booksCache[idx] = copy;

    return saveBooks();
}

bool Library::deleteBook(const std::string& code) {
    bool found = false;
    size_t idx = findBookIndexByCode(code, found);
    if (!found) return false;
    booksCache.erase(booksCache.begin() + static_cast<long>(idx));
    return saveBooks();
}

const std::vector<Book>& Library::getAllBooks() {
    loadBooks();
    return booksCache;
}

const std::vector<RentRecord>& Library::getAllRents() {
    loadRents();
    return rentsCache;
}

std::vector<Book> Library::searchBooksByName(const std::string& bookName) {
    loadBooks();
    std::vector<Book> res;
    for (size_t i = 0; i < booksCache.size(); ++i) {
        if (booksCache[i].name == bookName) res.push_back(booksCache[i]);
    }
    return res;
}

std::vector<RentRecord> Library::searchRentsByName(const std::string& bookName) {
    loadRents();
    std::vector<RentRecord> res;
    for (size_t i = 0; i < rentsCache.size(); ++i) {
        if (rentsCache[i].bookName == bookName) res.push_back(rentsCache[i]);
    }
    return res;
}

bool Library::rentBook(const std::string& bookCode,
    const std::string& lenderName,
    const std::string& phone,
    const std::string& rentDateTime,
    const std::string& returnDate) {
    loadBooks();
    loadRents();

    bool found = false;
    size_t idx = findBookIndexByCode(bookCode, found);
    if (!found) return false; 

    const Book& b = booksCache[idx];

    
    int total = totalCountByName(b.name);
    int rented = rentedCountByName(b.name);
    if (rented >= total) return false;

    RentRecord rec;
    rec.bookCode = b.code;
    rec.bookName = b.name;
    rec.bookAuthor = b.author;
    rec.type = b.type;
    rec.lenderName = lenderName;
    rec.rentDateTime = rentDateTime;
    rec.returnDate = returnDate;
    rec.phone = phone;

    rentsCache.push_back(rec);
    return saveRents();
}

bool Library::returnBook(const std::string& bookCode) {
    loadRents();
    for (size_t i = 0; i < rentsCache.size(); ++i) {
        if (rentsCache[i].bookCode == bookCode) {
            rentsCache.erase(rentsCache.begin() + static_cast<long>(i));
            return saveRents();
        }
    }
    return false; 
}


bool Library::renewBook(const std::string& bookCode, const std::string& newReturnDate) {
    loadRents();
    for (size_t i = 0; i < rentsCache.size(); ++i) {
        if (rentsCache[i].bookCode == bookCode) {
            rentsCache[i].returnDate = newReturnDate;
            return saveRents();
        }
    }
    return false;
}

int Library::totalCountByName(const std::string& bookName) {
    loadBooks();
    int count = 0;
    for (size_t i = 0; i < booksCache.size(); ++i)
        if (booksCache[i].name == bookName) ++count;
    return count;
}

int Library::rentedCountByName(const std::string& bookName) {
    loadRents();
    int count = 0;
    for (size_t i = 0; i < rentsCache.size(); ++i)
        if (rentsCache[i].bookName == bookName) ++count;
    return count;
}

int Library::availableCountByName(const std::string& bookName) {
    return totalCountByName(bookName) - rentedCountByName(bookName);
}
