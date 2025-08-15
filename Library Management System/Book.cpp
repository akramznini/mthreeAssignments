#include "Book.h"
#include <sstream>
#include <vector>
#include <algorithm>

const std::string STR_PHYSICAL = "physical";
const std::string STR_EBOOK = "ebook";
const std::string STR_VOICE = "voice";
const std::string STR_VIDEO = "video";
const std::string STR_UNKNOWN = "unknown";
constexpr size_t CSV_PARTS_COUNT = 5;

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
    if (s == STR_PHYSICAL) return BookType::Physical;
    if (s == STR_EBOOK)    return BookType::Ebook;
    if (s == STR_VOICE)    return BookType::Voice;
    if (s == STR_VIDEO)    return BookType::Video;
    return BookType::Unknown;
}

std::string Book::toString(BookType t) {
    switch (t) {
    case BookType::Physical: return STR_PHYSICAL;
    case BookType::Ebook:    return STR_EBOOK;
    case BookType::Voice:    return STR_VOICE;
    case BookType::Video:    return STR_VIDEO;
    default: return STR_UNKNOWN;
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
    if (parts.size() != CSV_PARTS_COUNT) return false;
    out.code = parts[0];
    out.name = parts[1];
    out.author = parts[2];
    out.purchaseDate = parts[3];
    out.type = Book::fromString(parts[4]);
    return !out.code.empty();
}
