#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <Arduino.h>

struct Location {
    float x; // Latitude
    float y; // Longitude
};

// TODO: Get location of every LCBO
const Location LOCATIONS[] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};

// Size of locations array
const int nLocations = sizeof(LOCATIONS)/sizeof(LOCATIONS[0]);

Location closestLocation(float myX, float myY, Location* locations, int nLocations);

#endif