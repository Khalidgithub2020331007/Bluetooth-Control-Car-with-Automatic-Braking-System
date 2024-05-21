#include <AFMotor.h>
#include <SoftwareSerial.h>

// Define motor ports on the Adafruit Motor Shield
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);

// Define Bluetooth module pins (using SoftwareSerial)
SoftwareSerial Bluetooth(2, 3); // RX, TX

// Define speed for the motors
const int SPEED = 255;

// Define ultrasonic sensor pins
#define trigPin 7
#define echoPin 8

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Serial.println("Motor, Bluetooth, and Ultrasonic Test");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {
    Serial.println("Obstacle detected! Stopping and reversing...");
    Stop();
    delay(2000);
    back();
    delay(2000);
    Stop();
  } else {
    if (Bluetooth.available() > 0) {
      char command = Bluetooth.read();
      Serial.print("Received: ");
      Serial.println(command);

      switch (command) {
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
        case 'T':
          Stop();
          break;
        default:
          Serial.println("Invalid command");
          break;
      }
    }
  }

  delay(100);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration / 58.2;
  return distance;
}

void forward() {
  Serial.println("Forward");
  motor1.setSpeed(SPEED);
  motor1.run(FORWARD);
  motor3.setSpeed(SPEED);
  motor3.run(FORWARD);
}

void back() {
  Serial.println("Backward");
  motor1.setSpeed(SPEED);
  motor1.run(BACKWARD);
  motor3.setSpeed(SPEED);
  motor3.run(BACKWARD);
}

void left() {
  Serial.println("Left");
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor3.setSpeed(SPEED);
  motor3.run(FORWARD);
}

void right() {
  Serial.println("Right");
  motor1.setSpeed(SPEED);
  motor1.run(FORWARD);
  motor3.setSpeed(0);
  motor3.run(RELEASE);
}

void Stop() {
  Serial.println("Stop");
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor3.setSpeed(0);
  motor3.run(RELEASE);
}
