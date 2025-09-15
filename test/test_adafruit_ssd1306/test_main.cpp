// Include required libraries
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "i2c_handler.h"
#include "utils.h"
#include "display.h"

// OLED global declarations
#define SSD1306_ADDR 0x3c // I2C address of OLED
#define SSD1306_SCREEN_WIDTH 128 // Screen width
#define SSD1306_SCREEN_HEIGHT 64 // Screen height
#define SSD1306_RESET -1 // OLED reset macro

// Create SSD1306 object
Adafruit_SSD1306 ssd1306(SSD1306_SCREEN_WIDTH, SSD1306_SCREEN_HEIGHT, &Wire, SSD1306_RESET);

// I2C global declarations
#define SDA_PIN 21 // I2C SDA pin
#define SCL_PIN 22 // I2C SCL pin
#define I2C_FREQ 100000 // I2C clock speed, standard mode (HZ)

// Keep track of setup errors
bool setupSuccess = true;

// Display test angle and distance
int angle = 0;
int distance = 0;

void setup() {
  // Initialize Serial
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C
  if(!i2cInit(SDA_PIN, SCL_PIN, I2C_FREQ)){
    Serial.println("I2C failed to initialize!");
    setupSuccess = false;
  }

  // Initialize ssd1306
  if(!ssd1306.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDR)){
    Serial.println("SSD1306 failed to initialize!");
    setupSuccess = false;
  }

  // Scan for I2C devices (if necessary)
  i2cScan();
}

void loop() {
  // Setup fail condition
  if(!setupSuccess){
    Serial.println("Setup failed!");
    while(true){}
  }

  // Display on OLED
  updateCompass(0, angle, distance, ssd1306);
  angle++;
  distance++;
  delay(50);
}