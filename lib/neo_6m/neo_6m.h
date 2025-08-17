#ifndef NEO_6M_H
#define NEO_6M_H

#include <Arduino.h>

class Neo6M {
    public:

    Neo6M(HardwareSerial &serial, uint16_t baud = 9600, uint8_t rxPin, uint8_t txPin);

    void begin();
    bool read();

    float getHour() {return this->hour;}
    float getMinute() {return this->minute;}
    float getSecond() {return this->second;}
    float getLatitude() {return this->latitude;}
    float getLongitude() {return this->longitude;}
    float getHorizontalDilution() {return this->horizontalDilution;}
    float getAltitude() {return this->altitude;}
    float getGeoidHeight() {return this->geoidHeight;}
    float getNumSatelites() {return this->numSatelites;}
    
    private:

    HardwareSerial &serial;
    uint16_t baudRate;
    uint8_t rx, tx;

    uint8_t hour, minute, second;
    float longitude, latitude;
    float horizontalDilution;
    float altitude;
    float geoidHeight;
    uint8_t numSatelites;





};

#endif