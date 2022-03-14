#include "nexa-controller.h"

#include <wiringPi.h>

#include <chrono>
#include <iostream>
#include <thread>

constexpr int TURNED_ON_COUNTER = 6;
constexpr int TURNED_OFF_COUNTER = 3;
constexpr int TRANSMIT_PIN = 0;
constexpr int PULSE_LENGTH = 250;              // us
constexpr int TURN_OFF_COOL_OFF_PERIOD = 260;  // ms
constexpr uint32_t MSB_BIT_MASK = 0x80000000;

NexaController::NexaController() : transmitPin{TRANSMIT_PIN}, pulseLength{PULSE_LENGTH} {}

void NexaController::sendTurnOn() {
    // turn on msg is sent/repeats 6 times
    std::cout << "sending turn on message..\n";
    const uint32_t TURN_ON_MSG = 0xAF44EF0;
    send(TURN_ON_MSG, TURNED_ON_COUNTER);
}

void NexaController::sendTurnOff() {
    // turn off msg is sent/repeats 3 times
    // MSG format HHHH HHHH HHHH HHHH HHHH HHHH HHGO EEEE -- see README
    // const char TURN_ON_MSG[8] =  { "00000", "1010", "1111", "0100", "0100", "1110", "1110", "0000" };
    // 0b1010111101000100111011100000 = 0xAF44EE0
    std::cout << "sending turn off message..\n";
    const uint32_t TURN_OFF_MSG = 0xAF44EE0;
    send(TURN_OFF_MSG, TURNED_OFF_COUNTER);
    std::this_thread::sleep_for(std::chrono::milliseconds(TURN_OFF_COOL_OFF_PERIOD));
    send(TURN_OFF_MSG, TURNED_OFF_COUNTER);
}

void NexaController::send(const uint32_t& msg, const int& repeat_cntr) {
    std::cout << "msg: " << msg << "\n"
              << "repeat cntr: " << repeat_cntr << "\n";

    for (int i = 0; i < repeat_cntr; ++i) {
        std::cout << "sent\n";
        sendPacket(msg);
    }
}

void NexaController::sendPacket(const uint32_t& msg) {
    transmit(startSymbol);
    sendMsg(msg);
    transmit(stopSymbol);
}

void NexaController::sendMsg(const uint32_t& msg) {
    for (unsigned int b_i = 0; b_i < 32; ++b_i) {
        if ((msg << b_i & MSB_BIT_MASK) != 0U) {
            transmit(oneSymbol);
            transmit(zeroSymbol);
        } else {
            transmit(zeroSymbol);
            transmit(oneSymbol);
        }
    }
    std::cout << std::endl;
}

void NexaController::transmit(signalSymbol_t symbol) const {
#ifdef PC_TEST
    if (symbol.firstPart.signallevel == SignalLevel::one) {
        for (int i = 0; i < symbol.firstPart.periodDuration; ++i) std::cout << "+";
    } else {
        for (int i = 0; i < symbol.firstPart.periodDuration; ++i) std::cout << "-";
    }

    if (symbol.secondPart.signallevel == SignalLevel::one) {
        for (int i = 0; i < symbol.secondPart.periodDuration; ++i) std::cout << "+";
    } else {
        for (int i = 0; i < symbol.secondPart.periodDuration; ++i) std::cout << "-";
    }

#else
    digitalWrite(this->transmitPin, static_cast<int>(symbol.firstPart.signallevel));
    delayMicroseconds(this->pulseLength * symbol.firstPart.periodDuration);
    digitalWrite(this->transmitPin, static_cast<int>(symbol.secondPart.signallevel));
    delayMicroseconds(this->pulseLength * symbol.secondPart.periodDuration);
#endif
}

int NexaController::getTransmitPin() const { return transmitPin; }
