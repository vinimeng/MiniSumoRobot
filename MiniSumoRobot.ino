#define pinSentido1MotorA 3
#define pinSentido2MotorA 2

#define pinSentido1MotorB 7
#define pinSentido2MotorB 6

void setup() {
  pinMode(pinSentido1MotorA, OUTPUT);
  pinMode(pinSentido2MotorA, OUTPUT);
  pinMode(pinSentido1MotorB, OUTPUT);
  pinMode(pinSentido2MotorB, OUTPUT);
}

void loop() {
  digitalWrite(pinSentido1MotorA, HIGH);
  digitalWrite(pinSentido2MotorA, LOW);
  digitalWrite(pinSentido1MotorB, HIGH);
  digitalWrite(pinSentido2MotorB, LOW);
  delay(255);
}
