/* 
 *  Hardware tweaks plus this sketch gives 0.2 uA or 200 nA of deep sleep power draw
 *  Power usage in sleep mode 0.1 - 0.2 uA (between 100 and 200 nA) on TSOP Nano
 */

#include "LowPower.h"

#include <avr/sleep.h> 
#include <avr/power.h> 

#define debugmode     false
#define testmode      false   // You can use the plotter in test mode

#define SPEAKERPIN    3
#define TONELENGTH    100
#define TONEFREQUENCY 3000

#include "tools.h"
#include "cpu.h"

void setup() {

  disable_wdt();
  disable_adc();
  
  if ( debugmode ) { 
    Serial.begin(115200); 
    Serial.println(F("Booting..."));
  } else {
    disable_uart();             // Disable internal serial logic
  } 
   
  led_onoff(500,1);
  led_onoff(100,2);

}


void loop() {
  
  inputs_lowpower();  

  if ( testmode ) {
    cpu_sleep_dummy();
    unset_interrupt_dummy();
  } else {
    sleepNow();
  }
  
  pinMode(SPEAKERPIN, OUTPUT);
  tone(SPEAKERPIN, TONEFREQUENCY, TONELENGTH);
  delay(TONELENGTH-5);

}
