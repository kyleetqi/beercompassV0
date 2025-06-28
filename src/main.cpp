// Include required libraries
#include <Arduino.h>
#include "i2c_handler.h"
#include "utils.h"
#include "qmc5883l.h"
#include "mpu6500.h"
#include "neo_6m.h"

// // Declare OLED parameters
// #define OLED_ADDRESS 0x3c
// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// #define OLED_RESET -1

// Global variables
#define LED_PIN 2 // Devboard LED
#define SDA_PIN 21 // I2C SDA pin
#define SCL_PIN 22 // I2C SCL pin
#define I2C_FREQ 100000 // I2C clock speed, standard mode (HZ)

// Keeps track of setup errors
bool setupSuccessful = true;

void setup() {
  Serial.begin(115200);
  delay(1000); // Wait for serial to get ready

  // Initialize I2C bus
  if(!i2cInit(SDA_PIN, SCL_PIN, I2C_FREQ)){
    Serial.println("I2C failed to initialize!");
    Serial.println("Program terminating.");
    setupSuccessful = false;
  }

  // Debug purposes: scan for I2C devices
  i2cScan();

  // Reading from register 00 of magnetometer
  // Should output 80 in hex
  Serial.println(i2cRead(0x2C, 0x00), HEX);

}

void loop() {
  // Prevents program from running if setup fails
  if(!setupSuccessful){
    while(true){}
  }
}
