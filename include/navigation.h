#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>

#ifndef DEG_TO_RAD
#define DEG_TO_RAD 0.017453292519943295769236907684886
#endif

#ifndef EARTH_RADIUS
#define EARTH_RADIUS 6371000
#endif

/**
 * @brief
 */
struct Location {
    float lat;
    float lon;
};

/**
 * @brief
 */
const Location LOCATIONS[] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};

/**
 * @brief
 */
const int nLocations = sizeof(LOCATIONS)/sizeof(LOCATIONS[0]);

/**
 * @brief
 * 
 * @param
 * @param
 * @param
 */
Location closestTarget(const Location myLocation, const Location locations[], int nLocations);

/**
 * @brief
 * 
 * @param
 * @param
 * @param
 */
float targetHeading(const float heading, const Location myLocation, const Location target);

float targetDistance(const Location myLocation, const Location target);

#endif