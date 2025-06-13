#include "qmc5883l.h"
#include <Arduino.h>
#include <Wire.h>

qmc5883l::CalibrationData qmc5883l::calibrate(int calibrationTime){

    bool isCalibrated = false;

    /*
    Stores the maximum magnetometer reading
    plus the time it was recorded at
    */
    int maxReadings[3][2]{
        {getX(), (int)millis()},
        {getY(), (int)millis()},
        {getZ(), (int)millis()},
    };

    // If no new max values have been written for
    // 5 seconds, then the compass is calibrated
    while (!isCalibrated) {

        uint32_t now = millis();
        int readings[3] = {getX(), getY(), getZ()};

        for (int i = 0; i < 3; i++) {
            if (readings[i] > maxReadings[i][0]) {
                maxReadings[i][0] = readings[i];
                maxReadings[i][1] = now;
            }
        }
        
        if ((now - maxReadings[0][1]) > calibrationTime &&
            (now - maxReadings[1][1]) > calibrationTime &&
            (now - maxReadings[2][1]) > calibrationTime)
            isCalibrated = true;
    } 

    return CalibrationData{
        maxReadings[0][0],
        maxReadings[1][0],
        maxReadings[2][0],
    };

}

int qmc5883l::getReading(){
    return 1;
}

int qmc5883l::getX() {
    // TODO: create function
    return 1;
}

int qmc5883l::getY() {
    // TODO: create function
    return 1;
}

int qmc5883l::getZ() {
    // TODO: create function
    return 1;
}

float qmc5883l::normalize(float val) {
    if (val >= 0)
        return val/32767.0f;
    return val/32768.0f;
}

float qmc5883l::getXNormalized() { return normalize(float(getX())); }
float qmc5883l::getYNormalized() { return normalize(float(getX())); }
float qmc5883l::getZNormalized() { return normalize(float(getZ())); }