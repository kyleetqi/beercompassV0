#include "qmc5883l.h"
#include "i2c_handler.h"
#include "bit_ops.h"

bool qmc5883l::setMode(Mode mode){
    uint8_t current = i2cRead(this->address, CTRLA_REG);

    // TODO: I might remove this block of code
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
    switch(odr){
        case 10: bits = 0b00; break;
        case 50: bits = 0b01; break;
        case 100: bits = 0b10; break;
        case 200: bits = 0b11; break;
        default: return false;
    }
    bits <<= 2;

    // Set output rate
    uint8_t current = i2cRead(this->address, CTRLA_REG);
    current = writeBits(current, bits, 0b00001100);
    return i2cWrite(this->address, CTRLA_REG, current);
}

bool qmc5883l::setOverSampleRate(uint8_t osr1){
    // Set bits based on mode selected
    uint8_t bits;
    switch(osr1){
        case 8: bits = 0b00; break;
        case 4: bits = 0b01; break;
        case 2: bits = 0b10; break;
        case 1: bits = 0b11; break;
        default: return false;
    }
    bits <<= 4;

    // Set over sample rate
    uint8_t current = i2cRead(this->address, CTRLA_REG);
    current = writeBits(current, bits, 0b00110000);
    return i2cWrite(this->address, CTRLA_REG, current);
}

bool qmc5883l::setDownSampleRate(uint8_t osr2){
    // Set bits based on mode selected
    uint8_t bits;
    switch(osr2){
        case 1: bits = 0b00; break;
        case 2: bits = 0b01; break;
        case 4: bits = 0b10; break;
        case 8: bits = 0b11; break;
        default: return false;
    }
    bits <<= 6;

    // Set down sample rate
    uint8_t current = i2cRead(this->address, CTRLA_REG);
    current = writeBits(current, bits, 0b11000000);
    return i2cWrite(this->address, CTRLA_REG, current);
}

bool qmc5883l::setSetResetMode(uint8_t mode){
    

}

bool qmc5883l::setRange(uint8_t rng){
    // Set bits based on mode selected
    uint8_t bits;
    switch(rng){
        case 30: bits = 0b00; break;
        case 12: bits = 0b01; break;
        case 8: bits = 0b10; break;
        case 2: bits = 0b11; break;
        default: return false;
    }
    bits <<= 2;

    // Set range
    uint8_t current = i2cRead(this->address, CTRLB_REG);
    current = writeBits(current, bits, 0b00001100);
    return i2cWrite(this->address, CTRLB_REG, current);
}

bool qmc5883l::resetRegisters(){
    uint8_t current = i2cRead(this->address, CTRLB_REG);
    writeBits(current, 0b10000000, 0b10000000);
    return i2cWrite(this->address, CTRLB_REG, current);
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