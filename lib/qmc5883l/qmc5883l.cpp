#include "qmc5883l.h"
#include "i2c_handler.h"
#include "bit_ops.h"

QMC5883L::QMC5883L(uint8_t myAddress) : address(myAddress) {}

bool QMC5883L::setMode(Mode mode){
    uint8_t config = i2cRead(this->address, CTRLA_REG);

    // Early return if mode is already set properly
    if(readBits(config, 0b11) == static_cast<uint8_t>(mode)){
        return true;
    }

    // Mode must be set to suspend between different modes
    if (readBits(config, 0b11) != 0b00){
        config = writeBits(config, 0b00, 0b11);
        if (!i2cWrite(this->address, CTRLA_REG, config)){
            return false;
        }
        delay(100);
    }

    // Write to registers
    config = writeBits(config, static_cast<uint8_t>(mode), 0b11);
    return i2cWrite(this->address, CTRLA_REG, config);
}
    
bool QMC5883L::setOutputRate(uint8_t odr){
    // Set bits based on mode selected
    uint8_t bits;
    switch(odr){
        case 10: bits = 0b00; break;
        case 50: bits = 0b01; break;
        case 100: bits = 0b10; break;
        case 200: bits = 0b11; break;
        default: return false;
    }
    bits <<= 2;

    // Set output rate
    return i2cWrite(this->address, CTRLA_REG, bits, 0b00001100);
    // uint8_t config = i2cRead(this->address, CTRLA_REG);
    // config = writeBits(config, bits, 0b00001100);
    // return i2cWrite(this->address, CTRLA_REG, config);
}

bool QMC5883L::setOverSampleRate(uint8_t osr1){
    // Set bits based on mode selected
    uint8_t bits;
    switch(osr1){
        case 8: bits = 0b00; break;
        case 4: bits = 0b01; break;
        case 2: bits = 0b10; break;
        case 1: bits = 0b11; break;
        default: return false;
    }
    bits <<= 4;

    // Set over sample rate
    return i2cWrite(this->address, CTRLA_REG, bits, 0b00110000);
    // uint8_t config = i2cRead(this->address, CTRLA_REG);
    // config = writeBits(config, bits, 0b00110000);
    // return i2cWrite(this->address, CTRLA_REG, config);
}

bool QMC5883L::setDownSampleRate(uint8_t osr2){
    // Set bits based on mode selected
    uint8_t bits;
    switch(osr2){
        case 1: bits = 0b00; break;
        case 2: bits = 0b01; break;
        case 4: bits = 0b10; break;
        case 8: bits = 0b11; break;
        default: return false;
    }
    bits <<= 6;

    // Set down sample rate
    return i2cWrite(this->address, CTRLA_REG, bits, 0b11000000);
    // uint8_t config = i2cRead(this->address, CTRLA_REG);
    // config = writeBits(config, bits, 0b11000000);
    // return i2cWrite(this->address, CTRLA_REG, config);
}

bool QMC5883L::setRange(uint8_t rng){
    // Set bits based on mode selected
    uint8_t bits;
    switch(rng){
        case 30: bits = 0b00; break;
        case 12: bits = 0b01; break;
        case 8: bits = 0b10; break;
        case 2: bits = 0b11; break;
        default: return false;
    }
    bits <<= 2;

    // Set range
    return i2cWrite(this->address, CTRLB_REG, bits, 0b00001100);
    // uint8_t config = i2cRead(this->address, CTRLB_REG);
    // config = writeBits(config, bits, 0b00001100);
    // return i2cWrite(this->address, CTRLB_REG, config);
}

bool QMC5883L::setSetResetMode(SetResetMode mode){
    return i2cWrite(this->address, CTRLB_REG, static_cast<uint8_t>(mode), 0b11);
    // uint8_t config = i2cRead(this->address, CTRLB_REG);
    // config = writeBits(config, static_cast<uint8_t>(mode), 0b11);
    // return i2cWrite(this->address, CTRLB_REG, config);
}

bool QMC5883L::resetRegisters(){
    return i2cWrite(this->address, CTRLB_REG, 1 << 7, 1 << 7);
    // uint8_t config = i2cRead(this->address, CTRLB_REG);
    // writeBits(config, 0b10000000, 0b10000000);
    // return i2cWrite(this->address, CTRLB_REG, config);
}

