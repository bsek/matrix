#include <signal.h>
#include "RestHandler.h"
#include "Scroller.h"

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

#ifdef __arm__
    scroller.setupLEDMatrix(CHANNEL);
#endif

    RestHandler restHandler{scroller};
    restHandler.setup();
    restHandler.start();
    return 0;
}


