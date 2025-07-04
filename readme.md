# Beer Compass

A compass built with the Arduino framework that always points to the nearest liquor store. This repository contains the firmware for version 0 of the project, which uses breakout boards and breadboards. Version 1 will feature a custom PCB design, but the firmware will remain largely the same since the same ICs will be used. (At least, that's the plan at the time of writing.)

# Project Organization

Tgus versuib us developed on an ESP32 using the Arduino framework. To enhance portability, the code is structured to separate hardware interfacing from the high level logic. Wrapper libraries handle I2C, SPI, and Serial communications. The IC libraries and main application avoid direct hardware calls, so if the project moves to another language or framework, only the hardware wrappers need modification, keeping the rest of the code untouched.

## Library Structure

```mermaid

flowchart TD

%% Main non-hardware libraries
main[Main Application] --> utils[Utility Library]
main --> arduino[Arduino Standard Library]
main --> locations[Liquor Store Locations]

%% Main IC libraries
main --> mpu6500[MPU6500 Library]
main --> qmc5883l[QMC5883L Library]
main --> neo6m[Neo-6M Library]

%% Main hardware interfacing libraries
main --> serial[Serial Handler]
main --> i2c[I2C Handler]

%% MPU6500 libraries
mpu6500 --> arduino
mpu6500 --> i2c

%% QMC5883L libraries

%% Neo-6M libraries
neo6m --> arduino
neo6m --> serial

%% I2C libraries
i2c --> wire[Arduino I2C Handler]
i2c --> bitops[Bit operations Library]

%% Serial libraries
serial --> arduino

```