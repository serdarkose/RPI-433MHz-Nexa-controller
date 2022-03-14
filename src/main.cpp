#include <cstring>
#include <iostream>
#include <string>

#include <wiringPi.h>

#include "nexa-controller.h"

// Use: rpi_nexa_controller <action>
// <action> ---> 1=switch on; 0=siwtch off
// example: rpi_nexa_controller 1
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Error: the use case is 'main 1' or 'main 0', please try it again!\n";
        exit(EXIT_FAILURE);
    }

    if ((strlen(argv[1]) != 1) || (atoi(argv[1]) < 0) || (atoi(argv[1]) > 1)) {
        std::cout << "Error: argument should be 1 or 0\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "configuring WirePi\n";
#ifndef PC_TEST
    if (wiringPiSetup() == -1) {
        std::cout << "wiringPiSetup failed!\n";
        exit(EXIT_FAILURE);
    }
#endif

    const int ACTION = atoi(argv[1]);
    NexaController nController = NexaController();

    pinMode(nController.getTransmitPin(), OUTPUT);  // Configure GPIO0 as an output
    digitalWrite(nController.getTransmitPin(), 0);

    switch (ACTION) {
        case 0:
            nController.sendTurnOff();
            break;
        case 1:
            nController.sendTurnOn();
            break;
        default:
            std::cout << "Error: undefined action!!\n";
            exit(EXIT_FAILURE);
    }

    return 0;
}