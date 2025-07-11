#include "mpu6500.h"
#include "i2c_handler.h"
#include "bit_ops.h"

bool MPU6500::setGyroOffset(int16_t offsetX, int16_t offsetY, int16_t offsetZ){

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
    return (reading - tempOffset)/tempSensitivity + 21;
}

bool MPU6500::setGyroOffsetOne(int16_t data, uint8_t lsbReg, uint8_t msbReg){
    
}