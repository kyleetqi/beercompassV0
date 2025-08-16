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

// Multiply to convert radians to degrees
#ifndef RAD_TO_DEG
#define RAD_TO_DEG 57.29577951308232f // 180/PI
#endif

class QMC5883L{
    public:

    /**
     * @brief Class constructor.
     * 
     * @param myAddress The I2C address of the object.
     */
    QMC5883L(uint8_t myAddress);

    /**
     * @brief typedef defining the modes for the setMode function
     */
    enum Mode : uint8_t {
        MODE_SUSPEND = 0,
        MODE_NORMAL = 1,
        MODE_SINGLE = 2, 
        MODE_CONTINUOUS = 3
    };

    /**
     * @brief Sets the magnetometer's operating mode.
     * 
     * @param mode The desired mode.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setMode(Mode mode);

    /**
     * @brief Sets the magnetometer's data output frequency.
     * 
     * @param odr Output data rate in Hz. Valid values: 10, 50, 100, 200. Default value is 10.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setOutputRate(uint8_t odr = 10);

    /**
     * @brief Sets the magnetometer's over sample rate ratio
     * 
     * @param osr1 Over sample rate ratio. Valid values: 1, 2, 4, 8. Default value is 2.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setOverSampleRate(uint8_t osr1 = 2);
    
    /**
     * @brief Sets the magnetometer's down sample rate ratio.
     * 
     * @param osr2 Down sample rate ratio. Valid values: 1, 2, 4, 8. Default value is 4.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setDownSampleRate(uint8_t osr2 = 4);

    /**
     * @brief Sets the magnetometer's magnetic range.
     * 
     * @param rng Magnetic range in Gauss. Valid values: 2, 8, 12, 30. Default value is 2.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setRange(uint8_t range = 2);

    /**
     * @brief typedef defining the modes for the setResetMode function
     */
    enum SetResetMode : uint8_t {
        SET_RESET_ON = 0,
        SET_ON = 1,
        SET_RESET_OFF = 2,
    };

    /**
     * @brief Sets the magnetometer's set/reset mode.
     * 
     * @param mode The desired mode.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setSetResetMode(SetResetMode mode);

    /**
     * @brief Resets the magnetometer's registers to its default values.
     * 
     * @return true if the operation is successful, false otherwise.
     */
    bool resetRegisters();

    /** 
     * @brief Tells you if the magnetometer has data ready.
     * 
     * @return true if the magnetometer has new data ready, false otherwise.
     */
    bool isDRDY();

    /**
     * @brief Indicates if the reading exceeds -30,000 to 30,000 LSBs. Register resets when read.
     * 
     * @return true if an output exceeds the range, false otherwise.
     */
    bool isOVFL();

    /** 
     * @brief Determines and stores the maximum and minimum readings in the X, Y, and Z directions.
     * 
     * @param calibrationTime Duration of no-change before ending calibration in ms.
     */
    void calibrate(int calibrationTime);

    /**
     * @brief Manually set magnetometer's maximum/minimum readings for calibration.
     * 
     * @param xMax The maximum reading in the X direction.
     * @param yMax The maximum reading in the Y direction.
     * @param zMax The maximum reading in the Z direction.
     * @param xMin The minimum reading in the X direction.
     * @param yMin The minimum reading in the Y direction.
     * @param zMin The minimum reading in the Z direction.
     */
    void setCalibrationData(int16_t xMax, int16_t yMax, int16_t zMax, int16_t xMin, int16_t yMin, int16_t zMin);

    /** 
     * @brief Reads the magnetometer's X register.
     * 
     * @return The magnetometer's raw X axis reading.
     */
    int16_t readX();

    /** 
     * @brief Reads the magnetometer's Y register.
     * 
     * @return The magnetometer's raw Y axis reading.
     */
    int16_t readY();

    /**
    * @brief Reads the magnetometer's Z register.
    * 
    * @return The magnetometer's raw Z axis reading.
    */
    int16_t readZ();

    /**
     * @brief Reads the magnetometer's 3 axis.
     */
    void read();

    /**
     * @brief Obtains the most recent magnetometer raw x reading.
     * 
     * @return The most recent raw x reading.
     */
    int16_t getXRaw(){return this->xRaw;}

    /**
     * @brief Obtains the most recent magnetometer raw y reading.
     * 
     * @return The most recent raw y reading.
     */
    int16_t getYRaw(){return this->yRaw;}

