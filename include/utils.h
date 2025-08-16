#ifndef UTILS_H
#define UTILS_H

#ifndef RAD_TO_DEG
#define RAD_TO_DEG 57.29577951308232f // 180/PI
#endif

/**
 * @brief Initializes the display
 */
void initDisplay();

/**
 * @brief Initializes the magnetometer
 */
void initMagnetometer();

/**
 * @brief Initializes the accelerometer
 */
void initAcclerometer();

struct Vec3{
  float x, y, z;
};

#endif