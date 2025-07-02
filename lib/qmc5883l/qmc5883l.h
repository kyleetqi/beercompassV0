#ifndef HMC5883L_H
#define HMC5883L_H

#include <Arduino.h>

// Magnetometer registers
#define XLSB_REG 0x01
#define XMSB_REG 0x02
#define YLSB_REG 0x03
#define YMSB_REG 0x04
#define ZLSB_REG 0x05
#define ZMSB_REG 0x06
#define STATUS_REG 0x09
#define CTRLA_REG 0x0A
#define CTRLB_REG 0x0B

class qmc5883l {
    public:

    qmc5883l(uint8_t myAddr){
        address = myAddr;
    };

    enum class Mode : uint8_t {
        Suspend = 0b00,
        Normal = 0b01,
        Single = 0b10,
        Continuous = 0b11,
    };

    /** 
     * @brief Sets the magnetometer's data output mode.
     * @param mode Magnetometer mode.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setMode(Mode mode);

    /**
     * @brief Sets the magnetometer's data output frequency.
     * @param odr Output data rate in Hz. Valid values: 10, 50, 100, 200. Default value is 100.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setOutputRate(uint8_t odr = 100);

    /**
     * @brief Sets the magnetometer's over sample rate.
     * @param 
     */
    bool setOverSampleRate(uint8_t osr1 = 2);
    bool setDownSampleRate(uint8_t osr2 = 4);

    bool setSetResetMode(uint8_t mode = 0b01);
    bool setRange(uint8_t rng = 0b11);
    bool resetRegisters();

    /** 
     * @brief Tells you if the magnetometer has data ready
     * @return The status of the magnetometer
     */
    bool isDRDY();

    bool isOVFL();

    /** 
     * @brief Calculates the maximum readings in the X, Y, and Z axis
     * @param calibrationTime calibration is complete when no new values for this amount of time
     * 
     */
    void calibrate(int calibrationTime);

    /** 
     * @brief Obtains the magnetometer's reading in the X axis
     * 
     */
    int16_t getXRaw();

    /** 
     * @brief Obtains the magnetometer's reading in the Y axis
     * 
     */
    int16_t getYRaw();

    /**
    * @brief Obtains the magnetometer's reading in the Z axis
    *
    */
    int16_t getZRaw();

    float getX();
    float getY();
    float getZ();
    float getTemperature(); // TODO: Determine return type of temp sensor

    // I don't think these functions are necessary
    // void setMaxX(int16_t val){this->maxX = val;}
    // void setMaxY(int16_t val){this->maxY = val;}
    // void setMaxZ(int16_t val){this->maxZ = val;}

    int16_t getMaxX(){return this->maxX;}
    int16_t getMaxY(){return this->maxY;}
    int16_t getMaxZ(){return this->maxZ;}
    int16_t getMinX(){return this->minX;}
    int16_t getMinY(){return this->minY;}
    int16_t getMinZ(){return this->minZ;}

    private:

    /** 
     * @brief I2C address of the device
     */
    uint8_t address;

    int16_t maxX, maxY, maxZ;
    int16_t minX, minY, minZ;

    /** 
     * @brief Normalize result to value between -1 and 1
     */
    float normalize(int16_t val, int16_t maxVal, int16_t minVal);

    int16_t getReading(uint8_t msbReg, uint8_t lsbReg);
};

#endif