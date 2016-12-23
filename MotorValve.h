/*
A library to control a motorized ball valve
  using the TB6612FNG Toshiba H-bridge
-----------------------------------------------------------------

The pins must be connected accordingly (see the datasheet of the H-bridge).
    -the PWM (PWMA and PWMB) controls for the tb6612fng are always set 
     all the way HIGH or LOW
     so no need to use a pwm pin
    -the enable pin on the H-bridge should be connected either to 5V
     or to a pin on the Arduino, which is set to HIGH, for the H-bridge 
     to function
    -the red (closed signal) and green (open signal) line on the valve
     should be connected to input pins (Is a pullup resisitor necessary here?)
    -it is possible to control 2 valves with one tb6612fng
    -The yellow line on the valve should be connected to [A or B]01 and the 
     blue line should be connected to [A or B]02.
    - the stby pin should be shared by both valves

This is derived from the TB6612FNG library by shrajtofle@gmail.com

I hope this library will help you in your projects!
*/
#ifndef MotorValve_H
#define MotorValve_H
#include "Arduino.h"


class MotorValve
{
 private:
   byte open_pin;
   byte close_pin;
   byte power_pin;
   byte stby_pin;
   byte open_signal;
   byte close_signal;
   boolean moving;
   boolean is_open;
 public:
   MotorValve(byte closepin, byte openpin, 
	      byte powerpin, byte stbypin,
	      byte closesignalpin, byte opensignalpin);
   void open();
   void close();
   boolean isopen();
   boolean isclosed();
};

#endif /*  MotorValve_H */