bool QMC5883L::isDRDY(){
    return (i2cRead(this->address, STATUS_REG) & 0b01) != 0;
}

bool QMC5883L::isOVFL(){
    return (i2cRead(this->address, STATUS_REG) & 0b10) != 0;
}

void QMC5883L::calibrate(int calibrationTime){
    // Stores the max and min magnetometer reading
    int16_t minMaxReadings[3][2] = {
        {INT16_MAX, INT16_MIN},
        {INT16_MAX, INT16_MIN},
        {INT16_MAX, INT16_MIN},
    };

    // Tracks timestamp of last array update
    uint32_t timeStamp = millis();

    // If no new max values have been written for
    // calibrationTime seconds, then the compass is calibrated
    bool isCalibrated = false;
    while (!isCalibrated) {
        Serial.println("Keep moving compass...");
        int16_t readings[3] = {getXRaw(), getYRaw(), getZRaw()};

        for (int i = 0; i < 3; i++) {
            if (readings[i] < minMaxReadings[i][0]) {
                minMaxReadings[i][0] = readings[i];
                timeStamp = millis();
            }
            if (readings[i] > minMaxReadings[i][1]) {
                minMaxReadings[i][1] = readings[i];
                timeStamp = millis();
            }
        }

        if (millis() - timeStamp > calibrationTime) {
            isCalibrated = true;
        }
        delay(10);
    } 

    // Write the values to the object
    this->maxX = minMaxReadings[0][1];
    this->maxY = minMaxReadings[1][1];
    this->maxZ = minMaxReadings[2][1];
    this->minX = minMaxReadings[0][0];
    this->minY = minMaxReadings[1][0];
    this->minZ = minMaxReadings[2][0];

    // Write values to serial
    // Serial.print("X min val: ");
    // Serial.print(this->minX);
    // Serial.print(" ");
    // Serial.print("X max val: ");
    // Serial.println(this->maxX);

    // Serial.print("Y min val: ");
    // Serial.print(this->minY);
    // Serial.print(" ");
    // Serial.print("Y max val: ");
    // Serial.println(this->maxY);

    // Serial.print("Z min val: ");
    // Serial.print(this->minZ);
    // Serial.print(" ");
    // Serial.print("Z max val: ");
    // Serial.println(this->maxZ);

    Serial.println("If you want to hardcode debug values, add this to main:");
    Serial.print("<yourCompassName>.setCalibrationData(");
    Serial.print(this->maxX);
    Serial.print(", ");
    Serial.print(this->maxY);
    Serial.print(", ");
    Serial.print(this->maxZ);
    Serial.print(", ");
    Serial.print(this->minX);
    Serial.print(", ");
    Serial.print(this->minY);
    Serial.print(", ");
    Serial.print(this->minZ);
    Serial.print(");");
}

void QMC5883L::setCalibrationData(int16_t maxX, int16_t maxY, int16_t maxZ, int16_t minX, int16_t minY, int16_t minZ){
    this->maxX = maxX;
    this->maxY = maxY;
    this->maxZ = maxZ;
    this->minX = minX;
    this->minY = minY;
    this->minZ = minZ;
}

int16_t QMC5883L::getXRaw() {
    return (int16_t)(i2cReadTwo(this->address, XMSB_REG, XLSB_REG));
}

int16_t QMC5883L::getYRaw() {
    return (int16_t)(i2cReadTwo(this->address, YMSB_REG, YLSB_REG));
}

int16_t QMC5883L::getZRaw() {
    return (int16_t)(i2cReadTwo(this->address, ZMSB_REG, ZLSB_REG));
}

float QMC5883L::getX() {return normalize(getXRaw(), this->maxX, this->minX);}
float QMC5883L::getY() {return normalize(getYRaw(), this->maxY, this->minY);}
float QMC5883L::getZ() {return normalize(getZRaw(), this->maxZ, this->minZ);}

float QMC5883L::azimuth(int16_t normX, int16_t normY){
    float angle = atan2(normY, normX); // Obtain angle in radians
    angle *= RAD_TO_DEG; // Convert to degrees
    // Convert angle to compass sign convention
    return fmod(450-angle, 360);
}

float QMC5883L::normalize(int16_t val, int16_t maxVal, int16_t minVal) {
    float center = (maxVal + minVal)/2.0f;
    float halfRange = (maxVal - minVal)/2.0f;
    return (val - center)/ halfRange;
}