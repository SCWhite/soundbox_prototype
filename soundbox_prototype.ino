/*
GND connected GND
3.3V connected 3.3V (Feather, Zero) or VCC (MKR1000, MKRZero)
LRCLK / WS connected to pin 0 (Feather, Zero) or pin 3 (MKR1000, MKRZero)
BCLK connected to pin 1 (Feather, Zero) or pin 2 (MKR1000, MKRZero)
Data /SD connected to pin 9 (Zero) or pin A6 (MKR1000, MKRZero
*/

/**
 
 Amsterdam Sounds Kit dBA sound level meter for TTN.

*/
#define ARM_MATH_CM0PLUS
#include "SLM.h"
#include "SerialDummy.h"

//// Disable all serial ouput, use when device is deployed somewhere
//#define DISABLE_SERIAL    1

// Send to TTN after each N seconds of measuring
#define SEND_AFTER    300

//#if DISABLE_SERIAL
//#define Serial      dummy
//#endif

// Sound level meter
//change to "SerialUSB"
//SLM slm(Serial);
SLM slm(SerialUSB);

static int recording = false;

// Setup 
void setup()
{
  /*while (!Serial)
  {
  }*/
  //NOTICE!! use "SerialUSB.begin(115200)" for SAMD21 board
  //Serial.begin(115200);
  SerialUSB.begin(115200);
  //Serial.print("OK");
  //Serial1.begin(115200);

//#ifndef CFG_eu868
//  Serial.println(F("Not configured with CFG_eu86"));
//#endif

  // While not using radio
  pinMode(8, OUTPUT);
  pinMode(8, HIGH);   
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Start the sound measurements
  slm.setup();
  slm.start();
  recording = true;
}


// Keep hold of current amount of seconds running
static int secs = 0;
void loop()
{
  // On every second 
  /*uint32_t n_secs = millis()/1000;
  if (secs != n_secs)
  {
    secs = n_secs;
    if (secs == SEND_AFTER)
    {
      slm.stop();
      recording = false;
      //connect();
    }
    // Blink quickly while recording, slowly while sending
    if (recording)
    {
      digitalWrite(LED_BUILTIN, (n_secs % 2) == 0 ? HIGH : LOW);   
    }
    else
    {
      digitalWrite(LED_BUILTIN, (n_secs % 4) == 0 ? HIGH : LOW);
    }
  }*/
  // Call update as often as possible while recording, else call the runloop of LMIC
//  if (recording)
//  {
    slm.update();
    //Serial.println("");
//  }
//  else
//  {
//    os_runloop_once();
//  }
}
