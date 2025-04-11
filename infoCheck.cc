#include "includes.h"
using json = nlohmann::json;

std::ifstream users_file("users.json");
json usersData = json::parse(users_file);

for (const json& item : usersData["users"]) {
    std::string user, pass;

    if (item.contains("username")) {
        user = item["username"];
    }
    else {
        user = "invalid username";
    }

    if (item.contains("password")) {
        pass = item["password"];
    }
    else {
        pass = "Incorrect password";
    }
    if (user == form["username"] && pass == form["password"])
}

