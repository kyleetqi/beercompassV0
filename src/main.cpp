// Include required libraries
#include <Arduino.h>
#include <utils.h>
#include <qmc5883l.h>

// Declare OLED parameters
#define OLED_ADDRESS 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1


void setup() {
  Serial.begin(1000000); // TODO: Determine serial rate
  // compass.init(); // TODO: Declare compass object and initialize

}

void loop() {
  
}
