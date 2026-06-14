// --- Motor direction pins ---
#define IN1 6   // Left motor A
#define IN2 7   // Left motor B
#define IN3 8   // Right motor A
#define IN4 9   // Right motor B
#define ENA 10  // Left motor speed (PWM) — jumper removed
#define ENB 11  // Right motor speed (PWM) — jumper removed

// --- IR line sensors ---
#define IR_LEFT   5
#define IR_RIGHT  4

// --- Ultrasonic sensors ---
#define LEFT_TRIG   12
#define LEFT_ECHO   13
#define RIGHT_TRIG  3
#define RIGHT_ECHO  2

// --- IR line detection ---
#define ON_LINE  HIGH

// --- Motor speeds (PWM 0–255; L298N needs ~60+ to move) ---
#define SPEED_STRAIGHT 120
#define SPEED_TURN      85
#define SPEED_AVOID     90
#define SPEED_SEARCH   100

// --- Obstacle detection range (cm) ---
#define OBSTACLE_MIN_CM  3
#define OBSTACLE_MAX_CM  20
#define PEEK_SCAN_MIN_CM 3
#define PEEK_SCAN_MAX_CM 100

// --- Maneuver timing (ms) ---
#define STOP_PAUSE_MS       300
#define BACKUP_MS           200
#define ROTATE_SCAN_MS      550
#define PAUSE_SHORT_MS      100
#define PAUSE_MED_MS        500
#define PAUSE_LONG_MS       700
#define BYPASS_ROTATE_MS    400
#define BYPASS_FORWARD_MS   550
#define BYPASS_FORWARD2_MS  650
#define BYPASS_TURN_MS      450
#define LINE_SEARCH_TURN_MS 100
#define LINE_SEARCH_PAUSE   80
#define LINE_SEARCH_TIMEOUT 100000

#define SERIAL_DEBUG 1

int navState = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);

#if SERIAL_DEBUG
  Serial.begin(9600);
#endif

  stopMotors();
  delay(400);
}

void loop() {
  bool leftOnLine  = digitalRead(IR_LEFT)  == ON_LINE;
  bool rightOnLine = digitalRead(IR_RIGHT) == ON_LINE;

  float distLeft  = getLeftDistance();
  float distRight = getRightDistance();

#if SERIAL_DEBUG
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 200) {
    lastPrint = millis();
    Serial.print(F("L:"));
    Serial.print(leftOnLine ? 1 : 0);
    Serial.print(F(" R:"));
    Serial.print(rightOnLine ? 1 : 0);
    Serial.print(F(" UL:"));
    Serial.print(distLeft);
    Serial.print(F(" UR:"));
    Serial.println(distRight);
  }
#endif

  if (isObstacleAhead(distLeft, distRight)) {
    navState = 0;
    stopMotors();
    delay(STOP_PAUSE_MS);
    avoidObstacle();
    return;
  }

  if (leftOnLine && !rightOnLine) {
    stopMotors();
    navState = 1;
    while (digitalRead(IR_RIGHT) != ON_LINE) {
      turnLeft(SPEED_TURN);
    }
    stopMotors();
  } else if (!leftOnLine && rightOnLine) {
    stopMotors();
    navState = 2;
    while (digitalRead(IR_LEFT) != ON_LINE) {
      turnRight(SPEED_TURN);
    }
    stopMotors();
  } else if (!leftOnLine && !rightOnLine) {
    if (navState == 1) {
      stopMotors();
      while (digitalRead(IR_RIGHT) != ON_LINE) {
        turnRight(SPEED_TURN);
      }
      stopMotors();
      navState = 0;
    } else if (navState == 2) {
      stopMotors();
      while (digitalRead(IR_LEFT) != ON_LINE) {
        turnLeft(SPEED_TURN);
      }
      stopMotors();
      navState = 0;
    } else {
      stopMotors();
    }
  } else {
    moveForward(SPEED_STRAIGHT);
    navState = 0;
  }
}

bool isObstacleAhead(float leftCm, float rightCm) {
  return (leftCm  > OBSTACLE_MIN_CM && leftCm  < OBSTACLE_MAX_CM) ||
         (rightCm > OBSTACLE_MIN_CM && rightCm < OBSTACLE_MAX_CM);
}

bool isObstacleStillInView(float leftCm, float rightCm) {
  return (leftCm  > PEEK_SCAN_MIN_CM && leftCm  < PEEK_SCAN_MAX_CM) ||
         (rightCm > PEEK_SCAN_MIN_CM && rightCm < PEEK_SCAN_MAX_CM);
}

