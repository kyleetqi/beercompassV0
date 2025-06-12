#ifndef QMC5883L_H
#define QMC5883L_H

class qmc5883l {
    public:

    /**
     * 
     */
    qmc5883l();

    /**
     * 
     * @param calibrationTime calibration is complete when no new values for this amount of time
     * 
     */
    void calibrate(int calibrationTime);

    /**
     * 
     */
    void init();

    /**
     * 
     */
    int getX();

    /**
     * 
     */
    int getY();
    int getZ();
    float getXNormalized();
    float getYNormalized();
    float getZNormalized();
    float temperature(); // TODO: Determine return type of temp sensor

    private:
    int getReading();
    float normalize(float val);
};

#endif