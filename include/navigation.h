#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>

/**
 * @brief
 */
struct Location {
    float x; // Latitude
    float y; // Longitude
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

#endif