#include <string>
#include <mutex>
#include <vector>

#ifdef __arm__
#include <wiringPi.h>
#endif

#ifndef SPI_SCROLLER_H
#define SPI_SCROLLER_H

#define CHANNEL 0
#define ROWS 8
#define MATRIXES 9

struct Matrix {
    std::uint8_t rows[ROWS];
    char letter;
};

class Scroller {

    std::mutex run_mutex;
    bool run;

    void doScroll(int times, Matrix *buffer, const std::vector<int> &text);
    Matrix scroll(Matrix &matrix, Matrix &prest);
    void setupBits(std::vector<int> text, Matrix* matrix);
    void display(Matrix *matrix, int len);
    void printAll(Matrix *buffer, int len);
    void showBits(std::uint8_t x);
    uint8_t reverse(std::uint8_t n);

public:
    void setupText(int times, const std::vector<int> &str);
    void setRun(bool run);
    bool isRunning();
#ifdef __arm__
    void setupLEDMatrix(int channel);
    void setSPIValue(uint8_t reg, uint8_t val);
#endif

};


#endif //SPI_SCROLLER_H
