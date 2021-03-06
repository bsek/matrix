#include "Scroller.h"
#include <memory>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <utility>
#include <wiringPiSPI.h>
#include "font.h"

static unsigned char lookup[16] = {
        0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
        0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf };

uint8_t Scroller::reverse(std::uint8_t n) {
    // Reverse the top and bottom nibble then swap them.
    return (lookup[n & 0b1111] << 4) | lookup[n >> 4];
}

void Scroller::showBits(std::uint8_t x) {
    for (int i = (sizeof(uint8_t) * 8) - 1; i >= 0; i--) {
        (x & (1u << i)) ? putchar('1') : putchar('0');
    }
}

void Scroller::printAll(Matrix *buffer, int len) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < MATRIXES + len; j++) {
            showBits(buffer[j].rows[i]);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Scroller::display(Matrix *matrix, int len) {
    uint8_t buf[MATRIXES * 2];
    for (int row = 0; row < ROWS; row++) {
        int selectedLetter = 0;
        for (int k = 0, j = 0; k < MATRIXES; k++ ) {
            buf[j++] = row+1;
            buf[j++] = reverse(matrix[selectedLetter++].rows[row]);
        }
        wiringPiSPIDataRW(CHANNEL, buf, MATRIXES * 2);
    }
    printAll(matrix, len);
}

void Scroller::setSPIValue(uint8_t reg, uint8_t val) {
	uint8_t buf[2];
	buf[0] = reg;
	buf[1] = val;
	wiringPiSPIDataRW(CHANNEL, buf, 2);
}

void Scroller::setupLEDMatrix(int channel) {
    uint8_t buf[2];

    if (wiringPiSPISetup(channel, 1000000) < 0) {
        fprintf (stderr, "SPI Setup failed: %s\n", strerror (errno));
        exit(errno);
    }

    setSPIValue(0x09,0x00);
    setSPIValue(0x0B,0x07);
    setSPIValue(0x0A,0xFF);
    setSPIValue(0x0C,0x01);
}

void Scroller::setupBits(std::vector<int> text, Matrix* matrix) {
    for (int i = 0; i < text.size(); i++) {
        const uint8_t* bit = &font[text[i] * 8];

        for (int j = 0; j < ROWS; j++) {
            matrix[i].rows[j] = bit[j];
        }
    }
}

Matrix Scroller::scroll(Matrix &matrix, Matrix &prest) {
    Matrix temp;
    for (int i = 0; i < ROWS; i++) {
        std::uint8_t rest = (matrix.rows[i] & 0x80) >> 7;

        matrix.rows[i] <<= 1;
        matrix.rows[i] += prest.rows[i];
        temp.rows[i] = rest;
    }
    return temp;
}

void Scroller::doScroll(int times, Matrix *buffer, const std::vector<int> &text) {
    uint32_t size = text.size();
    Matrix rest;
    for (int i = 0; i < ROWS; i++) {
        rest.rows[i] = 0;
    }

    long loops = 0;
    long totalLoopsNeeded = ((size + MATRIXES) * 8) * times;

    while(run) {
        loops++;

        for (int i = (MATRIXES + size - 1); i >= 0; i--) {
            rest = scroll(buffer[i], rest);
        }
        usleep(50000);
        display(buffer, size);

        if (loops > totalLoopsNeeded) {
            run = false;
        }
    }
}

void Scroller::setRun(bool run) {
    std::lock_guard<std::mutex> lock(run_mutex);
    Scroller::run = run;
}

void Scroller::setupText(int times, const std::vector<int> &text) {
    uint32_t size = text.size();
    // create buffer for initial values
    auto bits = std::make_unique<Matrix[]>(size);
    // create display buffer including off screen
    auto buffer = std::make_unique<Matrix[]>(MATRIXES + size);

    // copy bits from font to initial buffer
    setupBits(text, bits.get());

    // clean buffer
    for (int i = 0; i < MATRIXES + size; i++) {
        for (int j = 0; j < ROWS; j++) {
            buffer[i].rows[j] = 0;
        }
    }

    // fill off screen buffer
    for (int i = MATRIXES, k = 0; i < size + MATRIXES; i++, k++) {
        for (int j = 0; j < ROWS; j++) {
            buffer[i].rows[j] = bits[k].rows[j];
        }
    }

    run = true;

    doScroll(times, buffer.get(), text);

}

bool Scroller::isRunning() {
    return run;
}
