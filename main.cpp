#include <iostream>
#include <cstring>
#include "font.h"

#define CHANNEL 0
#define ROWS 8
#define MATRIXES 4

struct Matrix {
    std::uint8_t rows[ROWS];
    char letter;
};

static unsigned char lookup[16] = {
        0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
        0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };

uint8_t reverse(std::uint8_t n) {
    // Reverse the top and bottom nibble then swap them.
    return (lookup[n&0b1111] << 4) | lookup[n>>4];
}

void setupLEDMatrix(int channel) {
    // if (wiringPiSPISetup(CHANNEL, 1000000) < 0) {
    //     fprintf (stderr, "SPI Setup failed: %s\n", strerror (errno));
    //     exit(errno);
    // }
}

void setupBits(std::string text, Matrix* matrix) {
    for (int i = 0; i < text.length(); i++) {
        const char c = text.at(i);
        const uint8_t* bit = &font[c * 8];

        for (int j = 0; j < ROWS; j++) {
            matrix[i].rows[j] = bit[j];//reverse(bit[j]);
        }
        matrix[i].letter = c;
    }
}

void showbits(std::uint8_t x)
{
    int i;
    for(i=(sizeof(uint8_t)*8)-1; i>=0; i--)
        (x&(1u<<i))?putchar('1'):putchar('0');
}

Matrix scroll(Matrix &matrix, Matrix &prest) {
    Matrix temp;
    for (int i = 0; i < ROWS; i++) {
        std::uint8_t rest = (matrix.rows[i] & 0x80) >> 7;

        matrix.rows[i] <<= 1;
        matrix.rows[i] += prest.rows[i];
        temp.rows[i] = rest;
    }
    return temp;
}

void printAll(Matrix *buffer, int len) {

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < MATRIXES + len; j++) {
            showbits(buffer[j].rows[i]);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}


int main(int argc, char** argv) {
    std::string text = argv[0];

    if (argc > 1) {
        text = argv[1];
    }

    setupLEDMatrix(CHANNEL);

    // create buffer for initial values
    auto bits = new Matrix[text.length()];
    // create display buffer including off screen
    auto buffer = new Matrix[MATRIXES + text.length()];

    // copy bits from font to initial buffer
    setupBits(text, bits);

   // for (int i = 0; i < text.length() * 8; i++) {
   //     showbits(bits[i]);
   // }

    // clean buffer
    for (int i = 0; i < MATRIXES + text.length(); i++) {
        for (int j = 0; j < ROWS; j++) {
            buffer[i].rows[j] = 0;
        }
    }

    // fill off screen buffer
    for (int i = MATRIXES, k = 0; i < text.length() + MATRIXES; i++, k++) {
        for (int j = 0; j < ROWS; j++) {
            buffer[i].rows[j] = bits[k].rows[j];
        }
    }

    printAll(buffer, text.length());


    Matrix rest;
    for (int i = 0; i < ROWS; i++) {
        rest.rows[i] = 0;
    }

    for (int k = 0; k < 30; k++) {
        for (int i = (MATRIXES + text.length() - 1); i >= 0; i--) {
            rest = scroll(buffer[i], rest);
        }
        std::cout << std::endl;
        printAll(buffer, text.length());

    }
    //for (;;) {
      //  scroll(bits);
    //}
    return 0;
}


