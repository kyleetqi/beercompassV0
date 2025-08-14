#include "imu.h"

float pitch_accel(float ax, float ay, float az){
    return atan2(-ax, sqrt(ay * ay + az * az));
}

float roll_accel(float ay, float az){
    return atan2(ay, az);
}

float yaw_accel_mag(float ax, float ay, float az, float mx, float my, float mz){
    float pitch = pitch_accel(ax, ay, az);
    float roll = roll_accel(ay, az);
    float mxh = mx * cos(pitch) + mz * sin(pitch);
    float myh = mx * sin(roll) * sin(pitch) + my * cos(roll) - mz * sin(roll) * cos(pitch);
    return atan2(-myh, mxh);
}

float true_azimuth(float yaw){
    yaw *= RAD_TO_DEG;
    if(yaw < 0){
        yaw += 360.0f;
    }
    return yaw;
}

float true_azimuth(float ax, float ay, float az, float mx, float my, float mz){
    float yaw = yaw_accel_mag(ax, ay, az, mx, my, mz);
    return true_azimuth(yaw);
}