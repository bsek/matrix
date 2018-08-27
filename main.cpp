#include <signal.h>
#include "RestHandler.h"
#include "Scroller.h"

#ifdef RPI
#include <wiringPiSPI.h>
#endif

void signalHandler(int s){
    printf("Caught signal %d\n",s);
    exit(1);

}

int main(int argc, char** argv) {

    // setup signal handler
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = signalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    Scroller scroller;

#ifdef RPI
    scroller.setupLEDMatrix(CHANNEL);
#endif

    RestHandler restHandler{scroller};
    restHandler.setup();
    restHandler.start();
    return 0;
}


