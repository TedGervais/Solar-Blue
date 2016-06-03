#include <intrinsics.h>         //Intrinsic functions.
#include <avr_macros.h>         //Useful macros.
#include <iom328p.h>            //ATmega328p defenitions

#pragma vector=INT0_vect          // Declare vector location.
__interrupt void ISR_INT0(void)   // Declare interrupt function
{
  PORTC_PORTC4 =1;              //turn on the step up converter
}