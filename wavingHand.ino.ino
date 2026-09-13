#include <Servo.h>

const int TRIG_PIN = 8;
const int ECHO_PIN = 9;
const int SERVO_PIN = 7;

Servo handServo;


void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  handServo.attach(SERVO_PIN);
  handServo.write(90);
}
 
float finddistance() { // find out the distance using the hc-sr04 sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(3);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration * 0.0343 / 2;
  Serial.println(distance);
  return distance;
}


bool handdetected() { // checks if your hand is there so that it can wave back
  int confirmations = 0;

  for (int i = 0; i < 3; i++) {
    float distance = finddistance();

    if (distance <= 20) {
      confirmations++;
    }

    delay(100);
  }

  return confirmations == 3;
}


void handWaves() {
  handServo.write(90);
  delay(300);

  handServo.write(130);
  delay(300);
  handServo.write(90);
  delay(300);
  handServo.write(130);
  delay(300);
  handServo.write(90);
  handServo.write(65);
  delay(300);
  handServo.write(90);
}

void loop() {
  if (handdetected()) {
    handWaves();
  }
}