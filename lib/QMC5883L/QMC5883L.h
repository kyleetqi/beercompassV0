#ifndef QMC5883L_H
#define QMC5883L_H

class QMC5883L {
    QMC5883L();
    void calibrate();
    void init();
    int getX();
    int getY();
    int getZ();
    float getXNormalized();
    float getYNormalized();
    float getZNormalized();
};

#endif