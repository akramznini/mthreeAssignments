#include "LoginManager.h"


bool LoginManager::login(const std::string& user, const std::string& pass) const {
    return (user == "admin" && pass == "password123");
}
