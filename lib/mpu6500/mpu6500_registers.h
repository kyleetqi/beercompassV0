#ifndef MPU6500_REGISTERS_H
#define MPU6500_REGISTERS_H

#define SELF_TEST_X_GYRO   0x00
#define SELF_TEST_Y_GYRO   0x01
#define SELF_TEST_Z_GYRO   0x02

#define SELF_TEST_X_ACCEL  0x0D
#define SELF_TEST_Y_ACCEL  0x0E
#define SELF_TEST_Z_ACCEL  0x0F

#define XG_OFFSET_H        0x13
#define XG_OFFSET_L        0x14
#define YG_OFFSET_H        0x15
#define YG_OFFSET_L        0x16
#define ZG_OFFSET_H        0x17
#define ZG_OFFSET_L        0x18

#define ACCEL_XOUT_H       0x3B
#define ACCEL_XOUT_L       0x3C
#define ACCEL_YOUT_H       0x3D
#define ACCEL_YOUT_L       0x3E
#define ACCEL_ZOUT_H       0x3F
#define ACCEL_ZOUT_L       0x40

#define TEMP_OUT_H         0x41
#define TEMP_OUT_L         0x42

#define GYRO_XOUT_H        0x43
#define GYRO_XOUT_L        0x44
#define GYRO_YOUT_H        0x45
#define GYRO_YOUT_L        0x46
#define GYRO_ZOUT_H        0x47
#define GYRO_ZOUT_L        0x48


#endif