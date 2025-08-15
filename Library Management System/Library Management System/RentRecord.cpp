#include "RentRecord.h"
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

std::string RentRecord::toCsv() const {
    auto norm = [](std::string x) {
        std::replace(x.begin(), x.end(), ',', ';');
        return x;
        };
    std::ostringstream os;
    os << norm(bookCode) << "," << norm(bookName) << "," << norm(bookAuthor) << ","
        << Book::toString(type) << "," << norm(lenderName) << ","
        << norm(rentDateTime) << "," << norm(returnDate) << "," << norm(phone);
    return os.str();
}

bool RentRecord::fromCsv(const std::string& line, RentRecord& out) {
    auto p = splitCsv(line);
    if (p.size() != 8) return false;
    out.bookCode = p[0];
    out.bookName = p[1];
    out.bookAuthor = p[2];
    out.type = Book::fromString(p[3]);
    out.lenderName = p[4];
    out.rentDateTime = p[5];
    out.returnDate = p[6];
    out.phone = p[7];
    return !out.bookCode.empty();
}
