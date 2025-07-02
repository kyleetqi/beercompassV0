#ifndef I2C_HANDLER_H
#define I2C_HANDLER_H

#include <Arduino.h>

/**
 * @brief Scans for devices on the I2C lines.
 * @return true if a device was detected on the I2C lines, false otherwise.
 */
bool i2cScan();

/**
 * @brief Initializes the I2C lines.
 * @param sdaPin MCU serial data pin.
 * @param sclPin MCU serial clock pin.
 * @param frequency I2C line operational frequency.
 * @return true if initialization was successful, false otherwise.
 */
bool i2cInit(int sdaPin, int sclPin, uint32_t frequency);

/**
 * @brief Writes data to an I2C device's register.
 * @param addr The address of the I2C device.
 * @param reg The I2C device's targest register.
 * @param data The data to be written to the register.
 * @return true if writing was successful, false otherwise.
 */
bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data);

/**
 * @brief Reads data from an I2C device's register.
 * @param addr The address of the I2C device.
 * @param reg The I2C device's target register.
 * @return the data located in the target register.
 */
uint8_t i2cRead(uint8_t addr, uint8_t reg);

#endif