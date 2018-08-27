#include <future>
#include <iostream>
#include "RestHandler.h"

void RestHandler::setup() {
    mux.handle("/hello").get([&](served::response &res, const served::request &req) {
        res << "world";
        std::string s{"Hello world"};
        //std::future<void> result( std::async(RestHandler::scroller.setupText(1, s)));
        std::future<void> result(std::async([&]() { RestHandler::scroller.setupText(1, s); }));
        result.get();
    });
}

void RestHandler::start() {
    served::net::server server("127.0.0.1", "8080", mux);
    server.run(1);
}

RestHandler::RestHandler(Scroller &scroller) : scroller(scroller) {}
