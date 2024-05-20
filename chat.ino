#include <AFMotor.h>
#include <SoftwareSerial.h>

#define echoPin 8
#define trigPin 7

long duration, distance;
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
SoftwareSerial Bluetooth(2, 3); // RX, TX
int val;
int Speeed = 255;

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Ultrasonic sensor code
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Automatic braking system
  if (distance < 20) {
    Serial.println("Obstacle detected! Reversing...");
    back();
    delay(2000);
    Stop();
  } else {
    // Check for user input if distance is safe
    if (Bluetooth.available() > 0) {
      val = Bluetooth.read();
      Serial.print("Received: ");
      Serial.println(val);
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
  }

  delay(100);
}

void forward() {
  motor1.setSpeed(Speeed);
  motor1.run(FORWARD);
  motor3.setSpeed(Speeed);
  motor3.run(FORWARD);
}

void back() {
  motor1.setSpeed(Speeed);
  motor1.run(BACKWARD);
  motor3.setSpeed(Speeed);
  motor3.run(BACKWARD);
}

void left() {
  motor1.setSpeed(0); // Stop the left motor
  motor1.run(RELEASE);
  motor3.setSpeed(Speeed); // Move the right motor forward
  motor3.run(FORWARD);
}

void right() {
  motor1.setSpeed(Speeed); // Move the left motor forward
  motor1.run(FORWARD);
  motor3.setSpeed(0); // Stop the right motor
  motor3.run(RELEASE);
}

void Stop() {
  motor1.setSpeed(0); // Stop the left motor
  motor1.run(RELEASE);
  motor3.setSpeed(0); // Stop the right motor
  motor3.run(RELEASE);
}
