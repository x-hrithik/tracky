#include "includes.h"
using json = nlohmann::json;

bool infoCheck(const std::string & username, const std::string & password) {
    std::ifstream users_file("users.json");
    if (!users_file) return false;

    json usersData = json::parse(users_file);

    for (const json& item : usersData["users"]) {
        if (item.contains("username") && item.contains("password")) {
            std::string storedUser = item["username"];
            std::string storedPass = item["password"];

            if (storedUser == username && storedPass == password) {
                return true;
            }
        }
    }

    return false;
}

