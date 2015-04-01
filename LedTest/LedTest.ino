/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int RedLed = 11;
int GreenLed=12;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(RedLed, OUTPUT);     
  pinMode(GreenLed,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(RedLed, HIGH);   // turn the LED on (HIGH is the voltage level)
   digitalWrite(GreenLed, HIGH);   // turn the LED on (HIGH is the voltage level)
 
  delay(1000);               // wait for a second
  digitalWrite(RedLed, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(GreenLed, LOW);    // turn the LED off by making the voltage LOW

  delay(1000);               // wait for a second
}
