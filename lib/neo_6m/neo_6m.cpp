#include "neo_6m.h"

Neo6M::Neo6M(HardwareSerial &serial, uint16_t baud, uint8_t rxPin, uint8_t txPin)
: serial(serial), baudRate(baud), rx(rxPin), tx(txPin) {}

void Neo6M::begin(){
    this->serial.begin(this->baudRate);
    delay(1000);
}

bool Neo6M::isDRDY(){
    if(this->serial.available() == 0){
        return false;
    }
    return true;
}

bool Neo6M::read() {
    static char buffer[NEO6M_BUFFER_SIZE];
    static uint8_t index = 0;

    // Read all available chars
    while (this->serial.available()) {
        char c = this->serial.read();

        // If newline, we have a complete NMEA sentence
        if (c == '\n') {
            buffer[index] = '\0'; // null terminate
            index = 0; // reset for next sentence

            // Parse only GPGGA sentences (for now)
            if (strncmp(buffer, "$GPGGA", 6) == 0) {
                char *token;
                int fieldIndex = 0;

                token = strtok(buffer, ",");
                while (token != NULL) {
                    switch (fieldIndex) {
                        case 1:
                            if (strlen(token) >= 6) {
                                this->hour   = (token[0]-'0')*10 + (token[1]-'0');
                                this->minute = (token[2]-'0')*10 + (token[3]-'0');
                                this->second = (token[4]-'0')*10 + (token[5]-'0');
                            }
                            break;
                        case 2: {
                            float rawLat = atof(token);
                            int deg = int(rawLat / 100);
                            float min = rawLat - deg*100;
                            this->latitude = deg + min/60.0;
                            break;
                        }
                        case 3:
                            if (token[0] == 'S') this->latitude = -this->latitude;
                            break;
                        case 4: {
                            float rawLon = atof(token);
                            int deg = int(rawLon / 100);
                            float min = rawLon - deg*100;
                            this->longitude = deg + min/60.0;
                            break;
                        }
                        case 5:
                            if (token[0] == 'W') this->longitude = -this->longitude;
                            break;
                        case 7:
                            this->numSatelites = atoi(token);
                            break;
                        case 8:
                            this->horizontalDilution = atof(token);
                            break;
                        case 9:
                            this->altitude = atof(token);
                            break;
                        case 11:
                            this->geoidHeight = atof(token);
                            break;
                    }
                    token = strtok(NULL, ",");
                    fieldIndex++;
                }
                return true; // successfully parsed a valid sentence
            }

        } else {
            // Store char in buffer (avoid overflow)
            if (index < NEO6M_BUFFER_SIZE - 1) {
                buffer[index++] = c;
            } else {
                // Overflow: reset
                index = 0;
            }
        }
    }
    return false; // no complete sentence yet
}