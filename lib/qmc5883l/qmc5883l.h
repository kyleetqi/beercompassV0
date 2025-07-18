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
#define RAD_TO_DEG 57.29577951308232 // 180/PI

class QMC5883L{
    public:

    /**
     * @brief Class constructor.
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
     * @param mode The desired mode.
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

    /**
     * @brief Sets the magnetometer's magnetic range.
     * @param rng Magnetic range in Gauss. Valid values: 2, 8, 12, 30. Default value is 2.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setRange(uint8_t rng = 2);

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
     * @param mode The desired mode.
     * @return true if the configuration is successful, false otherwise.
     */
    bool setSetResetMode(SetResetMode mode);

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
     * @brief Manually set magnetometer's maximum/minimum readings for calibration.
     * @param maxX The maximum reading in the X direction.
     * @param maxY The maximum reading in the Y direction.
     * @param maxZ The maximum reading in the Z direction.
     * @param minX The minimum reading in the X direction.
     * @param minY The minimum reading in the Y direction.
     * @param minZ The minimum reading in the Z direction.
     */
    void setCalibrationData(int16_t maxX, int16_t maxY, int16_t maxZ, int16_t minX, int16_t minY, int16_t minZ);

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

    /**
     * @brief Calculates the azimuth/heading of the compass.
     * @param normX The normalized X reading of the magnetometer [-1,1].
     * @param normY The normalized Y reading of the magnetometer [-1,1].
     * @return The magnetometer azimuth/heading in degrees.
     */
    float azimuth(int16_t normX, int16_t normY);

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
     * @brief Normalize magnetometer reading to a value between -1 and 1.
     * @param val The magnetometer reading to be normalized.
     * @param maxVal The maximum reading in the desired axis.
     * @param minVal The minimum reading in the desired axis.
     * @return The value normalized using the minimum and maximum values.
     */
    float normalize(int16_t val, int16_t maxVal, int16_t minVal);
};

#endif