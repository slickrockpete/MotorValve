#include "Arduino.h"
#include "MotorValve.h"

MotorValve::MotorValve(byte closepin, byte openpin, 
		       byte powerpin, byte stbypin,
		       byte closesignalpin, byte opensignalpin)
{
 close_pin = closepin;
 open_pin = openpin;
 power_pin = powerpin;
 stby_pin = stbypin;
 close_signal = closesignalpin;
 open_signal = opensignalpin;
 pinMode(open_pin, OUTPUT);
 pinMode(close_pin, OUTPUT);
 pinMode(power_pin, OUTPUT);

 pinMode(close_signal, INPUT_PULLUP);
 pinMode(open_signal, INPUT_PULLUP);
 // for debugging
 pinMode(LED_BUILTIN, OUTPUT);
 moving = false;
}

void MotorValve::open()
{
  unsigned long start, end;
  if (digitalRead(open_signal) == LOW) {
    // already open
    is_open = true;
    //return;
  }
  // for debugging
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(open_pin, HIGH);
  digitalWrite(close_pin, LOW);
  digitalWrite(power_pin, HIGH);
  digitalWrite(stby_pin, HIGH);
  moving = true;
  // now wait for the the open signal to go low
  Serial.print("opening"); // debug
  start = millis(); // debug
  do {
    // debug 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(25);
    digitalWrite(LED_BUILTIN, LOW);
    delay(25);
    Serial.print(".");
    // wait for the expected amount of time for the valve to move
    // do something here to make sure we don't wait too long
  } while (digitalRead(open_signal) != LOW);
  end = millis();
  Serial.println("open");
  Serial.print("took "); Serial.print(end - start); 
  Serial.println(" millis to open");
  moving = false;
  digitalWrite(power_pin, LOW);
  digitalWrite(stby_pin, LOW);
  is_open = true;
}


void MotorValve::close()
{
  unsigned long start, end;
  if (digitalRead(close_signal) == LOW) {
    // already closed
    is_open = false;
    //return;
  }
  // for debugging
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(open_pin, LOW);
  digitalWrite(close_pin, HIGH);
  digitalWrite(power_pin, HIGH);
  digitalWrite(stby_pin, HIGH);
  moving = true;
  start = millis(); // debug
  // now wait for the the open signal to go low
  do {
    // debug 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(25);

    // wait for the expected amount of time for the valve to move
    // do something here to make sure we don't wait too long
  } while (digitalRead(close_signal) != LOW);
  end = millis();
  Serial.print("took "); Serial.print(end - start); 
  Serial.println(" millis to close");
  moving = false;
  digitalWrite(power_pin, LOW);
  digitalWrite(stby_pin, LOW);
  is_open = false;
}

// returns true only if it is all the way open
boolean MotorValve::isopen() 
{
  if (digitalRead(open_signal) == LOW)
    return true;
  else
    return false;
}

// returns true only if it is all the way closed
boolean MotorValve::isclosed() 
{
  if (digitalRead(close_signal) == LOW)
    return true;
  else
    return false;
}


