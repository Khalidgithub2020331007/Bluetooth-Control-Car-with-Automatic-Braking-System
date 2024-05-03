
#include <AFMotor.h>

//initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ); 
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

char command; 

void setup() 
{       
  Serial.begin(9600);  
}

void loop(){
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    Stop(); 
    switch(command){
    case 'F':  
      forward();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
    }
  } 
}

void forward()
{
  motor1.setSpeed(255); 
  motor1.run(FORWARD); 

  motor3.setSpeed(255);
  motor3.run(FORWARD); 

}

void back()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
 
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
 
}

void left()
{
  motor1.setSpeed(0); //Define maximum velocity
  motor1.run(RELEASE); //rotate the motor anti-clockwise
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  
}

void right()
{
  motor1.setSpeed(255); //Define maximum velocity
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
