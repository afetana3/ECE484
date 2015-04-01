//Cleaner Pins
#define DIR_PIN_CLEANER 0
#define STEP_PIN_CLEANER 1
#define BUTTON_PIN 2
#define ENABLE_PIN_CLEANER 6

// speeds
#define speed_delay_cleaner 450        // higher speed delay = lower speed 

void setup(){
    // Cleaner Pin Initilization 
  pinMode(DIR_PIN_CLEANER, OUTPUT);                    //Direction PIN for Stepper motor  
  pinMode(STEP_PIN_CLEANER, OUTPUT);                   //Step pin for Stepper motor
  pinMode(ENABLE_PIN_CLEANER,OUTPUT);                  //Enable pin for stepper motor
  
  pinMode(BUTTON_PIN,INPUT);                           //Switch PIN     
}
void loop(){
  int buttonState = digitalRead(BUTTON_PIN);      //Check for Switch
  if(buttonState == LOW){
    rotateCleaner(1,LOW);
  }
}

void rotateCleaner(int rotations ,int dir){  
 
    digitalWrite(ENABLE_PIN_CLEANER,LOW);                  // Enable should be low for motor to start 
    digitalWrite(DIR_PIN_CLEANER,dir);                    //Setting up direction base on function input
  
    int steps = rotations*200*27;                        //calculating number of steps
    // doing each stap and have a delay in between to make it slower 
    for(int i=0; i < steps; i++)
    { 
      digitalWrite(STEP_PIN_CLEANER, HIGH);            // one step on 
      delayMicroseconds(speed_delay_cleaner);                 // delay 
      digitalWrite(STEP_PIN_CLEANER, LOW);           //stop 
      delayMicroseconds(speed_delay_cleaner);       //dealy
    }  
    
  digitalWrite(ENABLE_PIN_CLEANER,HIGH);  
}
