#include "mpu6500.h"
#include "i2c_handler.h"
#include "bit_ops.h"

MPU6500::MPU6500(uint8_t myAddress) : address(myAddress) {}

bool MPU6500::setGyroOffset(int16_t offsetX, int16_t offsetY, int16_t offsetZ){
    uint8_t lsbMask = 0b11111111;
    uint8_t xMSB = offsetX >> 8;
    uint8_t yMSB = offsetY >> 8;
    uint8_t zMSB = offsetZ >> 8;
    uint8_t xLSB = offsetX & lsbMask;
    uint8_t yLSB = offsetY & lsbMask;
    uint8_t zLSB = offsetZ & lsbMask;
    bool success = true;
    success &= i2cWrite(this->address, XG_OFFSET_H, xMSB);
    success &= i2cWrite(this->address, YG_OFFSET_H, yMSB);
    success &= i2cWrite(this->address, ZG_OFFSET_H, zMSB);
    success &= i2cWrite(this->address, XG_OFFSET_L, xLSB);
    success &= i2cWrite(this->address, YG_OFFSET_L, yLSB);
    success &= i2cWrite(this->address, ZG_OFFSET_L, zLSB);
    return success;
}

bool MPU6500::setSampleRateDivider(uint8_t divider){
    return i2cWrite(this->address, SMPLRT_DIV, divider);
}

bool MPU6500::setFIFOMode(bool stopWhenFull){
    return setRegBit(CONFIG, stopWhenFull, 6);
}

bool MPU6500::setFSync(ExtSyncSource source){
    uint8_t bits = static_cast<uint8_t>(source) << 3;
    return i2cWrite(this->address, CONFIG, bits, 0b00111000);
}


bool MPU6500::setGyroLPF(bool isOn, uint8_t bandwidth){
    // Enable/Disable the LPF
    if(!(this->gyroLPFEnable(isOn))){
        return false;
    }
    // Configure LPF if on
    if (isOn) {
        // Set bits based on mode selected
        uint8_t bits;
        switch(bandwidth){
            case 250: bits = 0; break;
            case 184: bits = 1; break;
            case 92: bits = 2; break;
            case 41: bits = 3; break;
            case 20: bits = 4; break;
            case 10: bits = 5; break;
            case 5: bits = 6; break;
            case 3600: bits = 7; break;
            default: return false;
        }

        // Write bits to register
        return i2cWrite(this->address, CONFIG, bits, 0b00000111);
    }
    return true;
}

bool MPU6500::setGyroRange(uint8_t range){
    // Set bits based on mode selected
    uint8_t bits;
    switch(range){
        case 250: bits = 0b00; break;
        case 500: bits = 0b01; break;
        case 1000: bits = 0b10; break;
        case 2000: bits = 0b11; break;
        default: return false;
    }
    bits <<= 3;

    // Set gyro range
    return i2cWrite(this->address, GYRO_CONFIG, bits, 0b00011000);
}

bool MPU6500::gyroLPFEnable(bool isOn){
    // Configure bits based on isOn
    uint8_t bits = 0b01;
    if (isOn){
        bits = 0b00;
    }

    // Write bits to register
    return i2cWrite(this->address, GYRO_CONFIG, bits, 0b00000011);
}

bool MPU6500::setAccelRange(uint8_t range){
    // Set bits based on mode selected
    uint8_t bits;
    switch(range){
        case 2: bits = 0b00; break;
        case 4: bits = 0b01; break;
        case 8: bits = 0b10; break;
        case 16: bits = 0b11; break;
        default: return false;
    }
    bits <<= 3;

    // Write bits to register
    return i2cWrite(this->address, ACCEL_CONFIG, bits, 0b00011000);
}

bool MPU6500::accelLPFEnable(bool isOn){
    // Configure bits based on isOn
    uint8_t bits = 1;
    if (isOn){
        bits = 0;
    }
    bits <<= 3;

    // Write bits to register
    return i2cWrite(this->address, ACCEL_CONFIG_2, bits, 0b00001000);
}

