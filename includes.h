#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>

#define CROW_DISABLE_JSON
#include <crow.h>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

std::string fetchAndFormatMediaResults(const std::string& query);

std::unordered_map<std::string, std::string> parseFormData(const std::string& body);
