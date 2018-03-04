#include "latch-cd4099B.h"

bool LatchCD4099BDriver::enableSerialMonitor=false;

LatchCD4099BDriver* LatchCD4099BDriver::pLatchCD4099BDriver = NULL;

LatchCD4099BDriver::LatchCD4099BDriver(bool twoLatches)
{
     numberOfLatches = 1;
     if(twoLatches)
     {
           numberOfLatches = 2;
     }     
     initialized = false;
}
LatchCD4099BDriver::~LatchCD4099BDriver()
{
    if(pLatchCD4099BDriver!=NULL)
    {
        delete pLatchCD4099BDriver;   
    }
    pLatchCD4099BDriver=NULL;  
}
LatchCD4099BDriver* LatchCD4099BDriver::getLatchCD4099BDriver()
{
    if(pLatchCD4099BDriver==NULL)
    {
       pLatchCD4099BDriver=new LatchCD4099BDriver(true);
       pLatchCD4099BDriver->begin();
    } 
    return pLatchCD4099BDriver;
}

void LatchCD4099BDriver::begin()
{
  
   if(enableSerialMonitor)
   {  
        Serial.println("================================================");
        Serial.println("**** staring latch CD4099B Driver class ****");
        Serial.print("     Number of latches (CD4099B chips) -> ");
        Serial.println(numberOfLatches);
   }  
   // set all used pins to output
   // writeDisableLatch0 = D5; // write disable pin for first latch
   // writeDisableLatch1 = D6; // write disable pin for second latch 
   pinMode(writeDisableLatch0,OUTPUT);
    if(numberOfLatches == 2)
    {
          pinMode(writeDisableLatch1,OUTPUT);
    }   
   // dataPin  = D7;  // data pin
    pinMode(dataPin,OUTPUT);

    // addressPins0 = D1;
    // addressPins1 = D2;
    // addressPins2 = D4;  //Address pins A0, A1, A2
    pinMode(addressPins0,OUTPUT);
    pinMode(addressPins1,OUTPUT);
    pinMode(addressPins2,OUTPUT);

    // just set to hold previous state
    // disable the outputs: 
    digitalWrite(writeDisableLatch0, HIGH);
    if(numberOfLatches == 2)
    {
          digitalWrite(writeDisableLatch1, HIGH);
    }   
    reset();
    initialized=true;
}
void LatchCD4099BDriver::reset()
{
     if(!initialized)
     {
          if(enableSerialMonitor)
          {                             
              Serial.println("*** LatchCD4099BDriver Class instance not initialized. Call begin() first to initialize this class. ***");
          }    
          return;
     }
     if(numberOfLatches == 2)
     {
         for(int pin=0; pin<16; pin++)
         {
            setPin(pin, LOW);
         }
      
     }
     else
     { 
         for(int pin=0; pin<8; pin++)
         {
            setPin(pin, LOW);
         }
     }  
}

void LatchCD4099BDriver::setPin(int pinNumber, int PinState)
{

    if(enableSerialMonitor)
    {                             
        Serial.print("CALLED setPin(");
        Serial.print(pinNumber);
        Serial.print(",");
        Serial.print(PinState);
        Serial.println(")");
    }  
    if(!initialized)
     {
          if(enableSerialMonitor)
          {                             
              Serial.println("*** LatchCD4099BDriver Class instance not initialized. Call begin() first to initialize this class. ***");
          }    
          return;
     }  
    if(numberOfLatches == 2)
    {
         if(pinNumber<0 || pinNumber>15)
         {
               if(enableSerialMonitor)
               {                             
                    Serial.print("Invalid pin number ->");
                    Serial.println(pinNumber);
               }    
               return;        
         }      
    }
    else
    {
         if(pinNumber<0 || pinNumber>7)
         {
               if(enableSerialMonitor)
               {                             
                    Serial.print("Invalid pin number ->");
                    Serial.println(pinNumber);
               }    
               return;        
         }    
    }
    int thePin=pinNumber;
    if(pinNumber>=8)
    {
         thePin = pinNumber - 8;
    }
    if(enableSerialMonitor)
    {                             
        Serial.print("thePin ==> ");
        Serial.println(thePin);
    }       
    // set the data pin
     digitalWrite(dataPin, PinState);
     
    //set address line 0
    int address= thePin & 0x01;
    if(enableSerialMonitor)
    {                             
        Serial.print("        address Pins 0 ==> ");
        Serial.println(address);
    }       
    digitalWrite(addressPins0, address);
   
    address= (thePin & 0x02) >> 1;
    if(enableSerialMonitor)
    {                             
        Serial.print("        address Pins 1 ==> ");
        Serial.println(address);
    }     
    digitalWrite(addressPins1, address);

    address= (thePin & 0x04) >> 2;
    if(enableSerialMonitor)
    {                             
        Serial.print("        address Pins 2 ==> ");
        Serial.println(address);
    }     
    digitalWrite(addressPins2, address);
        
    if(pinNumber<=7)
    {
         digitalWrite(writeDisableLatch0, LOW);
         digitalWrite(writeDisableLatch0, HIGH);
    }
    else
    {
         digitalWrite(writeDisableLatch1, LOW);
         digitalWrite(writeDisableLatch1, HIGH);
    }
    if(enableSerialMonitor)
    {
        Serial.println("");
    }  
}

