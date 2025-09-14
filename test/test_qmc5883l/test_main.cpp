// Include required libraries
#include <Arduino.h>
#include "i2c_handler.h"
#include "utils.h"
#include "qmc5883l.h"

// I2C global declarations
#define SDA_PIN 21 // I2C SDA pin
#define SCL_PIN 22 // I2C SCL pin
#define I2C_FREQ 100000 // I2C clock speed, standard mode (HZ)

// QMC5883L global declarations
#define QMC5883L_ADDR 0x2C // I2C address of QMC5883L
#define QMC5883L_CALIBRATION_TIME 5000 
#define QMC5883L_OUTPUT_RATE 10 // Data output in Hz
#define QMC5883L_OVERSAMPLE_RATE 2 // Oversample rate
#define QMC5883L_DOWNSAMPLE_RATE 4 // Downsample rate
#define QMC5883L_RANGE 2 // +/- range in Gauss

// Create QMC5883L object
QMC5883L qmc5883l(QMC5883L_ADDR);

// Struct for storing sensor information
Vec3 mag;

// Keep track of setup errors
bool setupSuccess = true;
bool qmc5883lSuccess = true;

void setup() {
  // Initialize Serial
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C
  if(!i2cInit(SDA_PIN, SCL_PIN, I2C_FREQ)){
    Serial.println("I2C failed to initialize!");
    setupSuccess = false;
  }

  // Scan for I2C devices (if necessary)
  i2cScan();

  // Configure qmc5883l settings
  qmc5883lSuccess &= qmc5883l.resetRegisters();
  qmc5883lSuccess &= qmc5883l.setMode(QMC5883L::MODE_NORMAL);
  qmc5883lSuccess &= qmc5883l.setOutputRate(QMC5883L_OUTPUT_RATE);
  qmc5883lSuccess &= qmc5883l.setOverSampleRate(QMC5883L_OVERSAMPLE_RATE);
  qmc5883lSuccess &= qmc5883l.setDownSampleRate(QMC5883L_DOWNSAMPLE_RATE);
  qmc5883lSuccess &= qmc5883l.setSetResetMode(QMC5883L::SET_ON);
  qmc5883lSuccess &= qmc5883l.setRange(QMC5883L_RANGE);
  setupSuccess &= qmc5883lSuccess;
  if(!qmc5883lSuccess){
    Serial.println("QMC5883L failed to initialize!");
  }

  // Calibrate qmc5883l
  // Comment out if calibration isn't necessary
  if(qmc5883lSuccess){
    // qmc5883l.calibrate(QMC5883L_CALIBRATION_TIME);
  }
}

void loop() {
  // Setup fail condition
  if(!setupSuccess){
    Serial.println("Setup failed!");
    while(true){}
  }

  // Get magnetometer readings
  if(qmc5883l.isDRDY() == 1){
    qmc5883l.read();
    mag.x = qmc5883l.getXRaw();
    mag.y = qmc5883l.getYRaw();
    mag.z = qmc5883l.getZRaw();
  } else {
    Serial.println("Data not ready!");
  }

  // Print magnetometer readings
  Serial.print("X mag: ");
  Serial.print(mag.x);
  Serial.print(" Y mag: ");
  Serial.print(mag.y);
  Serial.print(" Z mag: ");
  Serial.println(mag.z);
  // Serial.print(" Azimuth: ");
  // Serial.println(qmc5883l.azimuth(mag.x, mag.y));

  delay(1000);
}