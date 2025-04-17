#define CROW_MAIN
#include "vedas.h"
using json = nlohmann::json;

int main() {
    crow::mustache::set_base("templates");
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
        ([](const crow::request& req) {
        std::string rawCookie = req.get_header_value("Cookie");
        std::unordered_map<std::string, std::string> cookies = parseCookies(rawCookie);

        crow::mustache::context ctx;

        if (cookies.find("username") != cookies.end()) {
            ctx["username"] = cookies["username"];
        }

        return crow::mustache::load("home.html").render(ctx);
            });


    CROW_ROUTE(app, "/static/<string>")
        ([](const std::string& filename) {
        std::ifstream in("static/" + filename, std::ifstream::in);
        if (!in) return crow::response(404);
        std::ostringstream contents;
        contents << in.rdbuf();
        in.close();

        crow::response res(contents.str());
        res.add_header("Content-Type", "text/css");
        return res;
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


    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::Post)
        ([](const crow::request& req) {
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


    CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::Post)
        ([](const crow::request& req) {
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
