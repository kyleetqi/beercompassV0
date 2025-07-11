#ifndef MPU6500_H
#define MPU6500_H

#include <Arduino.h>
#include "mpu6500_registers.h"

class MPU6500{
    public:

    /**
     * @brief Class constructor.
     * @param myAddress The I2C address of the object.
     */
    mpu6500(uint8_t myAddress);

    /**
     * @brief Set the gyroscope's reading offsets.
     * @param offsetX The gyroscope's X offset.
     * @param offsetY The gyroscope's Y offset.
     * @param offsetZ The gyroscope's Z offset.
     * @return True if the operation succeeded, false otherwise.
     */
    bool setGyroOffset(int16_t offsetX, int16_t offsetY, int16_t offsetZ);

    /**
     * @brief Obtain the gyroscope's X reading.
     * @return The gyroscope's X reading.
     */
    int16_t getGyroX();

    /**
     * @brief Obtain the gyroscope's Y reading.
     * @return The gyroscope's Y reading.
     */
    int16_t getGyroY();

    /**
     * @brief Obtain the gyroscope's Z reading.
     * @return The gyroscope's Z reading.
     */
    int16_t getGyroZ();

    /**
     * @brief Obtain the accelerometer's X reading.
     * @return The acceleromter's X reading.
     */
    int16_t getAccelX();

    /**
     * @brief Obtain the accelerometer's Y reading.
     * @return The acceleromter's Y reading.
     */
    int16_t getAccelY();

    /**
     * @brief Obtain the accelerometer's Z reading.
     * @return The acceleromter's Z reading.
     */
    int16_t getAccelZ();

    /**
     * @brief Obtain the device's temperature reading.
     * @return The device's temperature reading in Celsius.
     */
    int16_t getTemp();

    private:
    uint8_t address;

    bool setGyroOffsetOne(uint16_t offset, uint8_t msbReg, uint8_t lsbReg);
};

#endif