#include "navigation.h"
#include "utils.h"

Location closestTarget(const Location myLocation, const Location locations[], int nLocations){
    int nearestIndex = 0;
    float minDistanceSq = MAXFLOAT;

    for (int i = 0; i < nLocations; i++){
        float dx = myLocation.x - locations[i].x;
        float dy = myLocation.y - locations[i].y;
        float distanceSq = dx * dx + dy * dy;
        if(distanceSq < minDistanceSq){
            minDistanceSq = distanceSq;
            nearestIndex = i;
        }
    }
    Location closest = {locations[nearestIndex].x, locations[nearestIndex].y};
    return closest;
}

float targetHeading(const float myHeading, const Location myLocation, const Location target){
    float dx = target.x - myLocation.x;
    float dy = target.y - myLocation.y;
    float heading = atan2f(dy, dx) * RAD_TO_DEG - myHeading;
    if (heading < 0){
        heading += 360.0f;
    }
    if (heading >= 360.0f){
        heading -= 360.0f;
    }
    return heading;
}
