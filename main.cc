#define CROW_MAIN
#include "sight.h"
using json = nlohmann::json;

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](const crow::request& req) {
        std::ifstream file("home.html");
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string html = buffer.str();

        std::string rawCookie = req.get_header_value("Cookie");
        auto cookies = parseCookies(rawCookie);

        if (cookies.find("username") != cookies.end()) {
            std::string name = cookies["username"];
            size_t pos = html.find("{{username}}");
            if (pos != std::string::npos) {
                html.replace(pos, std::string("{{username}}").length(), "Welcome back, " + name + "!");
            }
        }
        else {
            html.replace(html.find("{{username}}"), std::string("{{username}}").length(), "");
        }

        return crow::response(html);
        });

    CROW_ROUTE(app, "/search")([](const crow::request& req) {
        const char* q = req.url_params.get("q");

        if (!q) {
            return crow::response(400, "Missing query");
        }

        std::string query = q;
        std::string html = fetchAndFormatMediaResults(query);

        return crow::response(html);
        });

    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::Post)([](const crow::request& req) {
        std::unordered_map<std::string, std::string> form = parseFormData(req.body);

        if (infoCheckLogin(form["username"], form["password"])) {
            crow::response res("login works");
            res.add_header("Set-Cookie", "username=" + form["username"]);
            return res;
        }
        else {
            return crow::response(401, "Incorrect USER and PASS. (test worked)");
        }
        });

    CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::Post)([](const crow::request& req) {
        std::unordered_map<std::string, std::string> form = parseFormData(req.body);

        std::string username = form["username"];
        std::string password = form["password"];

        if (infoCheckSignUp(username)) {
            return crow::response(409, "username already taken");
        }

        if (registerUser(username, password)) {
            crow::response res("welcome to tracky (account created)");
            res.add_header("Set-Cookie", "username=" + username);
            return res;
        }
    return crow::response(500, "failed to register user");
    });

    app.port(8080).multithreaded().run();
    return 0;
}
