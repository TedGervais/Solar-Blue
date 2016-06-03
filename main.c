//
//      
//
//
//
//
//
//
//
//              

#include <iom328p.h>            //ATmega328p defenitions
#define BAUD 115200
#define CLKSPD          //clock speed
#define MYUBRR
#include <intrinsics.h>     //Intrinsic functions.
#include <avr_macros.h>     //Useful macros.

float solar_Voltage;            //solar panel voltage 
float battery_Voltage;          //battery voltage
int adc_select;        // holds what channel we're reading
char batLow;           //for signaling battery low
char connected;         // for signaling connected to Bluetooth
char fullyCharged;       //for signallying battery full

int main(void)
{
  DDRD = 0xF2; // USART and LED control
  DDRC = 0x14; // ADC, step-up converter, bluetooth switch
  
  
  ADMUX_REFS1 = 1;
  ADMUX_REFS0 = 1;      //set ADC to internal 1.1V reference
  ADCSRA_ADEN= 1;      //enable the ADC
  ADCSRA_ADIE = 1;      // enable interrupt for adc conversion complete
  ADCSRB_ADTS2 =0;
  ADCSRB_ADTS1 =0;
  ADCSRB_ADTS0 =0;      // free running mode for conversion
  ADCSRA_ADATE = 0;     //enable auto triggering on source (free run)
  ADCSRA_ADSC = 1;      // start first conversion with ADC0 selected
  adc_select = 0;       // reminder variable for channel 0 selected
  
  EICRA_ISC01 =1;
  EICRA_ISC00 =1;       
  EIMSK_INT0 = 1;       //enable int0 for rising edge trigger
  __enable_interrupt();   //enable global interrupts
  
  while(1)
  {
    if(batLow)
    {
      for (int i =0; i < 5; i++)
        {
          PORTD_PORTD5 = 0;         //if battery low, red light flashes 5 times
          __delay_cycles(20000000);
          PORTD_PORTD5 = 1;
        }
    }
    if(fullyCharged)
    {
      for (int i =0; i < 5; i++)
        {
          PORTD_PORTD6 = 0;         //if battery full, green light flashes 5 times
          __delay_cycles(20000000);
          PORTD_PORTD6 = 1;
        }   
    }
      
    
  }
  
}
