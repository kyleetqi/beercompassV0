#include "display.h"
#include <Adafruit_GFX.h>

void updateCompass(float azimuth, float target, Adafruit_SSD1306 &display){
    display.clearDisplay();
    int cx = display.width()/2;
    int cy = display.height()/2;
    int r = 20; // Length of compass needle

    // Converts degrees to radians
    float theta = radians(target-azimuth);
    int x1 = cx + r*cosf(theta);
    int y1 = cy - r*sinf(theta); // Minus because increments downwards

    display.drawCircle(cx, cy, r, SSD1306_WHITE);
    display.drawLine(cx, cy, x1, y1, SSD1306_WHITE);
    display.display();
}