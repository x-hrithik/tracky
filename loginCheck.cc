#include "sight.h"
using json = nlohmann::json;

//map to store and split user name pass from html req, could also use streamview for this btw
std::unordered_map<std::string, std::string> parseFormData(const std::string& body) {
    std::unordered_map<std::string, std::string> userPass;
    std::stringstream ss(body);
    std::string pair;

    while (std::getline(ss, pair, '&')) {
        std::stringstream pairStream(pair);
        std::string user, pass;
        std::getline(pairStream, user, '=');
        std::getline(pairStream, pass);

        userPass[user] = pass;
    }

    return userPass;
}

//checks if login info is correct
bool infoCheckLogin(const std::string & username, const std::string & password) {
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

