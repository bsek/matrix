#include <future>
#include <iostream>
#include "RestHandler.h"
#include <nlohmann/json.hpp>

void RestHandler::setup() {
    mux.handle("/start").post([&](served::response &res, const served::request &req) {
        res << "Scroll started";
        std::thread result([&]() {
            auto message = nlohmann::json::parse(req.body());
            auto str = message.at("message").get<std::string>();
            scroller.setupText(3, str);
        });
        result.detach();
    });

    mux.handle("/stop").post([&](served::response &res, const served::request &req) {
        res << "Scroll stopped";
        scroller.setRun(false);
    });
}

void RestHandler::start() {
    served::net::server server("127.0.0.1", "8080", mux);
    server.run(1);
}

RestHandler::RestHandler(Scroller &scroller) : scroller(scroller) {}
