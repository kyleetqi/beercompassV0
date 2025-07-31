#ifndef NEO_6M_H
#define NEO_6M_H

#include <Arduino.h>

class NEO6M {
    public:

    bool begin();
    bool update();

    float getLatitude();
    float getLongitude();
    float getSpeed();
    float getCourse();
    uint8_t getSatelites();

    int getHour();
    int getMinute();
    int getSecond();
    int getDay();
    int getMonth();
    int getYear();

    bool isValidLocation();
    bool isValidTime();
    bool isValidDate();
    bool isConnected();

    void sendCommand(const char *cmd);
    void printRaw(Stream &out);
    String getLastNMEASentence();

    private:

};

#endif