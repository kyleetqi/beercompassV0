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
    MPU6500(uint8_t myAddress);

    /**
     * @brief Set the gyroscope's reading offsets.
     * @param offsetX The gyroscope's X offset.
     * @param offsetY The gyroscope's Y offset.
     * @param offsetZ The gyroscope's Z offset.
     * @return True if the operation succeeded, false otherwise.
     */
    bool setGyroOffset(int16_t offsetX, int16_t offsetY, int16_t offsetZ);

    // TODO: Make better Doxygen
    // TODO: Add a default value for divier
    /**
     * @brief Sets the sample rate divider for the MPU6500.
     * @param divider value to write to the register.
     * @return true if the operation is successful, false otherwise.
     */
    bool setSampleRateDivider(uint8_t divider);

    // TODO: Maybe change the parameter to a bool
    /**
     * @brief Sets the FIFO mode of the IC.
     * 
     * When set to '1', when the FIFO is full, additional writes will
     * not be written to FIFO. When set to '0', when the FIFO is full, 
     * additional writes will be written to the FIFO, replacing the
     * oldest data.
     * 
     * @param mode The desired FIFO mode.
     * @return true if the operation is successful, false otherwise.
     */
    bool setFIFOMode(uint8_t mode = 1);

    // TODO: Rename this enum
    enum ExtSyncSource : uint8_t {
        EXT_SOURCE_DISABLE = 0,
        EXT_SOURCE_TEMP = 1,
        EXT_SOURCE_GYRO_X = 2,
        EXT_SOURCE_GYRO_Y = 3,
        EXT_SOURCE_GYRO_Z = 4,
        EXT_SOURCE_ACCEL_X = 5,
        EXT_SOURCE_ACCEL_Y = 6,
        EXT_SOURCE_ACCEL_Z = 7
    };

    // TODO: Implement this function
    bool setFSync(ExtSyncSource source);

    // TODO: Implement this function
    bool setGyroLPFMode(uint8_t mode = 0);

    // TODO: Implement this function
    bool setGyroRange(uint8_t range = 250);

    // TODO: Implement this function
    bool gyroLPFEnable(bool isOn = 1);

    // TODO: Implement this function
    bool setAccelRange(uint8_t range = 2);

    // TODO: Implement this function
    bool accelLPFENable(bool isOn = 1);

    // TODO: Implement this function
    bool setAccelLPFMode(uint8_t mode = 0);

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
};

#endif

