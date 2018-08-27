#include <served/served.hpp>
#include "Scroller.h"

#ifndef SPI_RESTHANDLER_H
#define SPI_RESTHANDLER_H

class RestHandler {

private:
    served::multiplexer mux;
    Scroller &scroller;
public:
    RestHandler(Scroller &scroller);

    void setup();
    void start();
};


#endif //SPI_RESTHANDLER_H
