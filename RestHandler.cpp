#include <future>
#include <iostream>
#include "RestHandler.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void RestHandler::setup() {
    mux.handle("/start").post([&](served::response &res, const served::request &req) {
        if (scroller.isRunning()) {
            scroller.setRun(false);
        }

        res << "Scroll started";
        std::cout << "Received message:" << req.body() << std::endl;

        auto receivedMessage = req.body();

        std::thread result([&](std::string message) {
            json parsedMessage = nullptr;

            try {
                parsedMessage = json::parse(message);
            } catch (json::parse_error &e) {
                std::cout << "message: " << e.what() << '\n'
                          << "exception id: " << e.id << '\n'
                          << "byte position of error: " << e.byte << std::endl;
            }
            
            
            if (parsedMessage != nullptr) {
                try {
                    auto str = parsedMessage.at("message").get<std::string>();
                    auto times = 3;

                    if (parsedMessage.find("times") != parsedMessage.end()) {
                        times = parsedMessage.at("times").get<std::int32_t>();
                    }
                    scroller.setupText(times, str);
                } catch (json::out_of_range& e) {
                    std::cout << "message: " << e.what() << '\n'
                              << "exception id: " << e.id << std::endl;
                }
            }
        }, receivedMessage);

        result.detach();
    });

    mux.handle("/stop").post([&](served::response &res, const served::request &req) {
        res << "Scroll stopped";
        scroller.setRun(false);
    });
}

void RestHandler::start() {
    served::net::server server("0.0.0.0", "8080", mux);
    server.run(1);
    std::cout << "Server running on port 8080" << std::endl;
}

RestHandler::RestHandler(Scroller &scroller) : scroller(scroller) {}
