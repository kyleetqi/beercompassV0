#include "display.h"
#include <Adafruit_GFX.h>
#include <math.h>

void drawNeedle(float azimuth, float target, Adafruit_SSD1306 &display){
    int cx = display.width()/2; // X center
    int cy = display.height()/2; // Y center
    int r = 20; // Length of compass needle

    // Converts degrees to radians
    float theta = radians(target-azimuth);
    int x1 = cx + r*cosf(theta);
    int y1 = cy - r*sinf(theta); // Minus because y increments downwards

    display.drawCircle(cx, cy, r, SSD1306_WHITE);
    display.drawLine(cx, cy, x1, y1, SSD1306_WHITE);
}

void drawDistance(float distance, Adafruit_SSD1306 &display){
    int cx = display.width()/2;
    int cy = display.height()/2;
    int r = 20;

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setTextWrap(false);

    int roundedDist = (int)round(distance);
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d m", roundedDist);

    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(buffer, 0, 0, &x, &y, &w, &h);

    int textX = cx-(w/2);
    int textY = cy + r + 4;

    display.setCursor(textX, textY);
    display.print(buffer);
}

void updateCompass(float azimuth, float target, float distance, Adafruit_SSD1306 &display){
    display.clearDisplay();
    
    drawNeedle(azimuth, target, display);
    drawDistance(distance, display);

    display.display();
}