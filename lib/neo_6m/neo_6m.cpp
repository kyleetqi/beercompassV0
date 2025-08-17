#include "neo_6m.h"

Neo6M::Neo6M(HardwareSerial &serial, uint16_t baud, uint8_t rxPin, uint8_t txPin)
: serial(serial), baudRate(baud), rx(rxPin), tx(txPin) {}

void Neo6M::begin(){
    this->serial.begin(this->baudRate);
}

bool Neo6M::read(){
    if (!this->serial.available()) {
        return false;
    }
    // Do some stuff here
    return true;
}