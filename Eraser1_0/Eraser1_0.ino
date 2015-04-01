
//Cleaner Pins
#define DIR_PIN_CLEANER 0
#define STEP_PIN_CLEANER 1
#define BUTTON_PIN 2
#define ENABLE_PIN_CLEANER 6
//Lid Pins
#define DIR_PIN_LID 7
#define STEP_PIN_LID 8
#define ENABLE_PIN_LID 13
//IR Sensor Pins
#define IR_SENSOR-PIN 0
//Pressure Sensor
#define Pressure_Sensor_PIN 1
// speeds
#define speed_delay_cleaner 350        // higher speed delay = lower speed 
#define speed_delay_lid   450        // higher speed delay = lower speed
//LED
#define GreenLed 12
#define RedLed 11

//Initilization 
int buttonState =0;                    //setting button state to be zero to make sure safe start
boolean personPresent = false;
int sensorPresentHighLimit= 700;
  int sensorPresentLowLimit=300;
  int sensorNotPresentHighLimit=250;
  int sensorNotPresentLowLimit=0;

// setting up pins
void setup() { 
  //LED
  pinMode(RedLed, OUTPUT);     
  pinMode(GreenLed,OUTPUT);
  // Cleaner Pin Initilization 
  pinMode(DIR_PIN_CLEANER, OUTPUT);                    //Direction PIN for Stepper motor  
  pinMode(STEP_PIN_CLEANER, OUTPUT);                   //Step pin for Stepper motor
  pinMode(ENABLE_PIN_CLEANER,OUTPUT);                  //Enable pin for stepper motor
  
  pinMode(BUTTON_PIN,INPUT);                           //Switch PIN     
  
  // Lid Pin Initilization 
  pinMode(DIR_PIN_LID, OUTPUT);                        //Direction PIN for Stepper motor  
  pinMode(STEP_PIN_LID, OUTPUT);                       //Step pin for Stepper motor
  pinMode(ENABLE_PIN_LID,OUTPUT);                      //Enable pin for stepper motor 
  Serial.begin(9600);

   
}

