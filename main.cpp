#include "Scroller.h"
#include <ctime>
#include <iconv.h>
#include <iomanip>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <string>
#include <unistd.h>

void signalHandler(int s) {
  printf("Caught signal %d\n", s);
  exit(1);
}

std::string convert(const char *input) {
  char dest_str[255];
  char *out = dest_str;

  size_t inbytes = strlen(input);
  size_t outbytes = sizeof dest_str;
  iconv_t conv = iconv_open("CP850//TRANSLIT", "UTF-8");

  if (conv == (iconv_t)-1) {
    perror("iconv_open");
    return "";
  }

  char *i = const_cast<char *>(input);

  if (iconv(conv, &i, &inbytes, &out, &outbytes) == (size_t)-1) {
    perror("iconv");
    return "";
  }

  dest_str[sizeof dest_str - outbytes] = 0;

  return dest_str;
}

std::string getTimeAsString(const tm timeinfo) {
  // Format the time as a string with two digits for each field
  std::stringstream timeString;
  timeString << std::setfill('0') << std::setw(2) << timeinfo.tm_hour << ':'
             << std::setfill('0') << std::setw(2) << timeinfo.tm_min << ':'
             << std::setfill('0') << std::setw(2) << timeinfo.tm_sec;

  return timeString.str();
}

void count_down(tm *timeinfo, long num_seconds) {
  for (int i = 0; i < num_seconds; i++) {
    if (timeinfo->tm_sec > 0) {
      timeinfo->tm_sec--;
    } else {
      if (timeinfo->tm_min > 0) {
        timeinfo->tm_min--;
        timeinfo->tm_sec = 59;
      } else {
        timeinfo->tm_hour--;
        timeinfo->tm_min = 59;
        timeinfo->tm_sec = 59;
      }
    }
  }
}

int main(int argc, char **argv) {
  // setup signal handler
  struct sigaction sigIntHandler;

  sigIntHandler.sa_handler = signalHandler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  Scroller scroller;

  scroller.setupLEDMatrix(CHANNEL);

  tm timeinfo = {0};
  timeinfo.tm_hour = 12;
  timeinfo.tm_min = 0;
  timeinfo.tm_sec = 0;

  while (true) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::string convertedText = getTimeAsString(timeinfo);
    std::vector<int> text;

    for (auto character : convertedText) {
      unsigned char ch = static_cast<unsigned char>(character);
      text.push_back(ch);
    }

    scroller.setupText(1, text);
    //  std::cout << convertedText << std::endl;
    sleep(1);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto total_seconds =
        std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time)
            .count();

    std::cout << total_seconds << std::endl;
    count_down(&timeinfo, total_seconds);
  }
  return 0;
}
