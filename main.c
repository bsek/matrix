#include "font.h"
#include <errno.h>
#include <iconv.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wiringPiSPI.h>

// addr define
#define NO_OP_ADDR 0x0000
#define DIG0_ADDR 0x0100
#define DIG1_ADDR 0x0200
#define DIG2_ADDR 0x0300
#define DIG3_ADDR 0x0400
#define DIG4_ADDR 0x0500
#define DIG5_ADDR 0x0600
#define DIG6_ADDR 0x0700
#define DIG7_ADDR 0x0800

#define DECODE_ADDR 0x09
#define INTENSITY_ADDR 0x0A
#define SCAN_LIMIT_ADDR 0x0B
#define SHUTDOWN_ADDR 0x0C
#define DIST_TEST_ADDR 0x0F

#define INTENSITY 13

// data define
// shutdown reg
#define SHUTDOWN_MODE 0
#define NORMAL_MODE 1

// decode reg
#define NO_DECODE 0
#define DECODE_ALL 1

#define TEST_ON 1
#define TEST_OFF 0

#define SCAN_ALL 7 // scan all 8 digits

const static int CHANNEL = 0;
const static int ROWS = 8;
const static int MATRICES = 9;

struct Matrix {
  uint8_t rows[8];
  char letter;
};

static unsigned char lookup[16] = {0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
                                   0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf};

uint8_t reverse(uint8_t n) {
  // Reverse the top and bottom nibble then swap them.
  return (lookup[n & 0b1111] << 4) | lookup[n >> 4];
}

void showBits(uint8_t x) {
  for (int i = (sizeof(uint8_t) * 8) - 1; i >= 0; i--) {
    (x & (1u << i)) ? putchar('1') : putchar('0');
  }
}

void printAll(struct Matrix *buffer, int len) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < MATRICES; j++) {
      showBits(buffer[j].rows[i]);
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void setSPIValue(int reg, int val) {
  uint8_t buf[2];
  buf[0] = reg;
  buf[1] = val;
  wiringPiSPIDataRW(CHANNEL, buf, 2);
}

void setupLEDMatrix(int channel) {
  int fd;

  fd = wiringPiSPISetup(channel, 1000000);
  if (fd < 0) {
    fprintf(stderr, "SPI Setup failed: %s\n", errno);
    exit(fd);
  }

  for (int i = 0; i < MATRICES; i++) {
    setSPIValue(DECODE_ADDR, NO_DECODE);
    setSPIValue(SCAN_LIMIT_ADDR, SCAN_ALL);
    setSPIValue(INTENSITY_ADDR, INTENSITY);
    setSPIValue(SHUTDOWN_ADDR, NORMAL_MODE);
    setSPIValue(DIST_TEST_ADDR, TEST_OFF);
  }
}

void setupBits(const char *text, struct Matrix *matrix, int len) {
  for (int i = 0; i < len; i++) {
    const uint8_t *bit = &font[text[i] * 8];

    for (int j = 0; j < ROWS; j++) {
      matrix[i].rows[j] = bit[j];
    }
  }
}

void display(struct Matrix *matrix, int len) {
  uint8_t buf[MATRICES * 2];
  for (int row = 0; row < ROWS; row++) {
    int selectedLetter = 0;
    for (int k = 0, j = 0; k < MATRICES; k++) {
      buf[j++] = row + 1;
      buf[j++] = reverse(matrix[selectedLetter++].rows[row]);
    }
    wiringPiSPIDataRW(CHANNEL, buf, MATRICES * 2);
  }
  // printAll(matrix, len);
}

char *getTimeAsString(const struct tm *timeinfo) {
  char timeString[9];
  snprintf(timeString, sizeof(timeString), " %02d:%02d:%02d", timeinfo->tm_hour,
           timeinfo->tm_min, timeinfo->tm_sec);

  return strdup(timeString);
}

void count_down(struct tm *timeinfo, long num_seconds) {
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

void signalHandler(int s) {
  printf("Caught signal %d\n", s);
  exit(1);
}

int main(int argc, char **argv) {
  // setup signal handler
  struct sigaction sigIntHandler;

  sigIntHandler.sa_handler = signalHandler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);

  setupLEDMatrix(0);

  struct tm timeinfo = {0};
  timeinfo.tm_hour = 12;
  timeinfo.tm_min = 0;
  timeinfo.tm_sec = 0;

  // create buffer for initial values
  struct Matrix bits[MATRICES];

  while (1) {
    time_t start_time = time(NULL);

    char *text = getTimeAsString(&timeinfo);
    int len = strlen(text);

    // copy bits from font to initial buffer
    setupBits(text, bits, len);

    display(bits, len);

    sleep(1);

    time_t end_time = time(NULL);
    long total_seconds = end_time - start_time;

    printf("%ld\n", total_seconds);
    count_down(&timeinfo, total_seconds);
  }
  return 0;
}
