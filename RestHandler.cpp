#include <future>
#include <iostream>
#include <iconv.h>
#include <type_traits>
#include "RestHandler.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

char * convertUtf8toAscii(std::string &input) {
    size_t inbytes = input.length();
    char *dest_str = new char[inbytes];
    char *input_str = new char[inbytes];
    strcpy(input_str, input.c_str());

    char *dest = dest_str;

    size_t outbytes = sizeof dest_str;
    iconv_t conv = iconv_open("ISO8859-1", "UTF-8");

    if (conv == (iconv_t)-1) {
        perror("iconv_open");
        return nullptr;
    }

    if (iconv(conv, &input_str, &inbytes, &dest, &outbytes) == (size_t)-1) {
        perror("iconv");
        return nullptr;
    }

    dest_str[sizeof dest_str - outbytes] = 0;
    puts(dest_str);

    return dest_str;
}

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
                    std::string str = parsedMessage.at("message").get<std::string>();
                    auto times = 3;

                    if (parsedMessage.find("times") != parsedMessage.end()) {
                        times = parsedMessage.at("times").get<std::int32_t>();
                    }
                    char * text = convertUtf8toAscii(str);
                    //char * text = new char[str.length()];
                    //strcpy(text, str.c_str());
                    std::string inputStr(text);
                    scroller.setupText(times, inputStr);
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
