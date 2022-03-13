#include <iostream>
#include <string>
#include <string.h>

#include "nexa-controller.h"

// Use: rpi_nexa_controller <command>
// <command> ---> 1=switch on; 0=siwtch off
// example: rpi_nexa_controller 1
int main(int argc, char *argv[])
{
    if(argc != 2){
        std::cout << "Error: the use case is 'main 1' or 'main 0', please try it again!\n";
        exit(EXIT_FAILURE);
    }

    if( (strlen(argv[1]) != 1) || (atoi(argv[1]) <0) || (atoi(argv[1]) >1) ){
        std::cout << "Error: argument should be 1 or 0\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "success" << std::endl;

    return 0;
}