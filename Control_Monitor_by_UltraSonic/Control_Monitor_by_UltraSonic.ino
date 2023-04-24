#include <Servo.h>
#include <Keyboard.h>

Servo myservo;

int pos = 0; 

const int trigPin = 3;
const int echoPin = 4;
int led1 = 6;
int led2 = 9;
int led3 = 10;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  myservo.attach(8);
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  // if ()
  if (distance > 0 && distance < 50) {
    digitalWrite(led1, HIGH);
    delay(50);
  }
  if (distance > 0 && distance < 30) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(50);
  }
  if (distance > 0 && distance < 10) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    myservo.write(180);
    Keyboard.write(0x83);
    Keyboard.write('d');
    //Keyboard.write(0x83); // 왼쪽 윈도우 키
    delay(100);
    Keyboard.releaseAll();
    delay(50);
  } 
  if (distance >= 50) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    myservo.write(0);
    delay(50);
  }
  //delay(100);
}