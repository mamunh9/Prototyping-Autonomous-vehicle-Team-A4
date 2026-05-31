/*
 * IR Sensor Test — no motors
 * Wiring: Left IR=D5, Right IR=D4
 *
 * Upload this sketch, open Serial Monitor at 9600 baud.
 * Place each sensor over black line vs white surface and watch values:
 *   1 = on line (HIGH), 0 = off line (LOW)  — matches main sketch ON_LINE = HIGH
 *
 * If values look reversed on your track, your sensors may use LOW = on line.
 */

#define IR_LEFT   5
#define IR_RIGHT  4

void setup() {
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  Serial.begin(9600);
  Serial.println(F("IR Test — move sensors over line and white surface"));
  Serial.println(F("Format: Left=1/0  Right=1/0"));
}

void loop() {
  int left  = digitalRead(IR_LEFT);
  int right = digitalRead(IR_RIGHT);

  Serial.print(F("Left="));
  Serial.print(left);
  Serial.print(F("  Right="));
  Serial.println(right);

  delay(200);
}
