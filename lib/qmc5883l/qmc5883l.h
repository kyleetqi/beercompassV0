#ifndef QMC5883L_H
#define QMC5883L_H

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

class QMC5883L{
    public:

    /**
     * @brief Class constructor.
     * @param myAddress The I2C address of the object.
     */
    QMC5883L(uint8_t myAddress);

    /**
     * @brief Suspend the magnetometer.
     * @return true if the operation succeeded, false otherwise.
     */
    bool suspend();

    /**
     * @brief Set the magnetometer to normal mode.
     * @return true if the operation succeeded, false otherwise.
     */
    bool setModeNormal();

    /**
     * @brief Set the magnetometer to single mode.
     * @return true if the operation succeeded, false otherwise.
     */
    bool setModeSingle();

    /**
     * @brief Set the magnetometer to continuous mode.
     * @return true if the operation succeeded, false otherwise.
     */
    bool setModeContinuous();

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
    
    /**
     * @brief Sets the magnetometer's magnetic range.
     * @param rng Magnetic range in Gauss. Valid values: 2, 8, 12, 30. Default value is 2.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setRange(uint8_t rng = 2);

    /**
     * @brief Sets the magnetometer's set/reset mode to set and reset on.
     * @return true if the configuration is successful, false otherwise.
     */
    bool modeSetResetOn();

    /**
     * @brief Sets the magnetometer's set/reset mode to set on only.
     * @return true if the configuration is successful, false otherwise.
     */
    bool modeSetOn();

    /**
     * @brief Sets the magnetometer's set/reset mode to set and reset off.
     * @return true if the configuration is successful, false otherwise.
     */
    bool modeSetResetOff();

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

    /**
     * @brief Indicates if the reading exceeds -30,000 to 30,000 LSBs. Register resets when read.
     * @return true if an output exceeds the range, false otherwise.
     */
    bool isOVFL();

    /** 
     * @brief Determines and stores the maximum and minimum readings in the X, Y, and Z directions.
     * @param calibrationTime TBD.
     */
    void calibrate(int calibrationTime);

    /** 
     * @brief Reads the magnetometer's raw reading in the X axis.
     * @return The magnetometer's raw X axis reading.
     */
    int16_t getXRaw();

    /** 
     * @brief Reads the magnetometer's raw Y axis reading.
     * @return The magnetometer's raw Y axis reading.
     */
    int16_t getYRaw();

    /**
    * @brief Reads the magnetometer's raw Z axis reading.
    * @return The magnetometer's raw Y axis reading.
    */
    int16_t getZRaw();

    /**
     * @brief Calculates the magnetometer's X axis reading normalized using its max/min values.
     * @return The magnetometer's normalized X axis reading.
     */
    float getX();

    /**
     * @brief Calculates the magnetometer's Y axis reading normalized using its max/min values.
     * @return The magnetometer's normalized Y axis reading.
     */
    float getY();

    /**
     * @brief Calculates the magnetometer's Y axis reading normalized using its max/min values.
     * @return The magnetometer's normalized Y axis reading.
     */
    float getZ();

    // TODO: Implement this function
    // Idk if the QMC5883L actually has a temp sensor.
    float getTemperature();

    /**
     * @brief Manually set the maximum X reading.
     */
    void setMaxX(int16_t val){this->maxX = val;}

    /**
     * @brief Manually set the maximum Y reading.
     */
    void setMaxY(int16_t val){this->maxY = val;}

    /**
     * @brief Manually set the maximum Z reading.
     */
    void setMaxZ(int16_t val){this->maxZ = val;}

    /**
     * @brief Manually set the minimum X reading.
     */
    void setMinX(int16_t val){this->minX = val;}

    /**
     * @brief Manually set the minimum Y reading.
     */
    void setMinY(int16_t val){this->minY = val;}

    /**
     * @brief Manually set the minimum Z reading.
     */
    void setMinZ(int16_t val){this->minZ = val;}

    /**
     * @brief Obtain the magnetometer's maximum X axis reading.
     * @return The magnetometer's maximum X axis reading.
     */
    int16_t getMaxX(){return this->maxX;}

    /**
     * @brief Obtain the magnetometer's maximum Y axis reading.
     * @return The magnetometer's maximum Y axis reading.
     */ 
    int16_t getMaxY(){return this->maxY;}

    /**
     * @brief Obtain the magnetometer's maximum Z axis reading.
     * @return The magnetometer's maximum Z axis reading.
     */    
    int16_t getMaxZ(){return this->maxZ;}

    /**
     * @brief Obtain the magnetometer's minimum X axis reading.
     * @return The magnetometer's minimum X axis reading.
     */
    int16_t getMinX(){return this->minX;}

    /**
     * @brief Obtain the magnetometer's minimum Y axis reading.
     * @return The magnetometer's minimum Y axis reading.
     */
    int16_t getMinY(){return this->minY;}

    /**
     * @brief Obtain the magnetometer's minimum Z axis reading.
     * @return The magnetometer's minimum Z axis reading.
     */
    int16_t getMinZ(){return this->minZ;}

    private:

    /** 
     * @brief I2C address of the device.
     */
    uint8_t address;

    /**
     * @brief Maximum magnetometer reading in the indicated axis.
     */
    int16_t maxX, maxY, maxZ;

     /**
     * @brief Minimum magnetometer reading in the indicated axis.
     */
    int16_t minX, minY, minZ;

     /** 
     * @brief Sets the magnetometer's data output mode.
     * @param bits Bits corresponding to the desired mode.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setMode(uint8_t bits);

    /**
     * @brief Sets the magnetometer's set/reset mode.
     * @param bits Bits corresponding to the desired mode.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setSetResetMode(uint8_t bits);

    /** 
     * @brief Normalize magnetometer reading to a value between -1 and 1.
     * @param val The magnetometer reading to be normalized.
     * @param maxVal The maximum reading in the desired axis.
     * @param minVal The minimum reading in the desired axis.
     * @return The value normalized using the minimum and maximum values.
     */
    float normalize(int16_t val, int16_t maxVal, int16_t minVal);

    /**
     * @brief Obtains the magnetometer reading for a desired axis.
     * @param msbReg The Most Significant Bit register of the axis.
     * @param lsbReg The Least Significant Bit register of the axis.
     * @return The reading of the axis register.
     */
    int16_t getReading(uint8_t msbReg, uint8_t lsbReg);
};

#endif