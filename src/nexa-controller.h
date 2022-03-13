#ifndef SRC_NEXA_CONTROLLER_H_
#define SRC_NEXA_CONTROLLER_H_

#include <stdint.h>


// #define PC_TEST 1 // don't forget to remove this on RPI!!


enum class SignalLevel { zero = 0, one = 1 };

typedef struct signalBit {
    SignalLevel signallevel;
    int periodDuration;
} signal_t;

typedef struct signalSymbol {
    signal_t firstPart;
    signal_t secondPart;
} signalSymbol_t;

class NexaController {
   public:
    explicit NexaController();
    ~NexaController();

    void sendTurnOn();
    void sendTurnOff();
    int getTransmitPin() const; 

   private:
    void send(const uint32_t& msg, const int& repeat_cntr);
    void sendPacket(const uint32_t& msg);
    void sendMsg(const uint32_t& msg);
    void transmit(signalSymbol_t symbol);

    const signalSymbol_t startSymbol{{SignalLevel::one, 1}, {SignalLevel::zero, 10}};
    const signalSymbol_t stopSymbol{{SignalLevel::one, 1}, {SignalLevel::zero, 40}};
    const signalSymbol_t oneSymbol{{SignalLevel::one, 1}, {SignalLevel::zero, 5}};
    const signalSymbol_t zeroSymbol{{SignalLevel::one, 1}, {SignalLevel::zero, 1}};

    int transmitPin;
    int pulseLength;
};

#endif  // SRC_NEXA_CONTROLLER_H_