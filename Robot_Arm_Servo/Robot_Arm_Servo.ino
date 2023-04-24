//탱두의 아두이노 로봇팔
#include <Servo.h>
#define SW 3
#define SW2 12

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

short val1, val2, val3, val4;
short x1, x2, x3, x4;
byte deg1 = 90, deg2 = 90, deg3 = 90, deg4 = 90;
byte phase = 0;
byte save1[300], save2[300], save3[300], save4[300];
short number, repeat, i;

void setup() {
  Serial.begin(9600);
  motor1.attach(5);
  motor2.attach(6);
  motor3.attach(9);
  motor4.attach(10);
  pinMode(SW, INPUT_PULLUP);
  motor1.write(90);
  motor2.write(90);
  motor3.write(90);
  motor4.write(90);
  pinMode(SW2, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(SW) == LOW) {
    phase = 1;
    x1 = analogRead(A1);
    x2 = analogRead(A2);
    x3 = analogRead(A3);
    x4 = analogRead(A4);
  }
  if (digitalRead(SW2) == LOW) {
    if (number == 0) {
      for (i = 0; i < 300; i++) {
        save1[i] = 0;
        save2[i] = 0;
        save3[i] = 0;
        save4[i] = 0;
      }
    }
    save1[number] = deg1;
    save2[number] = deg2;
    save3[number] = deg3;
    save4[number] = deg4;
    number++;
  } 
  if (digitalRead(SW2) == HIGH) {
    if (number != 0) {
      delay(10);
      repeat = number;
      phase = 2;
    }
    number = 0;
  }

  if (phase == 1) {
    val1 = analogRead(A1);
    val2 = analogRead(A2);
    val3 = analogRead(A3);
    val4 = analogRead(A4);
    val1 -= x1;
    val2 -= x2;
    val3 -= x3;
    val4 -= x4;
    deg1 = map(val1, -340, 340, 0, 180);  //deg1=90
    deg2 = map(val2, -340, 340, 0, 180);
    deg3 = map(val3, -340, 340, 0, 180);
    deg4 = map(val4, -340, 340, 0, 180);
    deg1 = constrain(deg1, 0, 180);  //-5=0, 3845628=180
    deg2 = constrain(deg2, 0, 180);
    deg3 = constrain(deg3, 0, 180);
    deg4 = constrain(deg4, 0, 180);
    motor1.write(180 - deg1);
    motor2.write(180 - deg2);
    motor3.write(180 - deg3);
    motor4.write(180 - deg4);
  }
  if (phase == 2) {
    for (i = 0; i < repeat; i++) {
      motor1.write(180 - save1[i]);
      motor2.write(180 - save2[i]);
      motor3.write(180 - save3[i]);
      motor4.write(180 - save4[i]);
      delay(50);
    }
  }
  delay(50);
}