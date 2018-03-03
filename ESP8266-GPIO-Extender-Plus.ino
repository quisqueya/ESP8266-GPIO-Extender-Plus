
#include "multiplexer-CD74HC4067-16-lines.h"
#include "latch-cd4099B.h"


// *** remember that multiplexer 1 driver uses ****
// *** for the 16 digital inputs
// *** D8 ==> Signal line
// *** D1 ==> address pins S0 select line 0
// *** D2 ==> address pins S1 select line 1
// *** D4 ==> address pins S2 select line 2
// *** D0 ==> address pins S3 select line 3

// *** remember that multiplexer 2 driver uses ****
// *** for the 16 analog inputs
// *** A0 ==> Signal line
// *** D1 ==> address pins S0 select line 0
// *** D2 ==> address pins S1 select line 1
// *** D4 ==> address pins S2 select line 2
// *** D0 ==> address pins S3 select line 3
MultiAnalogDigitalRead multiread;

// *** remember that latch driver uses ****
// *** D5 ==> write disable pin for first latch
// *** D6 ==> write disable pin for second latch (not used if only one latch is used; 
//            specified by the false parameter in the constructor.
// *** D7 ==> as the data pin for both latches
// *** D1 ==> address pins A0 for both latches
// *** D2 ==> address pins A1 for both latches
// *** D4 ==> address pins A2 for both latches

LatchCD4099BDriver latch(true); 
//  true -> indicates we are using two latches to make it 16 digital output pins.
//  false -> indicates we are using only one latch to make it 8 digital output pins.

void setup() {
  // put your setup code here, to run once:
     Serial.begin(115200);
     while (!Serial) 
     {
         ; // wait for serial port to connect. Needed for native USB port only
     }
     Serial.println("");

  //  multiread.enableSerialMonitor =true; 
    multiread.begin();  

  //  latch.enableSerialMonitor =true; 
    latch.begin();
    
  //turn of digital outputs off
   for(int i=0; i<16;i++)
  {
      latch.setPin(i, LOW);
      delay(1000);
  }
}
int pinState=HIGH;
int oldValue=LOW;
void loop() {
  // put your main code here, to run repeatedly:
/*
   //digital outputs test
   delay(1000);
   latch.setPin(outPin, pinState);
   outPin++;
   if(outPin==16)
   {
         outPin=0;
         if(pinState==HIGH)
         {
              pinState=LOW;                
         }
         else
         {
              pinState=HIGH;
         }
   }     
 */
 int val=0;
 /*
 // digital input test
 int val=0;
 for(int i=0; i<16;i++)
 {
     val=multiread.readDigital(i);
     delay(2);
     if(val==HIGH)
     {
         latch.setPin(i, pinState);
         if(i==7)
         {
             if(pinState==HIGH)
             {
                  pinState=LOW;
             }
             else
             {
                  pinState=HIGH;
             
             }
             delay(1000);
         }
     }
   */
// analog input test
// using soil moisture humidity sensors
 int oldval[16]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
 for(int i=0; i<8;i++)
 {
    latch.setPin(i, LOW);
 }   
 delay(2000); 
 for(int i=0; i<16;i++)
 {
     val=multiread.readAnalog(i);
     delay(10);
     if(val < 900)
     {
          oldval[i]=HIGH;
          latch.setPin(i, HIGH);
     }    
 }
 delay(2000);  

}
