#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <Arduino.h>

class SerialPort{
    public:

    /**
     * @brief Class constructor.
     * @param uartNum UART port number.
     * @param txPin MCU TX pin.
     * @param rxPin MCU RX pin.
     */
    SerialPort(uint8_t myUartNum, uint8_t myTxPin, uint8_t myRxPin);

    /**
     * @brief Initializes the serial port.
     * @param baudRate Desired BAUD rate (bits per second).
     * @return True if initialization succeeded, false otherwise.
     */
    bool begin(uint32_t baudRate = 9600);

    /**
     * @brief Tells you if the serial port is valid.
     * @return True if the serial port is valid, false otherwise.
     */
    bool isValid();

    /**
     * @brief TBD
     * @param data TBD
     * @return True if printing succeeded, false otherwise.
     */
    bool print(const String& data);

    /**
     * @brief TBD
     * @param data TBD
     * @return True if printing succeeded, false otherwise.
     */
    bool println(const String& data);

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
    size_t write(uint8_t data);

    private:

    uint8_t uartNum;
    uint8_t txPin;
    uint8_t rxPin;
    HardwareSerial* serial;
};

#endif