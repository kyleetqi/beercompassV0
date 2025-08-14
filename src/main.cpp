// Include required libraries
#include <Arduino.h>
#include "i2c_handler.h"
#include "utils.h"
#include "qmc5883l.h"
#include "mpu6500.h"
#include "neo_6m.h"
#include "imu.h"

// OLED global declarations
#define OLED_ADDR 0x3c // I2C address of OLED
#define SCREEN_WIDTH 128 // Screen width
#define SCREEN_HEIGHT 64 // Screen height
#define OLED_RESET -1 // OLED reset macro

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
#define QMC5883L_RANGE 2 // +/- range in Gauss

// Create magnetometer object
QMC5883L qmc5883l(QMC5883L_ADDR);

// Accel/Gyro global declarations
#define MPU6500_ADDR 0x68 // I2C address of MPU6500
#define MPU6500_SAMPLE_RATE_DIVIDER 9 // Eq. to 100 Hz output rate
#define MPU6500_FIFO_MODE 0 // Overwrite old data
#define MPU6500_ACCEL_BANDWIDTH 44 // Accel LPF cutoff frequency
#define MPU6500_ACCEL_RANGE 2 // +/- range in m/s^2
#define MPU6500_TEMP_DISABLE 0 // Disable temp sensor
#define MPU6500_GYRO_DISABLE 0 // Disable gyro sensor
// The following macros are unecessary if gyro remains disabled.
// #define MPU6500_GYRO_BANDWIDTH 44
// #define MPU6500_GYRO_RANGE 250

// Create MPU6500 object
MPU6500 mpu6500(MPU6500_ADDR);

// Struct for storing sensor information
Vec3 accel, mag;

// Keep track of setup errors
bool setupSuccess = true;

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
  setupSuccess &= mpu6500.setFIFOMode(MPU6500_FIFO_MODE); // Choose value
  setupSuccess &= mpu6500.setFSync(MPU6500::EXT_SOURCE_DISABLE);
  setupSuccess &= mpu6500.setAccelLPF(1, MPU6500_ACCEL_BANDWIDTH);
  setupSuccess &= mpu6500.setAccelRange(MPU6500_ACCEL_RANGE);
  // Disable gyro for now
  // setupSuccess &= mpu6500.setGyroLPF(1, MPU6500_GYRO_BANDWIDTH);
  // setupSuccess &= mpu6500.setGyroRange(MPU6500_GYRO_RANGE);
  setupSuccess &= mpu6500.enableGyro(MPU6500_GYRO_DISABLE);
  setupSuccess &= mpu6500.enableTempSense(MPU6500_TEMP_DISABLE);

  // Calibrate compass
  qmc5883l.calibrate(QMC5883L_CALIBRATION_TIME);
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
    mag.x = qmc5883l.getX();
    mag.y = qmc5883l.getY();
    mag.z = qmc5883l.getZ();
  }

  // Get accelerometer readings
  if(mpu6500.isDRDY() == 1){
    mpu6500.readAccel();
    accel.x = mpu6500.getAccelX();
    accel.y = mpu6500.getAccelY();
    accel.z = mpu6500.getAccelZ();
  }

  // Get tilt-compensated azimuth
  float azimuth = true_azimuth(accel.x, accel.y, accel.z, mag.x, mag.y, mag.z);

  Serial.println("START READING");

  // Print accelerometer readings
  Serial.print("X accel: ");
  Serial.print(accel.x);
  Serial.print(" Y accel: ");
  Serial.print(accel.y);
  Serial.print(" Z accel: ");
  Serial.println(accel.z);

  // Print magnetometer readings
  Serial.print("X mag: ");
  Serial.print(mag.x);
  Serial.print(" Y mag: ");
  Serial.print(mag.y);
  Serial.print(" Z mag: ");
  Serial.println(mag.z);

  // Print tilt-compensated azimuth
  Serial.print("Corrected azimuth: ");
  Serial.println((int)azimuth);

  Serial.println("END READING");

  delay(200);
}
