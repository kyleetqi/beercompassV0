#ifndef NEO_6M_H
#define NEO_6M_H

#include <Arduino.h>

class Neo6M {
    public:

    Neo6M(HardwareSerial &serial, int baud = 9600, int rxPin, int txPin);

    void begin();
    void read();

    double getLatitude();

    private:

    HardwareSerial &serial;
    int baudRate;
    int rx, tx;

};

#endif