void loop() {    
  buttonState = digitalRead(BUTTON_PIN);      //Check for Switch
                                              
                                              //we are going to have check for sensor
                                              
     
  digitalWrite(GreenLed, HIGH);   // turn the Green LED on (HIGH is the voltage level)

   if(buttonState== LOW || safeToTrigger() && nobodySeating()  )                      // check for button or sensor 
  {
    digitalWrite(GreenLed, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(RedLed, HIGH);   // turn the LED on (HIGH is the voltage level)
    
    Serial.println("inside");
    closeLid();
    delay(1500);
    startCleaning();
    delay(1500);
    openLid();
    
    digitalWrite(RedLed, LOW);    // turn the LED off by making the voltage LOW
  }
  
}


///////////////////////////////////////////////////////////////////////////
//                          Open Lid
///////////////////////////////////////////////////////////////////////////
void openLid(){  
    rotateLidUp(1,HIGH);      //Number of rotation - Direction     **Change rotateLid function for more accurte lid movement
}
///////////////////////////////////////////////////////////////////////////
//                          Close Lid
///////////////////////////////////////////////////////////////////////////
void closeLid(){  
   rotateLid(1,LOW);       //Number of rotation - Direction       **Change rotateLid function for more accurte lid movement
}
/////////////////////////////////////////////////////////////////////////////
//                          Start Cleaning
///////////////////////////////////////////////////////////////////////////
void startCleaning(){
  rotateCleaner(2,LOW);      //Number of rotation - Direction  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                    TOOLS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
//                          Cleaner Rotation
////////////////////////////////////////////////////////////////////////////
//Check speed and direction and # rotation base on 200 step and 19 gear reduction = 1 rotation 
void rotateCleaner(int rotations ,int dir){  
 
    digitalWrite(ENABLE_PIN_CLEANER,LOW);                  // Enable should be low for motor to start 
    digitalWrite(DIR_PIN_CLEANER,dir);                    //Setting up direction base on function input
  
    int steps = rotations*200*19;                        //calculating number of steps
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

/////////////////////////////////////////////////////////////////////////////
//                         Lid Rotation
///////////////////////////////////////////////////////////////////////////
//Check speed and direction and # rotation base on 200 step and 27 gear reduction = 1 rotation 
void rotateLid(int rotations ,int dir){  
   
    digitalWrite(ENABLE_PIN_LID,LOW);                    // Enable should be low for motor to start 
    digitalWrite(DIR_PIN_LID,dir);                      //Setting up direction base on function input
  
    int steps = rotations*200*19;//calculating number of steps
    // doing each stap and have a delay in between to make it slower 
    for(int i=0; i < steps; i++)
    { 
      digitalWrite(STEP_PIN_LID, HIGH);                 // one step on 
      delayMicroseconds(speed_delay_lid);                  // delay 
      digitalWrite(STEP_PIN_LID, LOW);                //stop 
      delayMicroseconds(speed_delay_lid);            //dealy
    }  
    
  digitalWrite(ENABLE_PIN_LID,HIGH);  
}
/////////////////////////////////////////////////////////////////////////////
//                         Safe Trigger
/////////////////////////////////////////////////////////////////////////////
boolean safeToTrigger(){
  boolean safeToTrigger =false;
  
  int IR_Sensor = analogRead(0);
  Serial.println(IR_Sensor);
  int i =0;
  
  if (analogRead(0) < sensorPresentHighLimit && analogRead(0) > sensorPresentLowLimit && !personPresent){
    Serial.println("IR_Sensor,Inside if");
     personPresent = irSensorPresentCheck();
    
    }else if(analogRead(0) < sensorNotPresentHighLimit && analogRead(0) > sensorNotPresentLowLimit && personPresent){
      //check to see if person left bathroom !!!
      personPresent = irSensorNotPresentCheck();
      if(!personPresent){
        safeToTrigger =true;
        Serial.println("True");
      }
            
    }
    
    
  return safeToTrigger;
}

/////////////////////////////////////////////////////////////////////////////
//                       Person Present  
/////////////////////////////////////////////////////////////////////////////
boolean irSensorPresentCheck(){
  //limits - it need to be defined 
 
  int IR_Sensor = analogRead(0);
  int i ;
  boolean present ;
  
  for(i=0;i<100;i++){
     if (analogRead(0) < sensorNotPresentHighLimit && analogRead(0) > sensorNotPresentLowLimit){
    
      return false;
      
    
    }
  }
  delay(1000);
  for(i=0;i<100;i++){
     if (analogRead(0) < sensorNotPresentHighLimit && analogRead(0) > sensorNotPresentLowLimit){
    
      return false;
      
    
    }
  }
  delay(1000);
  for(i=0;i<100;i++){
     if (analogRead(0) < sensorNotPresentHighLimit && analogRead(0) > sensorNotPresentLowLimit){
    
      return false;
      
    Serial.println("Just checking");
     }
  }
  
  return true ;
}
/////////////////////////////////////////////////////////////////////////////
//                         Person Not present
/////////////////////////////////////////////////////////////////////////////
boolean irSensorNotPresentCheck(){
  //limits - it need to be defined above 
 
   
  int i;
 for(i=0;i<300;i++){                                                                            // 2 seacond dealy and checking if person present
  if (analogRead(0) < sensorPresentHighLimit && analogRead(0) > sensorPresentLowLimit ){        // if person present then return true
    Serial.println("here");
    return true; //wrong trigger
       
    }
    delay(10);
 }
 
 return false;                                                                                // if person not present then return false
}
/////////////////////////////////////////////////////////////////////////////
//                         Nobay Seating
/////////////////////////////////////////////////////////////////////////////
boolean nobodySeating(){
  boolean seating = false ;
  int sensorHighLimit = 11;
  int sensorLowLimit =7;
  Serial.println("Pressure_Sensor,Function");
  Serial.println(analogRead(1));
  delay(500);
  if(analogRead(1)> sensorHighLimit  || analogRead(1)==0){                     //check if somebody seating or seat is up  
   Serial.println("Pressure_Sensor,Function");
    return false ;
  }
  return true;                                                                            //retuen true if nobody seating
}
void rotateLidUp(int rotations ,int dir){  
   
    digitalWrite(ENABLE_PIN_LID,LOW);                    // Enable should be low for motor to start 
    digitalWrite(DIR_PIN_LID,dir);                      //Setting up direction base on function input
  
    int steps = rotations*200*19.5;//calculating number of steps
    // doing each stap and have a delay in between to make it slower 
    for(int i=0; i < steps; i++)
    { 
      digitalWrite(STEP_PIN_LID, HIGH);                 // one step on 
      delayMicroseconds(speed_delay_lid);                  // delay 
      digitalWrite(STEP_PIN_LID, LOW);                //stop 
      delayMicroseconds(speed_delay_lid);            //dealy
    }  
    
  digitalWrite(ENABLE_PIN_LID,HIGH);  
}


  
