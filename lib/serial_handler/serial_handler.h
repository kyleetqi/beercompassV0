#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <Arduino.h>

class SerialPort{
    public:

    /**
     * @brief Class constructor.
     * @param uartNum TBD
     * @param txPin TBD
     * @param rxPin TBD
     */
    SerialPort(uint8_t uartNum, uint8_t txPin, uint8_t rxPin);

    /**
     * @brief TBD
     * @param baudRate TBD
     */
    void begin(uint32_t baudRate = 9600);

    /**
     * @brief TBD
     * @param data TBD
     */
    void print(const String& data);

    /**
     * @brief TBD
     * @param data TBD
     */
    void println(const String& data);

    /**
     * @brief TBD
     * @return TBD
     */
    int available();

    /**
     * @brief TBD
     * @return TBD
     */
    int read();

    /**
     * @brief TBD
     * @param data TBD
     * @return TBD
     */
    void write(uint8_t data);

    private:

    uint8_t _uartNum;
    uint8_t _txPin;
    uint8_t _rxPin;
    HardwareSerial* _serial;

};

#endif