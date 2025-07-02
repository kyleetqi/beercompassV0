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

    /**
     * @brief Class constructor.
     * @param myAddr The I2C address of the object.
     */
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
     * @brief Sets the magnetometer's over sample rate ratio
     * @param osr1 Over sample rate ratio. Valid values: 1, 2, 4, 8. Default value is 2.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setOverSampleRate(uint8_t osr1 = 2);
    
    /**
     * @brief Sets the magnetometer's down sample rate ratio.
     * @param osr2 Down sample rate ratio. Valid values: 1, 2, 4, 8. Default value is 4.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setDownSampleRate(uint8_t osr2 = 4);

    // TODO: This lol
    // Make sure the default value makes sense
    bool setSetResetMode(uint8_t mode = 0b01);

    /**
     * @brief Sets the magnetometer's magnetic range.
     * @param rng Magnetic range in Gauss. Valid values: 2, 8, 12, 30. Default value is 2.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setRange(uint8_t rng = 2);

    /**
     * @brief Resets the magnetometer's registers to its default values.
     * @return true if the operation is successful, false otherwise.
     */
    bool resetRegisters();

    /** 
     * @brief Tells you if the magnetometer has data ready.
     * @return true if the magnetometer has new data ready, false otherwise.
     */
    bool isDRDY();

    // TODO: Create Doxygen
    bool isOVFL();

    /** 
     * @brief Determines and stores the maximum and minimum readings in the X, Y, and Z directions.
     * @param calibrationTime TBD.
     */
    void calibrate(int calibrationTime);

    /** 
     * @brief Obtains the magnetometer's raw reading in the X axis.
     * @return The magnetometer's raw reading in the X axis.
     */
    int16_t getXRaw();

    /** 
     * @brief Obtains the magnetometer's raw reading in the Y axis.
     * @return The magnetometer's raw reading in the Y axis.
     */
    int16_t getYRaw();

    /**
    * @brief Obtains the magnetometer's raw reading in the Z axis.
    * @return The magnetometer's raw reading in the Z axis.
    */
    int16_t getZRaw();

    float getX();
    float getY();
    float getZ();

    // TODO: Determine return type of temp sensor.
    // Also idk if the qmc5883l actually has a temp sensor.
    float getTemperature();

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