#ifndef SPI_HANDLER_H
#define SPI_HANDLER_H

#include <Arduino.h>
#include <SPI.h>

bool spiScan();
bool spiInit();
bool spiBeginTransaction();
bool spiEndTransaction();

#endif