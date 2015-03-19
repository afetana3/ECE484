
#define DIR_PIN 2
#define STEP_PIN 3
#define BUTTON_PIN 4
#define ENABLE_PIN 7

#define speed_delay 350


int buttonState =0;

// setting up pins
void setup() { 
  
  pinMode(DIR_PIN, OUTPUT);                    //Direction PIN for Stepper motor  
  pinMode(STEP_PIN, OUTPUT);                   //Step pin for Stepper motor
  pinMode(ENABLE_PIN,OUTPUT);                  //Enable pin for stepper motor
  pinMode(BUTTON_PIN,INPUT);                   //Switch PIN                   

   
}


void loop() {  
  
  buttonState = digitalRead(BUTTON_PIN);      //Check for Switch
                                              //we are going to have check for sensor
  
   if(buttonState==HIGH)                      // check for button or sensor 
  {
    closeLid();
    Rotate(1,HIGH);                           //5 rotation of stepper gear forward 
    //Rotate(1,LOW);                            //5 rotation of stepper gear backward
    openLid();
  }
  
}

//Check speed and direction and # rotation base on 200 step = 1 rotation 
void Rotate(int rotations ,int dir){  
 
    digitalWrite(ENABLE_PIN,LOW);            // Enable should be low for motor to start 
    digitalWrite(DIR_PIN,dir);               //Setting up direction base on function input
  
    int steps = rotations*200*19;               //calculating number of steps
    // doing each stap and have a delay in between to make it slower 
    for(int i=0; i < steps; i++)
    { 
      digitalWrite(STEP_PIN, HIGH);          // one step on 
      delayMicroseconds(speed_delay);        // delay 
      digitalWrite(STEP_PIN, LOW);           //stop 
      delayMicroseconds(speed_delay);        //dealy
    }  
    
  digitalWrite(ENABLE_PIN,HIGH);  
}
void openLid(){  
    int rotations = 1;
    int dir=HIGH;
    
    digitalWrite(ENABLE_PIN,LOW);            // Enable should be low for motor to start 
    digitalWrite(DIR_PIN,dir);               //Setting up direction base on function input
  
    int steps = rotations*200*19;               //calculating number of steps
    // doing each stap and have a delay in between to make it slower 
    for(int i=0; i < steps; i++)
    { 
      digitalWrite(STEP_PIN, HIGH);          // one step on 
      delayMicroseconds(speed_delay);        // delay 
      digitalWrite(STEP_PIN, LOW);           //stop 
      delayMicroseconds(speed_delay);        //dealy
    }  
    
  digitalWrite(ENABLE_PIN,HIGH);  
}
void closeLid(){  
  int rotations = 1;
  int dir = LOW;
 
    digitalWrite(ENABLE_PIN,LOW);            // Enable should be low for motor to start 
    digitalWrite(DIR_PIN,dir);               //Setting up direction base on function input
  
    int steps = rotations*200*19;               //calculating number of steps
    // doing each stap and have a delay in between to make it slower 
    for(int i=0; i < steps; i++)
    { 
      digitalWrite(STEP_PIN, HIGH);          // one step on 
      delayMicroseconds(speed_delay);        // delay 
      digitalWrite(STEP_PIN, LOW);           //stop 
      delayMicroseconds(speed_delay);        //dealy
    }  
    
  digitalWrite(ENABLE_PIN,HIGH);  
}
  
