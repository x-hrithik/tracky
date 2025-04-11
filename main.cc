#define CROW_MAIN
#include "includes.h"
using json = nlohmann::json;


int main() {
    crow::SimpleApp app;


    CROW_ROUTE(app, "/")([] {
        std::ifstream file("home.html");
        std::stringstream buffer;
        buffer << file.rdbuf();
        return crow::response(buffer.str());
        });


    CROW_ROUTE(app, "/search")
        ([](const crow::request& req) {
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

        // Debug output
        std::cout << "Username: " << form["username"] << "\n";
        std::cout << "Password: " << form["password"] << "\n";

        return crow::response(200, "test worked");
        });




    app.port(8080).multithreaded().run();
    return 0;
}