void avoidObstacle() {
  stopMotors();
  delay(PAUSE_SHORT_MS);

  moveBackward(SPEED_AVOID);
  delay(BACKUP_MS);

  rotateLeft(SPEED_AVOID);
  delay(ROTATE_SCAN_MS);
  stopMotors();
  delay(PAUSE_MED_MS);

  float distLeft  = getLeftDistance();
  float distRight = getRightDistance();

  if (isObstacleStillInView(distLeft, distRight)) {
    bypassPathA();
  } else {
    bypassPathB();
  }
}

void bypassPathA() {
  rotateRight(SPEED_AVOID);
  while (digitalRead(IR_RIGHT) != ON_LINE) {
    // motors keep running from rotateRight()
  }
  stopMotors();
  delay(PAUSE_MED_MS);

  rotateRight(SPEED_AVOID);
  delay(BYPASS_ROTATE_MS);
  stopMotors();
  delay(PAUSE_LONG_MS);

  moveForward(SPEED_AVOID);
  delay(BYPASS_FORWARD_MS);
  stopMotors();
  delay(PAUSE_MED_MS);

  rotateLeft(SPEED_AVOID);
  delay(BYPASS_TURN_MS);
  stopMotors();
  delay(PAUSE_LONG_MS);

  moveForward(SPEED_AVOID);
  delay(BYPASS_FORWARD2_MS);
  stopMotors();
  delay(PAUSE_MED_MS);

  turnLeft(SPEED_AVOID);
  delay(BYPASS_TURN_MS);
  stopMotors();
  delay(PAUSE_MED_MS);

  searchForLine();
}

void bypassPathB() {
  rotateRight(SPEED_AVOID);
  delay(BYPASS_ROTATE_MS);
  stopMotors();
  delay(PAUSE_MED_MS);

  moveForward(SPEED_AVOID);
  delay(BYPASS_FORWARD_MS + 200);
  stopMotors();
  delay(PAUSE_MED_MS);

  rotateRight(SPEED_AVOID);
  delay(BYPASS_ROTATE_MS);
  stopMotors();
  delay(PAUSE_MED_MS);

  searchForLine();
}

void searchForLine() {
  unsigned long startTime = millis();

  while (millis() - startTime < LINE_SEARCH_TIMEOUT) {
    turnLeft(SPEED_SEARCH);
    delay(LINE_SEARCH_TURN_MS);
    stopMotors();
    delay(LINE_SEARCH_PAUSE);

    if (digitalRead(IR_LEFT) == ON_LINE || digitalRead(IR_RIGHT) == ON_LINE) {
      reacquireLine();
      return;
    }

    turnRight(SPEED_SEARCH);
    delay(LINE_SEARCH_TURN_MS);
    stopMotors();
    delay(LINE_SEARCH_PAUSE);

    if (digitalRead(IR_LEFT) == ON_LINE || digitalRead(IR_RIGHT) == ON_LINE) {
      reacquireLine();
      return;
    }
  }
}

void reacquireLine() {
  stopMotors();
  delay(PAUSE_SHORT_MS);

  bool leftOnLine  = digitalRead(IR_LEFT)  == ON_LINE;
  bool rightOnLine = digitalRead(IR_RIGHT) == ON_LINE;

  if (leftOnLine && !rightOnLine) {
    while (digitalRead(IR_RIGHT) != ON_LINE) {
      turnLeft(SPEED_TURN);
    }
  } else if (!leftOnLine && rightOnLine) {
    while (digitalRead(IR_LEFT) != ON_LINE) {
      turnRight(SPEED_TURN);
    }
  }

  stopMotors();
  delay(PAUSE_SHORT_MS);
  moveForward(SPEED_STRAIGHT);
  delay(PAUSE_SHORT_MS);
  stopMotors();
}

float getLeftDistance() {
  digitalWrite(LEFT_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(LEFT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(LEFT_TRIG, LOW);
  long duration = pulseIn(LEFT_ECHO, HIGH, 22000);
  if (duration == 0) return 1000.0f;
  return duration * 0.034f / 2.0f;
}

float getRightDistance() {
  digitalWrite(RIGHT_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(RIGHT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(RIGHT_TRIG, LOW);
  long duration = pulseIn(RIGHT_ECHO, HIGH, 22000);
  if (duration == 0) return 1000.0f;
  return duration * 0.034f / 2.0f;
}

// --- Motor control with PWM on ENA / ENB ---

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
