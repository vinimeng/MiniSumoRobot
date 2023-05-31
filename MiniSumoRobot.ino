#define pino1MotorDireito 6
#define pino2MotorDireito 5
#define pino1MotorEsquerdo 11
#define pino2MotorEsquerdo 10
#define pinoEchoUltrassom 9
#define pinoTrigUltrassom 8
#define pinoSensorIRFrontal A0
#define pinoSensorIRTraseiroDireito A1
#define pinoSensorIRTraseiroEsquerdo A2
#define fatorParaCm 58

/**
  Classe para controlar motor DC
*/
class DCMotor {
  int spd = 255; // Velocidade: 0 ~ 255
  int pin1, pin2;

public:
  /**
    Definir pinagem do motor
  */
  void Pinout(int in1, int in2) {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  /**
    Modificar velocidade do motor.
    Velocidade: 0 ~ 255
  */
  void Speed(int in1) {
    spd = in1;
  }

  /**
    Modificar sentido do motor para ir para frente
  */
  void Forward() {
    analogWrite(pin1, spd);
    digitalWrite(pin2, LOW);
  }

  /**
    Modificar sentido do motor para ir para trás
  */
  void Backward() {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd);
  }

  /**
    Fazer motor parar
  */
  void Stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
};

DCMotor MotorDireito, MotorEsquerdo;
char robotMode = 'H'; // Modo de funcionamento do robô. H = caçar, A = atacar, F = fugir

void setup() {
  // Motores
  MotorDireito.Pinout(pino1MotorDireito, pino2MotorDireito);
  MotorEsquerdo.Pinout(pino1MotorEsquerdo, pino2MotorEsquerdo);
  
  // Ultrassom
  pinMode(pinoEchoUltrassom, INPUT);
  pinMode(pinoTrigUltrassom, OUTPUT);
  
  // Sensores infra-vermelho
  pinMode(pinoSensorIRFrontal, INPUT);
  pinMode(pinoSensorIRTraseiroEsquerdo, INPUT);
  pinMode(pinoSensorIRTraseiroDireito, INPUT);

  // Serial para debugger
  Serial.begin(9600);

  // 5 segundos antes de começar conforme regras
  //delay(5000);
}

void loop() {
  switch (robotMode) {
    case 'H': // Hunt
      huntMode();
      break;
    case 'A': // Attack
      attackMode();
      break;
    case 'F': // Flee
      fleeMode();
      break;
    default:
      huntMode();
  }

  Serial.print("Modo do Robo: ");
  Serial.println(robotMode);
}

/**
  Fazer com que o robô procure o inimigo
*/
void huntMode() {
  if (!ultrassom()) {
    rodarParaEsquerda();
  } else {
    robotMode = 'A';
  }
}

/**
  Fazer com que o robô ataque o inimigo
*/
void attackMode() {
  if (IRTraseiroDireito() || IRTraseiroEsquerdo()) {
    robotMode = 'F';
  }

  if (ultrassom()) {
    irParaFrente();
  } else if (!ultrassom() && IRFrontal()) {
    robotMode = 'F';
  } else {
    robotMode = 'H';
  }
}

/**
  Fazer com que o robô fuja
*/
void fleeMode() {
  if (IRTraseiroDireito() || IRTraseiroEsquerdo()) {
    rodarParaDireita();
    delay(100);
    irParaFrente();
  } else if (IRFrontal()) {
    rodarParaEsquerda();
    delay(100);
    irParaTras();
  } else {
    robotMode = 'H';
  }
}

/**
  Fazer com que o robô começa a vá para frente
*/
void irParaFrente() {
  MotorDireito.Speed(255);
  MotorEsquerdo.Speed(200);
  MotorEsquerdo.Forward();
  MotorDireito.Forward();
}

/**
  Fazer com que o robô começa a vá para trás
*/
void irParaTras() {
  MotorDireito.Speed(255);
  MotorEsquerdo.Speed(200);
  MotorEsquerdo.Backward();
  MotorDireito.Backward();
}

/**
  Fazer com que o robô começa a rodar para a esquerda
*/
void rodarParaEsquerda() {
  MotorDireito.Speed(155);
  MotorEsquerdo.Speed(100);
  MotorEsquerdo.Backward();
  MotorDireito.Forward();
}

/**
  Fazer com que o robô começa a rodar para a direita
*/
void rodarParaDireita() {
  MotorDireito.Speed(155);
  MotorEsquerdo.Speed(100);
  MotorEsquerdo.Forward();
  MotorDireito.Backward();
}

/**
  Retorna verdadeiro caso a distância medida para um obstáculo
  seja menor que o tamanho do Dohyō
*/
bool ultrassom() {
  digitalWrite(pinoTrigUltrassom, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinoTrigUltrassom, LOW);
  double distancia = pulseIn(pinoEchoUltrassom, HIGH);
  distancia = distancia / fatorParaCm;
  Serial.print("Distancia (cm): ");
  Serial.println(distancia);
  return distancia < 40;
}

/**
  Retorna verdadeiro se o sensor infra-vermelho frontal detectar
  a borda branca do Dohyō
*/
bool IRFrontal() {
  return analogRead(pinoSensorIRFrontal) < 100;
}

/**
  Retorna verdadeiro se o sensor infra-vermelho traseiro esquerdo detectar
  a borda branca do Dohyō
*/
bool IRTraseiroEsquerdo() {
  return analogRead(pinoSensorIRTraseiroEsquerdo) < 100;
}

/**
  Retorna verdadeiro se o sensor infra-vermelho traseiro direito detectar
  a borda branca do Dohyō
*/
bool IRTraseiroDireito() {
  return analogRead(pinoSensorIRTraseiroDireito) < 100;
}
