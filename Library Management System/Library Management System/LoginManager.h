#pragma once
#include <string>

class LoginManager {
public:
    bool login(const std::string& user, const std::string& pass) const;
};