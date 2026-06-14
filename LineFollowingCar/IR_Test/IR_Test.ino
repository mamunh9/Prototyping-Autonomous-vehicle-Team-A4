
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
