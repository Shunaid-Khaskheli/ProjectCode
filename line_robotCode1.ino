#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

// Ultrasonic Sensor Initialization
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define max_distance 50

// IR Sensor Initialization
#define IR_LEFT A0
#define IR_RIGHT A1

// DC MOTOR Initialization
#define MAX_SPEED 200
#define MAX_SPEED_OFFSET 20

Servo servo;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, max_distance);

DC_Motor motor1(1, MOTOR12_1KHZ);
DC_Motor motor2(2, MOTOR12_1KHZ);
DC_Motor motor3(3, MOTOR34_1KHZ);
DC_Motor motor4(4, MOTOR34_1KHZ);


int distance = 0;
int leftDistance;
int rightDistance;
boolean object;

void setup() {
  Serial.begin(9600);
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);
  servo.attach(10);
  servo.write(90);

  motor1.setSpeed(120);
  motor2.setSpeed(120);
  motor3.setSpeed(120);
  motor4.setSpeed(120);
}

void loop() 
{
  if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 0 ) 
  {  objectAvoid(); }
  
  else if (digitalRead(irLeft) == 0 && digitalRead(irRight) == 1 ) 
  {  objectAvoid();
     Serial.println("TL");  // Turn Left
     moveLeft();
  }
  
  else if (digitalRead(irLeft) == 1 && digitalRead(irRight) == 0 )
  {
    objectAvoid();
    Serial.println("TR");  // Turn Right
    moveRight();
  }
  
  else if (digitalRead(irLeft) == 1 && digitalRead(irRight) == 1 )
  {
    Stop(); // Stop!
  }
}

void objectAvoid() {
  distance = getDistance();
  if (distance <= 15) //Stop
    {
      Stop();
      Serial.println("Stop");

    l ookLeft();
      lookRight();
      delay(100);  
    
  if (rightDistance <= leftDistance)  // Left
    { 
      object = true;
      turn();
      Serial.println("moveLeft");
    }
  else  //right 
    {
      object = false;
      turn();
      Serial.println("moveRight");
    }
    delay(100);
    }
  else 
    {  //forword
      Serial.println("moveforword");
      moveForward();
    }
}

int getDistance() {
  delay(50);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 100;
  }
  return cm;
}

int lookLeft () {
  //lock left
  servo.write(150);
  delay(500);
  leftDistance = getDistance();
  delay(100);
  servo.write(90);
  Serial.print("Left:");
  Serial.print(leftDistance);
  return leftDistance;
  delay(100);
}

int lookRight() {
  //lock right
  servo.write(30);
  delay(500);
  rightDistance = getDistance();
  delay(100);
  servo.write(90);
  Serial.print("   ");
  Serial.print("Right:");
  Serial.println(rightDistance);
  return rightDistance;
  delay(100);
}
void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void moveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

}
void turn() {
  if (object == false) {
    Serial.println("turn Right");
    moveLeft();
    delay(700);
    moveForward();
    delay(800);
    moveRight();
    delay(900);
    if (digitalRead(irRight) == 1) {
      loop();
    } else {
      moveForward();
    }
  }
  else {
    Serial.println("turn left");
    moveRight();
    delay(700);
    moveForward();
    delay(800);
    moveLeft();
    delay(900);
    if (digitalRead(irLeft) == 1) {
      loop();
    } else {
      moveForward();
    }
  }
}
void moveRight() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void moveLeft() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}