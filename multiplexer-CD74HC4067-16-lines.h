#ifndef MULTIPLEXER_CD74HC4067_16_LINES_H
#define MULTIPLEXER_CD74HC4067_16_LINES_H
 
#include <Arduino.h>


class MultiAnalogDigitalRead{
private:
    
    bool initialized;
    void setAddress(int pinNumber);
    
    const int analogReadPin = A0;
    const int digitalReadPin  = D8;  // data pin
    const int addressPins0 = D1;
    const int addressPins1 = D2;
    const int addressPins2 = D4;    
    const int addressPins3 = D0; //Address pins A0, A1, A2, A3    
public:
    MultiAnalogDigitalRead();
    ~MultiAnalogDigitalRead();

    void begin();
    int readDigital(int pin);
    int readAnalog(int pin);
    
    // static public
    static bool enableSerialMonitor;
};
 
#endif MULTIPLEXER_CD74HC4067_16_LINES_H
