#include "i2c_handler.h"
#include <Arduino.h>
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

uint8_t i2cRead(uint8_t addr, uint8_t reg){
    Wire.beginTransmission(addr);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0){
        return 0; // TODO: need to figure out a failed read return
    }

    uint8_t numBytes = 1; // Need dummy variable to get rid of warning :/
    Wire.requestFrom(addr, numBytes);
    if(Wire.available()){
        return Wire.read();
    }
    return 0; // TODO: need to figure out a failed read return
}
