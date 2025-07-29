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

    // TODO: Make better Doxygen.
    // TODO: Add a default value for divier.
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
    bool setFIFOMode(bool stopWhenFull = 1);

    /**
     * @brief typedef defining the external sync sources for setFSync
     */
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

    // TODO: Create Doxygen
    bool setFSync(ExtSyncSource source = EXT_SOURCE_DISABLE);

    // TODO: choose sensible default parameter value.
    /**
     * @brief Sets the gyroscope and temperature sensor LPF.
     * @param isOn true to enable the LPF, false to disable it.
     * @param bandwidth The bandwidth of the LPF.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setGyroLPF(bool isOn, uint8_t bandwidth = 250);

    // TODO: choose sensible default parameter value.
    /**
     * @brief Set the gryo full scale range.
     * @param range The desired range. Valid values: 250, 500, 1000, 200 (dps). Default value: 250.
     * @return true if configuration is successful, false otherwise.
     */
    bool setGyroRange(uint8_t range = 250);

    /**
     * @brief Enables/disables the gyroscope and temperature sensor LPF.
     * @note If the LPF is disabled, FCHOICE_B bits default to 01.
     * @param inOn true to enable the LPF, false to disable it.
     * @return true if the configuration is successful, false otherwise.
     */
    bool gyroLPFEnable(bool isOn = 1);

    // TODO: choose sensible default parameter value.
    /**
     * @brief Set the accelerometer full scale range.
     * @param range The desired range. Valid values: 2, 4, 8, 16 (g). Default value: 2.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setAccelRange(uint8_t range = 2);

    /**
     * @brief Enables/disables the accelerometer LPF.
     * @param isOn true to enable the LPF, false to disable it.
     * @return true if the configuration is successful, false otherwise.
     */
    bool accelLPFEnable(bool isOn = 1);

    // TODO: choose sensible default parameter value.
    /**
     * @brief Sets the accelerometer LPF.
     * @param isON true to enable the LPF, false to disable it.
     * @param bandwidth the bandwidth of the LPF.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setAccelLPFMode(bool isOn, uint8_t bandwidth = 460);

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

    /** 
     * @brief Resets the IC's registers.
     * @return true if the operation is successful, false otherwise.
     */
    bool resetRegisters();

    /**
     * @brief Sets the chip to sleep.
     * @return true if the operation is successful, false otherwise.
     */
    bool sleep();

    /**
     * @brief Wakes up the chip.
     * @return true if the operation is successful, false otherwise.
     */
    bool wake();

    /**
     * @brief Sets the chip to sleep or wake.
     * @param isAsleep true to set the chip to sleep mode, false to set to wake.
     * @return true if the operation is successful, false otherwise.
     */
    bool setSleepMode(bool isAsleep);

    // TODO: Implement function for CYCLE bit
    // PWR_MGMT_1 Register

    /**
     * @brief Enables/disables the temperature sensor.
     * @param isEnable true to enable the sensor, false othwerise.
     * @return true if the operation is successful, false otherwise.
     */
    bool enableTempSense(bool isEnable);


    // TODO: Implement function for LP_WAKE_CTRL bits
    // PWR_MGMT_2 Register

    /**
     * @brief Enables/disables the X accelerometer.
     * @param isEnable true to enable the accelerometer, false otherwise.
     * @return true if the operation is successful, false otherwise.
     */
    bool enableXAccel(bool isEnable);

    /**
     * @brief Enables/disables the Y accelerometer.
     * @param isEnable true to enable the accelerometer, false otherwise.
     * @return true if the operation is successful, false otherwise.
     */
    bool enableYAccel(bool isEnable);

    /**
     * @brief Enables/disables the Z accelerometer.
     * @param isEnable true to enable the accelerometer, false otherwise.
     * @return true if the operation is successful, false otherwise.
     */
    bool enableZAccel(bool isEnable);

    /**
     * @brief Enables/disables the X gyroscope.
     * @param isEnable true to enable the gyroscope, false otherwise.
     * @return true if the operation is successful, false otherwise.
     */
    bool enableXGyro(bool isEnable);

    /**
     * @brief Enables/disables the Y gyroscope.
     * @param isEnable true to enable the gyroscope, false otherwise.
     * @return true if the operation is successful, false otherwise.
     */
    bool enableYGyro(bool isEnable);

    /**
     * @brief Enables/disables the Z gyroscope.
     * @param isEnable true to enable the gyroscope, false otherwise.
     * @return true if the operation is successful, false otherwise.
     */
    bool enableZGyro(bool isEnable);

    /**
     * @brief Enables/disables the accelerometers.
     * @param isEnable true to enable the accelerometers, false otherwise.
     * @return true if the operation is successful, false otherwise.
     */
    bool enableAccel(bool isEnable);

    /**
     * @brief Enables/disables the gyroscopes.
     * @param isEnable true to enable the gyroscope, false otherwise.
     * @return true if the operation is successful, false otherwise.
     */
    bool enableGyro(bool isEnable);

    // TODO: Create doxygen.
    /**
     * @brief
     * @return
     */
    uint8_t whoAmI();

    // TODO: Add XA_OFFS and sim functions or something

    private:

    /**
     * @brief The I2C address of the device.
     */
    uint8_t address;

    /**
     * @brief Sets a single bit in a desired chip register. Used for set/reset purposes.
     * @param reg The desired register to be modifed.
     * @param myBit The bit to write to the register.
     * @param bitPos The target bit position in the desired register.
     * @return true if the operation is successful, false otherwise.
     */
    bool setRegBit(uint8_t reg, bool myBit, uint8_t bitPos);
};

#endif

