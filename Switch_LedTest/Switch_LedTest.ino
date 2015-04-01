

int Button = 2;         // the number of the input pin
int RedLed = 11;
int GreenLed=12;
int state = HIGH

void setup()
{
  pinMode(Button, INPUT);
  pinMode(RedLed, OUTPUT);     
  pinMode(GreenLed,OUTPUT);
}

void loop()
{
  if(digitalRead(Button)){              // toggle LED each time botton get pressed 
        state = ~state;
        digitalWrite(REDLed, state);   
        digitalWrite(GreenLed, state); 
  }

}
