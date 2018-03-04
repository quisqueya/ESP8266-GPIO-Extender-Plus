#ifndef LATCH_CD4099B_DRIVER_H
#define LATCH_CD4099B_DRIVER_H
 
#include <Arduino.h>




class LatchCD4099BDriver{
private:
    int numberOfLatches;
    bool initialized;

    static LatchCD4099BDriver* pLatchCD4099BDriver;
    
    const int writeDisableLatch0 = D5; // write disable pin for first latch
    const int writeDisableLatch1 = D6; // write disable pin for second latch

    // both latches will use D7 as the data pin and D1, D2,  and D4 as the address pins
    const int dataPin  = D7;  // data pin
    const int addressPins0 = D1;
    const int addressPins1 = D2;
    const int addressPins2 = D4;  //Address pins A0, A1, A2
       
public:
    LatchCD4099BDriver(bool twoLatches=false);
    ~LatchCD4099BDriver();

    void begin();
    void setPin(int pinNumber, int PinState);
    void reset();
    
    // static public
    static LatchCD4099BDriver* getLatchCD4099BDriver(); 
    static bool enableSerialMonitor;
};
 
#endif LATCH_CD4099B_DRIVER_H
