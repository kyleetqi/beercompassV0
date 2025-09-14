#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

/**
 * @brief Draws a compass needle pointing towards a target heading
 * @param azimuth The user's current heading in degrees, using standard compass convention.
 * @param target The azimuth of the target in degrees, using standard compass convention.
 * @param display Reference to the Adafruit_SSD1306 display object to draw on.
 */
void updateCompass(float azimuth, float target, Adafruit_SSD1306 &display);

#endif