#include <intrinsics.h>         //Intrinsic functions.
#include <avr_macros.h>         //Useful macros.
#include <iom328p.h>            //ATmega328p defenitions

#pragma vector =ADC_vect        //declare location
__interrupt void ISR_ADC(void) //declare interrupt function
{
  unsigned int ADC_raw;          //raw binary conversion result
  extern float solar_Voltage;            //solar panel voltage 
  extern float battery_Voltage;          //battery voltage
  extern int adc_select;        // holds what channel we're reading
  extern char batLow;           //for signaling battery low
  extern char connected;         // for signaling connected to Bluetooth
  extern char fullyCharged;       //for signallying battery full
  
  ADC_raw = ADC;                        //put raw binary value in variable
  
  if(adc_select ==0)
  {
    solar_Voltage = ((ADC_raw/1024)*1.1);    //stores voltage value in volts 

    if(solar_Voltage <= 0.6)
    {
      PORTC_PORTC2 = 1;                         //shut of charging transistor
    }
    if(solar_Voltage > 0.6)
    {
      
      PORTC_PORTC2 = 0;                         //turn on charging transistor
    }
      adc_select =1;
      ADMUX_MUX0 =1;                           //change ADC to measure battery
  }
    
    
  
  if (adc_select ==1)
  {
    battery_Voltage = ((ADC_raw/1024)*1.1);    //stores voltage value in volts    
    if(battery_Voltage > 0.9)
    {
      PORTC_PORTC2  = 1;                     //battery too high, stop charging
      fullyCharged =1;
    }
    if(battery_Voltage < 0.85)
    {
      PORTC_PORTC2 =0;
      fullyCharged =0;
    }
    if(battery_Voltage <= 0.75)
    {
      PORTC_PORTC4 = 1;                          // turn off if battery too low
      batLow = 1;
      //TODO: Send kill signal to bluetooth
    }
    if(battery_Voltage > .77)
    {
      PORTC_PORTC4 = 0;                         //turn step-up on if battery ok
      batLow =0;
    }
    adc_select =0;
    ADMUX_MUX0 = 0;                         //switch to measure battery voltage
  }
  return;
}