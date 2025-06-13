#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Returns compass heading, compansating for tilt
 * 
 * @param azimuth The current compass azimuth
 * 
 * @return
 */
float trueHeading();

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

/**
 * 
 */
struct closestLocation {
    float Xcoord;
    float Ycoord;
};

/**
 * @brief Determines closest coordinates from dataset given current location
 */
closestLocation calcClosestLocation(float myX, float myY);

#endif