bool MPU6500::setAccelLPFMode(bool isOn, uint8_t bandwidth){
    // Enable/Disable the LPF
    if(!(this->accelLPFEnable(isOn))){
        return false;
    }
    // Configure LPF if on
    if (isOn) {
        // Set bits based on mode selected
        uint8_t bits;
        switch(bandwidth){
            case 460: bits = 0; break;
            case 184: bits = 1; break;
            case 92: bits = 2; break;
            case 41: bits = 3; break;
            case 20: bits = 4; break;
            case 10: bits = 5; break;
            case 5: bits = 6; break;
            default: return false;
        }

        // Write bits to register
        return i2cWrite(this->address, ACCEL_CONFIG_2, bits, 0b00000111);
    }
    return true;
}

// TODO: Update read functions to update the object's values.

int16_t MPU6500::readGyroX(){
    return (int16_t)(i2cReadTwo(this->address, GYRO_XOUT_H, GYRO_XOUT_L));
}

int16_t MPU6500::readGyroY(){
    return (int16_t)(i2cReadTwo(this->address, GYRO_YOUT_H, GYRO_YOUT_L));
}

int16_t MPU6500::readGyroZ(){
    return (int16_t)(i2cReadTwo(this->address, GYRO_ZOUT_H, GYRO_ZOUT_L));
}

int16_t MPU6500::readAccelX(){
    return (int16_t)(i2cReadTwo(this->address, ACCEL_XOUT_H, ACCEL_XOUT_L));
}

int16_t MPU6500::readAccelY(){
    return (int16_t)(i2cReadTwo(this->address, ACCEL_YOUT_H, ACCEL_YOUT_L));
}

int16_t MPU6500::readAccelZ(){
    return (int16_t)(i2cReadTwo(this->address, ACCEL_ZOUT_H, ACCEL_ZOUT_L));
}

int16_t MPU6500::readTemp(){
    int16_t reading = (int16_t)(i2cReadTwo(this->address, TEMP_OUT_H, TEMP_OUT_L));
    // Convert the reading into degrees Celsius. Reference the data sheet for equation
    // TODO: Define tempOffset and tempSensitivity
    // return (reading - tempOffset)/tempSensitivity + 21;
    return reading;
}

bool MPU6500::resetRegisters(){
    return i2cWrite(this->address, PWR_MGMT_1, 1, 0b10000000);
}

bool MPU6500::sleep(){
    return setSleepMode(1);
}

bool MPU6500::wake(){
    return setSleepMode(0);
}

bool MPU6500::setSleepMode(bool isAsleep){
    return setRegBit(PWR_MGMT_1, isAsleep, 6);
}

bool MPU6500::enableTempSense(bool isEnable){
    return setRegBit(PWR_MGMT_1, !isEnable, 3);
}

bool MPU6500::enableXAccel(bool isEnable){
    return setRegBit(PWR_MGMT_2, !isEnable, 5);
}

bool MPU6500::enableYAccel(bool isEnable){
    return setRegBit(PWR_MGMT_2, !isEnable, 4);
}

bool MPU6500::enableZAccel(bool isEnable){
    return setRegBit(PWR_MGMT_2, !isEnable, 3);
}

bool MPU6500::enableXGyro(bool isEnable){
    return setRegBit(PWR_MGMT_2, !isEnable, 2);
}

bool MPU6500::enableYGyro(bool isEnable){
    return setRegBit(PWR_MGMT_2, !isEnable, 1);
}

bool MPU6500::enableZGyro(bool isEnable){
    return setRegBit(PWR_MGMT_2, !isEnable, 0);
}

bool MPU6500::enableAccel(bool isEnable){
    bool success = enableXAccel(isEnable);
    success &= enableYAccel(isEnable);
    success &= enableZAccel(isEnable);
    return success;
}

bool MPU6500::enableGyro(bool isEnable){
    bool success = enableXGyro(isEnable);
    success &= enableYGyro(isEnable);
    success &= enableZGyro(isEnable);
    return success;
}

uint8_t MPU6500::whoAmI(){
    return i2cRead(this->address, WHO_AM_I);
}

bool MPU6500::setRegBit(uint8_t reg, bool myBit, uint8_t bitPos){
    return i2cWrite(this->address, reg, (uint8_t)myBit, 1 << bitPos);
}