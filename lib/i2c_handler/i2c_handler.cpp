#include "i2c_handler.h"
#include "bit_ops.h"
#include <Wire.h>

bool i2cScan(){
  Serial.print("Scanning for I2C devices");
  for (int i = 0; i < 3; i++){
    delay(500);
    Serial.print(".");
  }
  delay(500);
  Serial.println();

  bool deviceDetected = 0;
  for (int addr = 1; addr < 127; addr++){
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0){
      Serial.print("Found device at address 0x");
      Serial.println(addr, HEX);
      deviceDetected = 1;
      }
    }
    return deviceDetected;
}

bool i2cInit(int sdaPin, int sclPin, uint32_t frequency){
    return Wire.begin(sdaPin, sclPin, frequency);
}

bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data){
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data);
    return Wire.endTransmission() == 0;
}

bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data, uint8_t mask){
  uint8_t config = i2cRead(addr, reg);
  config = writeBits(config, data, mask);
  return i2cWrite(addr, reg, config);
}

bool i2cWriteBit(uint8_t addr, uint8_t reg, bool myBit, uint8_t bitPos){
  if (bitPos > 7){
    return false;
  }
  return i2cWrite(addr, reg, (uint8_t)myBit << bitPos, 1 << bitPos);
}

uint8_t i2cRead(uint8_t addr, uint8_t reg) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission(false); // send repeated start

    Wire.requestFrom(addr, (uint8_t)1);
    return Wire.read();
}


uint16_t i2cReadTwo(uint8_t addr, uint8_t lsbReg, uint8_t msbReg){
  Wire.beginTransmission(addr);
  Wire.write(lsbReg);
  Wire.endTransmission();
  Wire.requestFrom(addr, (uint8_t)2);
  if(Wire.available() < 2) return 0;
  uint8_t lsb = Wire.read();
  uint8_t msb = Wire.read();
  return (int16_t)((msb << 8) | lsb);
}


