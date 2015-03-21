
//Cleaner Pins
#define DIR_PIN_CLEANER 2
#define STEP_PIN_CLEANER 3
#define BUTTON_PIN 4
#define ENABLE_PIN_CLEANER 7
//Lid Pins
#define DIR_PIN_LID 8
#define STEP_PIN_LID 5
#define ENABLE_PIN_LID 12
//IR Sensor Pins
#define IR_SENSOR-PIN 0
// speeds
#define speed_delay_cleaner 350        // higher speed delay = lower speed 
#define speed_delay_lid   350        // higher speed delay = lower speed

//Initilization 
int buttonState =0;                    //setting button state to be zero to make sure safe start
boolean personPresent = false;

// setting up pins
void setup() { 
  
  // Cleaner Pin Initilization 
  //pinMode(DIR_PIN_CLEANER, OUTPUT);                    //Direction PIN for Stepper motor  
  //pinMode(STEP_PIN_CLEANER, OUTPUT);                   //Step pin for Stepper motor
 // pinMode(ENABLE_PIN_CLEANER,OUTPUT);                  //Enable pin for stepper motor
  
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
  
   if(buttonState==HIGH || safeToTrigger())                      // check for button or sensor 
  {
    closeLid();
    delay(500);
    //startCleaning();
    delay(500);
    openLid();
  }
  
}


///////////////////////////////////////////////////////////////////////////
//                          Open Lid
///////////////////////////////////////////////////////////////////////////
void openLid(){  
    rotateLid(1,HIGH);      //Number of rotation - Direction     **Change rotateLid function for more accurte lid movement
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
  
    int steps = rotations*200*27;//calculating number of steps
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

//not complete
boolean safeToTrigger(){
  boolean safeToTrigger =false;
  int sensorPresentHighLimit= 700;
  int sensorPresentLowLimit=100;
  int sensorNotPresentHighLimit=60;
  int sensorNotPresentLowLimit=0;
  int IR_Sensor = analogRead(0);
  Serial.println(IR_Sensor);
  int i =0;
  
  if (analogRead(0) < sensorPresentHighLimit && analogRead(0) > sensorPresentLowLimit && !personPresent){
    
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

boolean irSensorPresentCheck(){
  int sensorPresentHighLimit= 700;
  int sensorPresentLowLimit=100;
  int sensorNotPresentHighLimit=60;
  int sensorNotPresentLowLimit=0;
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
boolean irSensorNotPresentCheck(){
  int sensorPresentHighLimit= 700;
  int sensorPresentLowLimit=100;
  int sensorNotPresentHighLimit=60;
  int sensorNotPresentLowLimit=0;
   
  int i;
 for(i=0;i<200;i++){
  if (analogRead(0) < sensorPresentHighLimit && analogRead(0) > sensorPresentLowLimit ){
    Serial.println("here");
    return true; //wrong trigger
       
    }
    delay(10);
 }
 
 return false;
}



  
