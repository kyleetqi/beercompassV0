#include "serial_handler.h"

SerialPort::SerialPort(uint8_t myUartNum, uint8_t myTxPin, uint8_t myRxPin)
    : uartNum(myUartNum), txPin(myTxPin), rxPin(myRxPin) {
    switch(uartNum){
        case 0: serial = &Serial; break;
        case 1: serial = &Serial1; break;
        case 2: serial = &Serial2; break;
        default: serial = nullptr; break;
    }
}

bool SerialPort::begin(uint32_t baudRate){
    if(this->serial == nullptr) return -1;
    if(uartNum == 0){
        this->serial->begin(baudRate);
    } else {
        this->serial->begin(baudRate, SERIAL_8N1, rxPin, txPin);
    }
    return true;
}

bool SerialPort::isValid(){
    if(this->serial == nullptr) return -1;
    return true;
}

bool SerialPort::print(const String& data){
    if(this->serial == nullptr) return -1;
    this->serial->print(data);
    return true;
}

bool SerialPort::println(const String& data){
    if(this->serial == nullptr) return -1;
    this->serial->println(data);
    return true;
}

int SerialPort::available(){
    if (this->serial != nullptr){
        return this->serial->available();
    } 
    return 0;
}

int SerialPort::read(){
    if(this->serial == nullptr) return -1;
    if(this->serial->available() == 0){
        return -1;
    }
    return this->serial->read();
}

size_t SerialPort::write(uint8_t data){
    if(this->serial == nullptr) return false;
    this->serial->write(data);
    return true;
}



    