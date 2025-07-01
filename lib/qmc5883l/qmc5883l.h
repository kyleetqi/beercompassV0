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

    struct CalibrationData {
        int maxX;
        int maxY;
        int maxZ;
    };

    enum class Mode : uint8_t {
        Suspend = 0b00,
        Normal = 0b01,
        Single = 0b10,
        Continuous = 0b11,
    };

    /** @brief Sets the magnetometer's data output mode
     *  @param mode The desired mode
     *  @return Returns true if mode was set successfully
     */
    bool setMode(Mode mode); // TODO: make sure suspend is called between mode changes

    bool setOutputRate(uint8_t odr = 100);
    bool setOverSampleRate(uint8_t osr1 = 2);
    bool setDownSampleRate(uint8_t osr2 = 4);

    bool setSetResetMode(uint8_t mode = 0b01);
    bool setRange(uint8_t rng = 0b11);
    bool resetRegisters();

    /** @brief Tells you if the magnetometer has data ready
     *  @return The status of the magnetometer
     */
    bool isDRDY();

    bool isOVFL();

    /** @brief Calculates the maximum readings in the X, Y, and Z axis
     * @param calibrationTime calibration is complete when no new values for this amount of time
     * 
     */
    CalibrationData calibrate(int calibrationTime);

    /** @brief Obtains the magnetometer's reading in the X axis
     * 
     */
    uint16_t getX();

    /** @brief Obtains the magnetometer's reading in the Y axis
     * 
     */
    uint16_t getY();

    /* @brief Obtains the magnetometer's reading in the Z axis
    *
    */
    uint16_t getZ();

    float getXNormalized();
    float getYNormalized();
    float getZNormalized();
    float getTemperature(); // TODO: Determine return type of temp sensor

    private:

    /** 
     * @brief I2C address of the device
     */
    uint8_t address;

    /** 
     * @brief Normalize result to value between -1 and 1
     */
    float normalize(float val);
};

#endif