#include <AFMotor.h>
 
//initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
 
int val;
int Speeed = 255;
const int trigPin = 7;
const int echoPin = 8;

int Speed = 255;
long duration;
int distance;

void setup()
{
  Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop(){
 
             distance = getDistance();
                Serial.println(distance);
 if(distance>=20){
  if(Serial.available() > 0){
    val = Serial.read();
     
    Stop();
     
          if (val == 'F'){
          forward();
          }
 
          if (val == 'B'){
          back();
          }
 
          if (val == 'L'){
          left();
          }
 
          if (val == 'R'){
          right();
          }


          if (val == 'T'){
          Stop();
          }
  }}
 else{
  Stop();
 }
            

}
          
 
           
 
 
 
void forward()
{
  motor1.setSpeed(Speeed); 
  motor1.run(FORWARD); 
  motor3.setSpeed(252);
  motor3.run(FORWARD); 
}
 
void back()
{
  motor1.setSpeed(Speeed); 
  motor1.run(BACKWARD);   
  motor3.setSpeed(252);
  motor3.run(BACKWARD);
  
}
 
void left()
{
  motor1.setSpeed(0); //Define maximum velocity
  motor1.run(RELEASE); //rotate the motor anti-clockwise
  
  motor3.setSpeed(Speeed); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
}
 
void right()
{
  motor1.setSpeed(Speeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
 
  motor3.setSpeed(0); //Define maximum velocity
  motor3.run(RELEASE); //rotate the motor anti-clockwise
 
}
 

 
 
void Stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
 
}

int getDistance() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  duration = pulseIn(echoPin, HIGH);


  distance = duration * 0.034 / 2; 


  return distance;
}