    /**
     * @brief Obtains the most recent magnetometer raw z reading.
     * 
     * @return The most recent raw z reading.
     */
    int16_t getZRaw(){return this->zRaw;}

    /**
     * @brief Obtains the most recent magnetometer normalized x reading.
     * 
     * @return The most recent normalized x reading.
     */
    float getX(){return this->x;}

    /**
     * @brief Obtains the most recent magnetometer normalized y reading.
     * 
     * @return The most recent normalized y reading.
     */
    float getY(){return this->y;}

    /**
     * @brief Obtains the most recent magnetometer normalized z reading.
     * 
     * @return The most recent normalized z reading.
     */
    float getZ(){return this->z;}

    /**
     * @brief Obtains the most recent magnetometer x reading in Gauss.
     */
    float getXGauss(){return this->xGauss;}

    /**
     * @brief Obtains the most recent magnetometer y reading in Gauss.
     */
    float getYGauss(){return this->yGauss;}

    /**
     * @brief Obtains the most recent magnetometer z reading in Gauss.
     */
    float getZGauss(){return this->zGauss;}

    /**
     * @brief Calculates the azimuth/heading of the compass.
     * 
     * @param xNorm The normalized X reading of the magnetometer [-1,1].
     * @param yNorm The normalized Y reading of the magnetometer [-1,1].
     * @return The magnetometer azimuth/heading in degrees.
     */
    float azimuth(float xNorm, float yNorm);

    /**
     * @brief Obtain the magnetometer's maximum X axis reading.
     * 
     * @return The magnetometer's maximum X axis reading.
     */
    int16_t getXMax(){return this->xMax;}

    /**
     * @brief Obtain the magnetometer's maximum Y axis reading.
     * 
     * @return The magnetometer's maximum Y axis reading.
     */ 
    int16_t getYMax(){return this->yMax;}

    /**
     * @brief Obtain the magnetometer's maximum Z axis reading.
     * 
     * @return The magnetometer's maximum Z axis reading.
     */    
    int16_t getZMax(){return this->zMax;}

    /**
     * @brief Obtain the magnetometer's minimum X axis reading.
     * 
     * @return The magnetometer's minimum X axis reading.
     */
    int16_t getXMin(){return this->xMin;}

    /**
     * @brief Obtain the magnetometer's minimum Y axis reading.
     * 
     * @return The magnetometer's minimum Y axis reading.
     */
    int16_t getYMin(){return this->yMin;}

    /**
     * @brief Obtain the magnetometer's minimum Z axis reading.
     * 
     * @return The magnetometer's minimum Z axis reading.
     */
    int16_t getZMin(){return this->zMin;}

    private:

    /** 
     * @brief I2C address of the device.
     */
    uint8_t address;

    /**
     * @brief Maximum magnetometer reading in the indicated axis.
     */
    int16_t xMax, yMax, zMax;

     /**
     * @brief Minimum magnetometer reading in the indicated axis.
     */
    int16_t xMin, yMin, zMin;

    /**
     * @brief The most recent magnetometer reading in the indicated axis.
     */
    int16_t xRaw, yRaw, zRaw;

    /**
     * @brief The most recent magnetomer reading in the indicated axis, normalized to [-1, 1].
     */
    float x, y, z;

    /**
     * @brief The most recent magnetometer reading in the indicated axis in Gauss.
     */
    float xGauss, yGauss, zGauss;

    /**
     * @brief The LSB resolution of the magnetometer.
     */
    float lsbRes;

    /**
     * @brief Reads raw magnetometer data from a specified axis and updates internal state.
     * 
     * @param msbReg The register address containing the MSB axis information.
     * @param lsbReg The register address containing the LSB axis information.
     * @param rawStorage The variable where the raw reading should be stored.
     * @param normStorage the variable where the normalized reading should be stored.
     * @param maxVal The maximum value for this axis.
     * @param minVal The minimum value for this axis.
     * @return the raw reading from the registers.
     */
    int16_t readAxis(uint8_t msbReg, uint8_t lsbReg, int16_t& rawStorage, float& normStorage, float& gaussStorage, int16_t maxVal, int16_t minVal);

    /**
     * @brief Normalize magnetometer reading to a value between -1 and 1.
     * 
     * @param val The magnetometer reading to be normalized.
     * @param maxVal The maximum reading in the desired axis.
     * @param minVal The minimum reading in the desired axis.
     * @return The value normalized using the minimum and maximum values.
     */
    float normalize(int16_t val, int16_t maxVal, int16_t minVal);
};

#endif