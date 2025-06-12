#include "qmc5883l.h"
#include <Arduino.h>
#include <Wire.h>

void qmc5883l::calibrate(int calibrationTime){

    bool isCalibrated = false;

    /*
    Stores the maximum magnetometer reading
    plus the time it was recorded at
    */
    int maxReadings[3][2]{
        {getX(), 0},
        {getY(), 0},
        {getZ(), 0},
    };

    /*
    If no new max values have been written for
    5 seconds, then the compass is calibrated
    */
    while (isCalibrated = false) {

        uint32_t now = millis();
        int xRead = getX();
        int yRead = getY();
        int zRead = getZ();

        if (xRead > maxReadings[1][1]) {
            maxReadings[1][1] = xRead;
            maxReadings[1][2] = now;
            isCalibrated = false;
        }
        if (yRead > maxReadings[2][1]) {
            maxReadings[2][1] = xRead;
            maxReadings[2][2] = now;
            isCalibrated = false;
        }
        if (zRead > maxReadings[3][1]) {
            maxReadings[3][1] = xRead;
            maxReadings[3][2] = now;
            isCalibrated = false;
        }
        
        if ((now - maxReadings[1][2]) > calibrationTime ||
            (now - maxReadings[2][2]) > calibrationTime ||
            (now - maxReadings[3][2]) > calibrationTime)
            isCalibrated = true;
    } 

    return; 
    // TODO: Make this return type not void

}

int qmc5883l::getReading(){
    return 1;
}

int qmc5883l::getX() {
    // TODO: create function
    return 1;
}

int qmc5883l::getY() {
    return 1;
}

int qmc5883l::getZ() {
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