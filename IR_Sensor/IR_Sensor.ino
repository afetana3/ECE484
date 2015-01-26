int x; 

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  x=analogRead(2);    //Read value form analog pin 2 
  Serial.println(x);  //print the value in the screen
  
  
   
}
