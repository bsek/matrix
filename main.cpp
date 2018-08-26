#include <iostream>
#include <cstring>
#include <unistd.h>
#include "font.h"

#include <wiringPiSPI.h>

#define CHANNEL 0
#define ROWS 8
#define MATRIXES 6

void showbits(uint8_t val);

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

void display(Matrix *matrix, int len) {
	uint8_t buf[MATRIXES * 2]; 
	for (int row = 0; row < ROWS; row++) {
		int selectedLetter = 0;
		for (int k = 0, j = 0; k < MATRIXES; k++ ) {
			buf[j++] = row+1;
			buf[j++] = reverse(matrix[selectedLetter++].rows[row]);
		}
		wiringPiSPIDataRW(CHANNEL, buf, MATRIXES * 2);
	}
}

void spi(uint8_t reg, uint8_t val) {
	uint8_t buf[2];
	buf[0] = reg;
	buf[1] = val;
	wiringPiSPIDataRW(CHANNEL, buf, 2); 
}

void setupLEDMatrix(int channel) {
    if (wiringPiSPISetup(channel, 1000000) < 0) {
        fprintf (stderr, "SPI Setup failed: %s\n", strerror (errno));
        exit(errno);
    }
    spi(0x09,0x00);
    spi(0x0B,0x07);
    spi(0x0A,0xFF);
    spi(0x0C,0x01);
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

    Matrix rest;
    for (int i = 0; i < ROWS; i++) {
        rest.rows[i] = 0;
    }

    while(true) {
        for (int i = (MATRIXES + text.length() - 1); i >= 0; i--) {
            rest = scroll(buffer[i], rest);
        }
	usleep(50000);
    	display(buffer, text.length());
    }

    return 0;
}


