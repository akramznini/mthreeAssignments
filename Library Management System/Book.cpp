#include "Book.h"
#include <sstream>
#include <vector>
#include <algorithm>

static std::vector<std::string> splitCsv(const std::string& s) {
    std::vector<std::string> out;
    std::string cur;
    std::stringstream ss(s);
    while (std::getline(ss, cur, ',')) out.push_back(cur);
    return out;
}

BookType Book::fromString(const std::string& t) {
    std::string s = t;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (s == "physical") return BookType::Physical;
    if (s == "ebook")    return BookType::Ebook;
    if (s == "voice")    return BookType::Voice;
    if (s == "video")    return BookType::Video;
    return BookType::Unknown;
}

std::string Book::toString(BookType t) {
    switch (t) {
    case BookType::Physical: return "physical";
    case BookType::Ebook:    return "ebook";
    case BookType::Voice:    return "voice";
    case BookType::Video:    return "video";
    default: return "unknown";
    }
}

std::string Book::toCsv() const {

    auto norm = [](std::string x) {
        std::replace(x.begin(), x.end(), ',', ';');
        return x;
        };
    std::ostringstream os;
    os << norm(code) << "," << norm(name) << "," << norm(author) << ","
        << norm(purchaseDate) << "," << Book::toString(type);
    return os.str();
}

bool Book::fromCsv(const std::string& line, Book& out) {
    auto parts = splitCsv(line);
    if (parts.size() != 5) return false;
    out.code = parts[0];
    out.name = parts[1];
    out.author = parts[2];
    out.purchaseDate = parts[3];
    out.type = Book::fromString(parts[4]);
    return !out.code.empty();
}
