#define pinoSentido1MotorA 3
#define pinoSentido2MotorA 2
#define pinoSentido1MotorB 1
#define pinoSentido2MotorB 0
#define pinoEchoUltrassom 4
#define pinoTrigUltrassom 5
#define pinoSensorIRFrontal A0

#define fatorParaCm 58

double distancia = 0;

void setup() {
  pinMode(pinoSentido1MotorA, OUTPUT);
  pinMode(pinoSentido2MotorA, OUTPUT);
  pinMode(pinoSentido1MotorB, OUTPUT);
  pinMode(pinoSentido2MotorB, OUTPUT);
  pinMode(pinoEchoUltrassom, INPUT);
  pinMode(pinoTrigUltrassom, OUTPUT);
  pinMode(pinoSensorIRFrontal, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Ultrassom
  //digitalWrite(pinoTrigUltrassom, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(pinoTrigUltrassom, LOW);
  //distancia = pulseIn(pinoEchoUltrassom, HIGH);
  //distancia = distancia / fatorParaCm;
  //Serial.print(distancia);
  //Serial.println("cm");

  // Motor
  //digitalWrite(pinoSentido1MotorA, LOW);
  //digitalWrite(pinoSentido2MotorA, HIGH);
  //digitalWrite(pinoSentido1MotorB, LOW);
  //digitalWrite(pinoSentido2MotorB, HIGH);

  //IR Frontal
  Serial.println(analogRead(pinoSensorIRFrontal));

  delay(255);
}
