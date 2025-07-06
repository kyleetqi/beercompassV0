#ifndef MPU6500_H
#define MPU6500_H

#include <stdint.h>
#include "mpu6500_registers.h"

class mpu6500{
    public:

    mpu6500(uint8_t myAddr) : address(myAddr) {};

    private:
    uint8_t address;

};

#endif