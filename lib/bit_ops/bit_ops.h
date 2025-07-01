#ifndef BIT_OPS_H
#define BIT_OPS_H

#include <Arduino.h>

inline uint8_t setBits(uint8_t reg, uint8_t mask){
    return reg |= mask;
}

inline uint8_t clearBits(uint8_t reg, uint8_t mask){
    return reg &= ~mask;
}

inline uint8_t toggleBits(uint8_t reg, uint8_t mask){
    return reg ^= mask;
}

inline uint8_t writeBits(uint8_t reg, uint8_t value, uint8_t mask){
    if (clearBits(value, mask) != 0 ){
        Serial.println("Warning: writeBits call contains value bits outside the mask!");
    }
    return clearBits(reg, mask) | (value & mask);
}

inline uint8_t readBits(uint8_t reg, uint8_t mask){
    // Aligns return result to LSB
    while ((mask & 0x01) == 0){
        mask >>= 1;
        reg >>=1;
    }
    return reg & mask;
}

#endif