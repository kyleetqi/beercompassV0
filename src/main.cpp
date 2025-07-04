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
#define QMC5883L_ADDR 0x2C // I2C address of QMC5883L
#define CALIBRATION_TIME 5000 

// Create magnetometer object
QMC5883L myCompass(QMC5883L_ADDR);

// Keeps track of setup errors
bool setupSuccessful = true;

void setup() {
  Serial.begin(115200); // Initialize serial
  delay(1000); // Wait for serial to get ready

  // Initialize I2C bus
  if(!i2cInit(SDA_PIN, SCL_PIN, I2C_FREQ)){
    Serial.println("I2C failed to initialize!");
    Serial.println("Program terminating.");
    setupSuccessful = false;
  }

  i2cScan();   // Debug purposes: scan for I2C devices

  // Configure magnetometer settings
  setupSuccessful &= myCompass.resetRegisters();
  setupSuccessful &= myCompass.setMode(QMC5883L::Mode::Continuous);
  setupSuccessful &= myCompass.setOutputRate(100);
  setupSuccessful &= myCompass.setOverSampleRate(2);
  setupSuccessful &= myCompass.setDownSampleRate(4);
  // TODO: Create this function below in qmc5883l.cpp
  // setupSuccessful &= bool setSetResetMode(uint8_t mode = 0b01);
  setupSuccessful &= myCompass.setRange(2);

  myCompass.calibrate(CALIBRATION_TIME);

  // TODO: Maybe add this to the calibrate function
  // Serial.print("X min val: ");
  // Serial.print(myCompass.getMinX());
  // Serial.print(" ");
  // Serial.print("X max val: ");
  // Serial.println(myCompass.getMaxX());

  // Serial.print("Y min val: ");
  // Serial.print(myCompass.getMinY());
  // Serial.print(" ");
  // Serial.print("Y max val: ");
  // Serial.println(myCompass.getMaxY());

  // Serial.print("Z min val: ");
  // Serial.print(myCompass.getMinZ());
  // Serial.print(" ");
  // Serial.print("Z max val: ");
  // Serial.println(myCompass.getMaxZ());


}

void loop() {
  // Setup fail condition
  if(!setupSuccessful){
    Serial.println("Setup failed!");
    while(true){}
  }

  // // // Testing to see if this actually works
  // if(myCompass.isDRDY() == 1){
  //   Serial.println(myCompass.getXRaw());
  // } else {
  //   Serial.println("Data is not ready!");
  // }

  // delay(100);
}
