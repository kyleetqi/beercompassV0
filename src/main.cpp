// Include required libraries
#include <Arduino.h>
#include "i2c_handler.h"
#include "utils.h"
#include "qmc5883l.h"
#include "mpu6500.h"
#include "neo_6m.h"

// OLED global declarations
#define OLED_ADDR 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// I2C global declarations
#define SDA_PIN 21 // I2C SDA pin
#define SCL_PIN 22 // I2C SCL pin
#define I2C_FREQ 100000 // I2C clock speed, standard mode (HZ)

// Magnetometer global declarations
#define QMC5883L_ADDR 0x2C // I2C address of qmc5883l
#define QMC5883L_MODE 0b11 // Continuous read mode
#define QMC5883L_ODR 0b10 // 100 Hz output rate
#define QMC5883L_OSR1 0b10 // 2x oversampling ratio
#define QMC5883L_OSR2 0b10 // 4x downsampling rate
// ^tbh all these declarations might not be necessary but we'll see ig

// Create magnetometer object
qmc5883l myCompass = qmc5883l(QMC5883L_ADDR);

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
  Serial.println(i2cRead(QMC5883L_ADDR, 0x00), HEX);

}

void loop() {
  // Prevents program from running if setup fails
  if(!setupSuccessful){
    while(true){}
  }

  // // Testing to see if this actually works
  if(myCompass.isDRDY() == 1){
    Serial.println(myCompass.getX(), HEX);
  } else {
    Serial.println("Data is not ready!");
  }

  delay(500);
}
