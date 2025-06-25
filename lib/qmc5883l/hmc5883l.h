#ifndef QMC5883L_H
#define QMC5883L_H

class qmc5883l {
    public:

    /**
     * 
     */
    qmc5883l();


    /** @brief Struct that stores the maximum X, Y, and Z readings
     * 
     */
    struct CalibrationData {
        int maxX;
        int maxY;
        int maxZ;
    };

    /** @brief Calculates the maximum readings in the X, Y, and Z axis
     * @param calibrationTime calibration is complete when no new values for this amount of time
     * 
     */
    CalibrationData calibrate(int calibrationTime);

    /** 
     * 
     */
    bool init();

    /** @brief Obtains the magnetometer's reading in the X axis
     * 
     */
    int getX();

    /** @brief Obtains the magnetometer's reading in the Y axis
     * 
     */
    int getY();

    /* @brief Obtains the magnetometer's reading in the Z axis
    *
    */
    int getZ();
    float getXNormalized();
    float getYNormalized();
    float getZNormalized();
    float getTemperature(); // TODO: Determine return type of temp sensor

    private:
    int getReading();
    float normalize(float val);
};

#endif