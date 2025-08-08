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
#define QMC5883L_CALIBRATION_TIME 5000 
#define QMC5883L_OUTPUT_RATE 10 // Data output in Hz
#define QMC5883L_OVERSAMPLE_RATE 2 // Oversample rate
#define QMC5883L_DOWNSAMPLE_RATE 4 // Downsample rate
#define QMC5883L_RANGE // +/- range in Gauss

// Create magnetometer object
QMC5883L qmc5883l(QMC5883L_ADDR);

// Accel/Gyro global declarations
#define MPU6500_ADDR 0x68
#define MPU6500_SAMPLE_RATE_DIVIDER 1000 // TODO: Choose value
#define MPU6500_GYRO_BANDWIDTH 250 // TODO: Determine value

// Create MPU6500 object
MPU6500 mpu6500(MPU6500_ADDR);

// Keeps track of setup errors
bool setupSuccess = true;

void setup() {
  // Initialize Serial and wait for it to get ready
  Serial.begin(115200);
  delay(1000);

  // Initialize I2C bus
  if(!i2cInit(SDA_PIN, SCL_PIN, I2C_FREQ)){
    Serial.println("I2C failed to initialize!");
    setupSuccess = false;
  }

  // Scan for I2C devices (if necessary)
  // i2cScan();

  // Configure magnetometer settings
  setupSuccess &= qmc5883l.resetRegisters();
  setupSuccess &= qmc5883l.setMode(QMC5883L::MODE_CONTINUOUS);
  setupSuccess &= qmc5883l.setOutputRate(QMC5883L_OUTPUT_RATE);
  setupSuccess &= qmc5883l.setOverSampleRate(QMC5883L_OVERSAMPLE_RATE);
  setupSuccess &= qmc5883l.setDownSampleRate(QMC5883L_DOWNSAMPLE_RATE);
  setupSuccess &= qmc5883l.setSetResetMode(QMC5883L::SET_ON);
  setupSuccess &= qmc5883l.setRange(QMC5883L_RANGE);

  // Configure accel/gyro settings
  setupSuccess &= mpu6500.resetRegisters();
  setupSuccess &= mpu6500.setSampleRateDivider(MPU6500_SAMPLE_RATE_DIVIDER);
  setupSuccess &= mpu6500.setFIFOMode(1); // Choose value
  setupSuccess &= mpu6500.setFSync(MPU6500::EXT_SOURCE_DISABLE);
  setupSuccess &= mpu6500.setGyroLPF(1, MPU6500_GYRO_BANDWIDTH);
  setupSuccess &= mpu6500.setGyroRange(250); // Choose value
  setupSuccess &= mpu6500.setAccelLPF(1, 460); // Choose bandwidth
  setupSuccess &= mpu6500.setAccelRange(2); // Choose value
  setupSuccess &= mpu6500.enableTempSense(false);

  // Calibrate compass
  qmc5883l.calibrate(QMC5883L_CALIBRATION_TIME);
}

void loop() {
  // Setup fail condition
  if(!setupSuccess){
    Serial.println("Setup failed!");
    while(true){}
  }

  // // // Testing to see if this actually works
  if(qmc5883l.isDRDY() == 1){
    // Serial.println("Start reading");

    // Serial.print("X value: ");
    // Serial.print(qmc5883l.getXGauss());
    // Serial.print(" Y value: ");
    // Serial.print(qmc5883l.getYGauss());
    // Serial.print(" Z value: ");
    // Serial.println(qmc5883l.getZGauss());

    Serial.print("X raw: ");
    Serial.print(qmc5883l.readX());
    Serial.print(" Y raw: ");
    Serial.print(qmc5883l.readY());
    Serial.print(" Z raw: ");
    Serial.println(qmc5883l.readZ());

    // Serial.println("End reading");
  } else {
    Serial.println("Data is not ready!");
  }

  delay(300);
}
