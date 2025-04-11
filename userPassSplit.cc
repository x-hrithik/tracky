#include "includes.h"

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
