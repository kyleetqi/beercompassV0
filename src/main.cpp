// Include required libraries
#include <Arduino.h>
#include "i2c_handler.h"
#include "serial_handler.h"
#include "utils.h"
#include "qmc5883l.h"
#include "mpu6500.h"
#include "neo_6m.h"

// X min val: -16980 X max val: 12781
// Y min val: -13560 Y max val: 13128
// Z min val: -10305 Z max val: 6740

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
#define QMC5883L_ADDR 0x2C // I2C address of QMC5883L
#define CALIBRATION_TIME 5000 

// Create magnetometer object
QMC5883L myCompass(QMC5883L_ADDR);

// Keeps track of setup errors
bool setupSuccessful = true;

void setup() {
  // Initialize Serial and wait for it to get ready
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C bus
  if(!i2cInit(SDA_PIN, SCL_PIN, I2C_FREQ)){
    Serial.println("I2C failed to initialize!");
    setupSuccessful = false;
  }

  // Debug purposes: scan for I2C devices
  // i2cScan();

  // Configure magnetometer settings
  setupSuccessful &= myCompass.resetRegisters();
  setupSuccessful &= myCompass.setModeContinuous();
  setupSuccessful &= myCompass.setOutputRate(100);
  setupSuccessful &= myCompass.setOverSampleRate(2);
  setupSuccessful &= myCompass.setDownSampleRate(4);
  setupSuccessful &= myCompass.modeSetOn();
  setupSuccessful &= myCompass.setRange(2);
  if(!setupSuccessful){
    Serial.println("Compass configuration failed!");
  }
  if(setupSuccessful){
    myCompass.calibrate(CALIBRATION_TIME);
  }

  // // For debugging purposes, manually set calibration values
  // myCompass.setMaxX(12781);
  // myCompass.setMaxY(13128);
  // myCompass.setMaxZ(6740);
  // myCompass.setMinX(-16980);
  // myCompass.setMinY(-13560);
  // myCompass.setMinZ(-10305); 
}

void loop() {
  // Setup fail condition
  if(!setupSuccessful){
    Serial.println("Setup failed!");
    while(true){}
  }

  // // // Testing to see if this actually works
  if(myCompass.isDRDY() == 1){
    // Serial.println("Start reading");

    // Serial.print("X value: ");
    // Serial.print(myCompass.getX());
    // Serial.print(" Y value: ");
    // Serial.print(myCompass.getY());
    // Serial.print(" Z value: ");
    // Serial.println(myCompass.getZ());

    Serial.print("X raw: ");
    Serial.print(myCompass.getXRaw());
    Serial.print(" Y raw: ");
    Serial.print(myCompass.getYRaw());
    Serial.print(" Z raw: ");
    Serial.println(myCompass.getZRaw());

    // Serial.println("End reading");
  } else {
    Serial.println("Data is not ready!");
  }

  delay(300);
}
