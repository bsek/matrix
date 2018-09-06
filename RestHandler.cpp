#include <future>
#include <iostream>
#include "RestHandler.h"
#include <nlohmann/json.hpp>

void RestHandler::setup() {
    mux.handle("/start").post([&](served::response &res, const served::request &req) {
        res << "Scroll started";
	std::cout << "Received message:" << req.body() << std::endl;

	auto receivedMessage = req.body();

        std::thread result([&](std::string message) {
		try {
			json::parse("[1,2,3,]");
		} catch (json::parse_error& e) {
			std::cout << "message: " << e.what() << '\n'
			<< "exception id: " << e.id << '\n'
			<< "byte position of error: " << e.byte << std::endl;
		}

            auto parsedMessage = nlohmann::json::parse(message);
            auto str = parsedMessage.at("message").get<std::string>();
            scroller.setupText(3, str);
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
