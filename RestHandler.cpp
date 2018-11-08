#include <future>
#include <iostream>
#include <type_traits>
#include <vector>
#include <codecvt>
#include <stdlib.h>

#include "RestHandler.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::wstring utf8_to_wstring(const std::string &str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.from_bytes(str);
}

#include <iconv.h>

std::string convert(const char * input) {
    char dest_str[255];
    char *out = dest_str;

    size_t inbytes = strlen(input);
    size_t outbytes = sizeof dest_str;
    iconv_t conv = iconv_open("CP850//TRANSLIT", "UTF-8");

    if (conv == (iconv_t)-1) {
        perror("iconv_open");
        return "";
    }

    char * i = const_cast<char *>(input);

    if (iconv(conv, &i, &inbytes, &out, &outbytes) == (size_t)-1) {
        perror("iconv");
        return "";
    }

    dest_str[sizeof dest_str - outbytes] = 0;

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
                    auto convertedText = convert(str.c_str());

                    std::vector<int> text;

                    for (auto character : convertedText) {
                        unsigned char ch = static_cast<unsigned char>(character);
                        if (ch <= 254) {
                            text.push_back(ch);
                        }
                    }

                    auto times = 3;

                    if (parsedMessage.find("times") != parsedMessage.end()) {
                        times = parsedMessage.at("times").get<std::int32_t>();
                    }

                    scroller.setupText(times, text);
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
