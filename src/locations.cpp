#include "locations.h"

Location closestLocation(float myX, float myY, Location* locations, int nLocations){
    int nearestIndex = 0;
    float minDistanceSq = MAXFLOAT;

    for (int i = 0; i < nLocations; i++){
        float dx = myX - locations[i].x;
        float dy = myY - locations[i].y;
        float distanceSq = dx * dx + dy * dy;
        if(distanceSq < minDistanceSq){
            minDistanceSq = distanceSq;
            nearestIndex = i;
        }
    }
    Location closest = {locations[nearestIndex].x, locations[nearestIndex].y};
    return closest;
}