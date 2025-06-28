#ifndef I2C_HANDLER_H
#define I2C_HANDLER_H

#include <Arduino.h>

bool i2cScan();
bool i2cInit(int sdaPin, int sclPin, uint32_t frequency);
bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t i2cRead(uint8_t addr, uint8_t reg);


#endif