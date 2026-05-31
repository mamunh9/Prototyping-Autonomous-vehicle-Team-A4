/*
 * Ultrasonic Sensor Test — no motors
 * Wiring: Left TRIG=12 ECHO=13, Right TRIG=3 ECHO=2
 *
 * Upload this sketch, open Serial Monitor at 9600 baud.
 * Move your hand in front of each sensor and watch distance in cm.
 *   ~3–400 cm = normal range
 *   1000 = no echo (out of range or wiring issue)
 */

#define LEFT_TRIG   12
#define LEFT_ECHO   13
#define RIGHT_TRIG  3
#define RIGHT_ECHO  2

void setup() {
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);
  Serial.begin(9600);
  Serial.println(F("Ultrasonic Test — wave hand in front of sensors"));
}

void loop() {
  float leftCm  = getDistance(LEFT_TRIG, LEFT_ECHO);
  float rightCm = getDistance(RIGHT_TRIG, RIGHT_ECHO);

  Serial.print(F("Left="));
  Serial.print(leftCm);
  Serial.print(F(" cm   Right="));
  Serial.print(rightCm);
  Serial.println(F(" cm"));

  delay(300);
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 22000);
  if (duration == 0) return 1000.0f;
  return duration * 0.034f / 2.0f;
}
