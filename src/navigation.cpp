#include "navigation.h"
#include "utils.h"

Location closestTarget(const Location myLocation, const Location locations[], int nLocations){
    int nearestIndex = 0;
    float minDistanceSq = MAXFLOAT;

    for (int i = 0; i < nLocations; i++){
        float dx = myLocation.lon - locations[i].lon;
        float dy = myLocation.lat - locations[i].lat;
        float distanceSq = dx * dx + dy * dy;
        if(distanceSq < minDistanceSq){
            minDistanceSq = distanceSq;
            nearestIndex = i;
        }
    }
    Location closest = {locations[nearestIndex].lon, locations[nearestIndex].lat};
    return closest;
}

float targetHeading(const float myHeading, const Location myLocation, const Location target){
    // Convert to radians
    float myLat = myLocation.lat * DEG_TO_RAD;
    float targetLat = target.lat * DEG_TO_RAD;
    float dLon = (target.lon - myLocation.lon) * DEG_TO_RAD;

    // Great circle formula
    float y = sinf(dLon) * cosf(targetLat);
    float x = cosf(myLat) * sinf(targetLat) - sinf(myLat) * cosf(targetLat) * cosf(dLon);
    float heading = atan2f(y, x);

    // Convert back to compass convention
    heading *= RAD_TO_DEG;
    if (heading < 0 ) {
        heading += 360.0f;
    }
    heading -= myHeading;
    if (heading < 0) {
        heading += 360.0f;
    }
    if (heading >= 360.0f) {
        heading -= 360.0f;
    }
    return heading;

    // Old implementation that assumes Earth curvature is negligible.
    // Keep just in case.
    // float dx = target.lon - myLocation.lon;
    // float dy = target.lat - myLocation.lat;
    // float heading = atan2f(dy, dx) * RAD_TO_DEG - myHeading;
    // if (heading < 0){
    //     heading += 360.0f;
    // }
    // if (heading >= 360.0f){
    //     heading -= 360.0f;
    // }
    // return heading;
}

float targetDistance(const Location myLocation, const Location target){
    float myLat = myLocation.lat * DEG_TO_RAD;
    float targetLat = target.lat * DEG_TO_RAD;
    float dLat = targetLat - myLat;
    float dLon = (target.lon - myLocation.lon) * DEG_TO_RAD;

    float a = sinf(dLat/2) * sinf(dLat/2) + cosf(myLat) * cosf(targetLat) *
              sinf(dLon/2) * sinf(dLon/2);
    
    float c = 2.0f * atan2f(sqrtf(a), sqrtf(1.0f - a));
    return c * EARTH_RADIUS; // Convert to metres
}
