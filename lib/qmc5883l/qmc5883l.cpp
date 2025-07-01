#include "qmc5883l.h"
#include "i2c_handler.h"
#include "bit_ops.h"

bool qmc5883l::setMode(Mode mode){
    uint8_t current = i2cRead(this->address, CTRLA_REG);

    // Early return if mode is already set properly
    if(readBits(current, 0b11) == static_cast<uint8_t>(mode)){
        return true;
    }

    // Mode must be set to suspend between different modes
    if (readBits(current, 0b11) != 0b00){
        current = writeBits(current, 0b00, 0b11);
        if (!i2cWrite(this->address, CTRLA_REG, current)){
            return false;
        }
        delay(100);
    }

    // Write to registers
    current = writeBits(current, static_cast<uint8_t>(mode), 0b11);
    return i2cWrite(this->address, CTRLA_REG, current);
}
    
bool qmc5883l::setOutputRate(uint8_t odr){

    // Set bits based on mode selected
    uint8_t bits;
    if(odr == 10){
        bits = 0b00;
    }else if (odr == 50){
        bits = 0b01;
    }else if (odr == 100){
        bits = 0b10;
    }else if (odr == 200){
        bits = 0b11;
    }else {
        return false;
    }

    // Write to register
    return i2cWrite(this->address, CTRLA_REG, bits);

}

bool setOverSampleRate(uint8_t osr1){

}

bool setDownSampleRate(uint8_t osr2){

}

bool setSetResetMode(uint8_t mode){

}

bool setRange(uint8_t rng){

}

bool resetRegisters(){

}

qmc5883l::CalibrationData qmc5883l::calibrate(int calibrationTime){

    // Stores the maximum magnetometer reading
    // Plus the time it was recorded at
    int maxReadings[3][2]{
        {getX(), (int)millis()},
        {getY(), (int)millis()},
        {getZ(), (int)millis()},
    };

    // If no new max values have been written for
    // 5 seconds, then the compass is calibrated
    bool isCalibrated = false;
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

    // Return struct containing calibration data
    return CalibrationData{
        maxReadings[0][0],
        maxReadings[1][0],
        maxReadings[2][0],
    };

}

bool qmc5883l::isDRDY(){
    return (i2cRead(this->address, STATUS_REG) & 1);
}

bool isOVFL(){

}

uint16_t qmc5883l::getX() {
    int16_t result = i2cRead(this->address, XMSB_REG) << 8;
    result |= i2cRead(this->address, XLSB_REG);
    return result;
}

uint16_t qmc5883l::getY() {
}

uint16_t qmc5883l::getZ() {
}

float qmc5883l::normalize(float val) {
    if (val >= 0)
        return val/32767.0f;
    return val/32768.0f;
}

float qmc5883l::getXNormalized() { return normalize(float(getX())); }
float qmc5883l::getYNormalized() { return normalize(float(getX())); }
float qmc5883l::getZNormalized() { return normalize(float(getZ())); }

float getTemperature(){
    return 1;
}