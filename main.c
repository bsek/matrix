#include "font.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#define DECODE_ADDR 0x0900
#define INTENSITY_ADDR 0x0A00
#define SCAN_LIMIT_ADDR 0x0B00
#define SHUTDOWN_ADDR 0x0C00
#define DIST_TEST_ADDR 0x0F00

#define INTENSITY_MODE 0xFF

// data define
// shutdown reg
#define SHUTDOWN_MODE 0x0000
#define NORMAL_MODE 0x0001

// decode reg
#define NO_DECODE 0x0000  // all digit will not be decode
#define DECODE_ALL 0x00FF // decode all digit as BCD

const static int CHANNEL = 0;
const static int ROWS = 8;
const static int MATRIXES = 9;

struct Matrix {
  uint8_t rows[8];
  char letter;
};

void showBits(uint8_t x) {
  for (int i = (sizeof(uint8_t) * 8) - 1; i >= 0; i--) {
    (x & (1u << i)) ? putchar('1') : putchar('0');
  }
}

void printAll(struct Matrix *buffer, int len) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < MATRIXES; j++) {
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

  setSPIValue(DECODE_ADDR, DECODE_ALL);
  setSPIValue(SCAN_LIMIT_ADDR, DIG6_ADDR);
  setSPIValue(INTENSITY_ADDR, INTENSITY_MODE);
  setSPIValue(SHUTDOWN_ADDR, NORMAL_MODE);
}

void setupBits(const char *text, struct Matrix *matrix) {
  for (int i = 0; i < strlen(text); i++) {
    const uint8_t *bit = &font[text[i] * 8];

    for (int j = 0; j < ROWS; j++) {
      matrix[i].rows[j] = bit[j];
    }
  }
}

void display(struct Matrix *matrix, int len) {
  uint8_t buf[MATRIXES * 2];
  for (int row = 0; row < ROWS; row++) {
    int selectedLetter = 0;
    for (int k = 0, j = 0; k < MATRIXES; k++) {
      buf[j++] = row + 1;
      buf[j++] = matrix[selectedLetter++].rows[row];
    }
    wiringPiSPIDataRW(CHANNEL, buf, MATRIXES * 2);
  }
  printAll(matrix, len);
}

int main(int argc, char **argv) {
  setupLEDMatrix(0);

  const char *text = "Hello world";

  uint32_t size = strlen(text);

  // create buffer for initial values
  struct Matrix bits[size];
  // create display buffer including off screen
  struct Matrix buffer[MATRIXES];

  // copy bits from font to initial buffer
  setupBits(text, bits);

  // clean buffer
  for (int i = 0; i < MATRIXES; i++) {
    for (int j = 0; j < ROWS; j++) {
      buffer[i].rows[j] = 0;
    }
  }

  // fill off screen buffer
  for (int i = 0, k = 0; i < MATRIXES + size; i++, k++) {
    for (int j = 0; j < ROWS; j++) {
      buffer[i].rows[j] = bits[k].rows[j];
    }
  }

  display(buffer, size);

  sleep(2);
  return 0;
}
