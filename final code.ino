#include <AFMotor.h>

// Initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);

const int trigPin = 7;
const int echoPin = 8;

int val;
int Speed = 255;
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    val = Serial.read();

    Stop();

    if (val == 'F') {
      forward();
    }

    if (val == 'B') {
      back();
    }

    if (val == 'L') {
      left();
    }

    if (val == 'R') {
      right();
    }

    if (val == 'T') {
      Stop();
    }
  }
  
  // Check for obstacles
  distance = getDistance();
  if (distance > 0 && distance <= 20) { // If an obstacle is within 20 cm
    Stop();
  }
}

void forward() {
  motor1.setSpeed(Speed);
  motor1.run(FORWARD);
  motor3.setSpeed(Speed);
  motor3.run(FORWARD);
}

void back() {
  motor1.setSpeed(Speed);
  motor1.run(BACKWARD);
  motor3.setSpeed(Speed);
  motor3.run(BACKWARD);
}

void left() {
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  
  motor3.setSpeed(Speed);
  motor3.run(FORWARD);
}

void right() {
  motor1.setSpeed(Speed);
  motor1.run(FORWARD);
  
  motor3.setSpeed(0);
  motor3.run(RELEASE);
}

void Stop() {
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  
  motor3.setSpeed(0);
  motor3.run(RELEASE);
}

int getDistance() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  return distance;
}
