// Include required libraries
#include <Arduino.h>
#include "utils.h"
#include "neo_6m.h"
#include "navigation.h"
#include "my_locations.h"
#include <HardwareSerial.h>

// Neo6M global declarations
#define NEO6M_SERIAL_PORT Serial1
#define NEO6M_BAUD_RATE 9600
#define NEO6M_RX 16
#define NEO6M_TX 17

// Create Neo6M object
Neo6M neo6m(NEO6M_SERIAL_PORT, NEO6M_BAUD_RATE, NEO6M_RX, NEO6M_TX);

// Keep track of setup errors
bool setupSuccess = true;

void setup() {
  // Initialize Serial
  Serial.begin(115200);
  delay(1000);

  // Initialize Neo6M Serial
  neo6m.begin();
}

void loop() {
  // Setup fail condition
  if(!setupSuccess){
    Serial.println("Setup failed!");
    while(true){}
  }

  // Read Neo6M
  while(neo6m.isDRDY()){
    neo6m.read();
  }

  Serial.print("Latitude: ");
  Serial.println(neo6m.getLatitude());
  Serial.print("Longitude: ");
  Serial.println(neo6m.getLongitude());
  Serial.println("-------------------");

  delay(200);
}