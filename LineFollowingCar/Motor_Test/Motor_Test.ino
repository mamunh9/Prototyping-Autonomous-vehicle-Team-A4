/*
 * Motor Test — wheels only
 * Wiring: IN1=6, IN2=7, IN3=8, IN4=9, ENA=10, ENB=11
 *
 * Upload this sketch, then watch the wheels cycle:
 *   forward → backward → turn left → turn right → rotate left → rotate right → stop
 * Each step runs for 2 seconds.
 */

#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define ENA 10
#define ENB 11

#define TEST_SPEED 150

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stopMotors();
  delay(500);
}

void loop() {
  moveForward(TEST_SPEED);
  delay(2000);

  moveBackward(TEST_SPEED);
  delay(2000);

  turnLeft(TEST_SPEED);
  delay(2000);

  turnRight(TEST_SPEED);
  delay(2000);

  rotateLeft(TEST_SPEED);
  delay(2000);

  rotateRight(TEST_SPEED);
  delay(2000);

  stopMotors();
  delay(2000);
}

void moveForward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveBackward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnRight(int speed) {
  analogWrite(ENA, 0);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void rotateLeft(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rotateRight(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
