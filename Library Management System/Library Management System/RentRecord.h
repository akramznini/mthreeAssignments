#pragma once
#pragma once
#include <string>
#include "Book.h"

struct RentRecord {
    std::string bookCode;
    std::string bookName;
    std::string bookAuthor;
    BookType type = BookType::Unknown;

    std::string lenderName;
    std::string rentDateTime;  
    std::string returnDate;    
    std::string phone;

    
    std::string toCsv() const;
    static bool fromCsv(const std::string& line, RentRecord& out);
};
