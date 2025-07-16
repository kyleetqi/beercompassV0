#include "mpu6500.h"
#include "i2c_handler.h"
#include "bit_ops.h"

MPU6500::MPU6500(uint8_t myAddress) : address(myAddress) {};

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

bool MPU6500::setFIFOMode(uint8_t mode){
    if (mode != 0 || mode != 1){
        return false;
    }
    mode <<= 6;

    // Set FIFO Mode
    uint8_t current = i2cRead(this->address, CONFIG);
    current = writeBits(current, mode, 0b01000000);
    return i2cWrite(this->address, CONFIG, current);    
}

int16_t MPU6500::getGyroX(){
    return (int16_t)(i2cReadTwo(this->address, GYRO_XOUT_H, GYRO_XOUT_L));
}

int16_t MPU6500::getGyroY(){
    return (int16_t)(i2cReadTwo(this->address, GYRO_YOUT_H, GYRO_YOUT_L));
}

int16_t MPU6500::getGyroZ(){
    return (int16_t)(i2cReadTwo(this->address, GYRO_ZOUT_H, GYRO_ZOUT_L));
}

int16_t MPU6500::getAccelX(){
    return (int16_t)(i2cReadTwo(this->address, ACCEL_XOUT_H, ACCEL_XOUT_L));
}

int16_t MPU6500::getAccelY(){
    return (int16_t)(i2cReadTwo(this->address, ACCEL_YOUT_H, ACCEL_YOUT_L));
}

int16_t MPU6500::getAccelZ(){
    return (int16_t)(i2cReadTwo(this->address, ACCEL_ZOUT_H, ACCEL_ZOUT_L));
}

int16_t MPU6500::getTemp(){
    int16_t reading = (int16_t)(i2cReadTwo(this->address, TEMP_OUT_H, TEMP_OUT_L));
    // Convert the reading into degrees Celsius. Reference the data sheet for equation
    // TODO: Define tempOffset and tempSensitivity
    // return (reading - tempOffset)/tempSensitivity + 21;
    return reading;
}