#pragma once
#include <string>

enum class BookType {
    Physical,
    Ebook,
    Voice,
    Video,
    Unknown
};

struct Book {
    std::string code;          
    std::string name;          
    std::string author;
    std::string purchaseDate;  // YYYY-MM-DD
    BookType type = BookType::Unknown;

    static BookType fromString(const std::string& t);
    static std::string toString(BookType t);

    std::string toCsv() const;
    static bool fromCsv(const std::string& line, Book& out);
};
