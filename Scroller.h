#include <string>

#ifndef SPI_SCROLLER_H
#define SPI_SCROLLER_H

#define CHANNEL 0
#define ROWS 8
#define MATRIXES 6

struct Matrix {
    std::uint8_t rows[ROWS];
    char letter;
};

class Scroller {
private:
    bool run;

    void doScroll(int times, Matrix *buffer, std::string &text);
    Matrix scroll(Matrix &matrix, Matrix &prest);
    void setupBits(std::string text, Matrix* matrix);
    void display(Matrix *matrix, int len);
    void printAll(Matrix *buffer, int len);
    void showBits(std::uint8_t x);
    uint8_t reverse(std::uint8_t n);

public:
    void setupText(int times, std::string &text);
    void setRun(bool run);
#ifdef RPI
    void setupLEDMatrix(int channel);
    void setSPIValue(uint8_t reg, uint8_t val);
#endif

};


#endif //SPI_SCROLLER_H
