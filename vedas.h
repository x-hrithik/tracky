#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <sys/stat.h>
#include <unordered_set>
#include <iomanip>
#include <functional>
#include <cstddef>
#include <string_view>
#include <ranges>


#define CROW_DISABLE_JSON
#include <crow.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

//search api format
std::string fetchAndFormatMediaResults(const std::string& query);

//map for user names and passwords
std::unordered_map<std::string, std::string> parseFormData(const std::string& body);

//map for splitting cookie string
std::unordered_map<std::string, std::string> parseCookies(const std::string& cookieHeader);

//checks for user and pass
bool infoCheckLogin(const std::string& username, const std::string& password);

//sign up functions, username checker and register user
bool infoCheckSignUp(const std::string& username);
bool registerUser(const std::string& username, const std::string& password);