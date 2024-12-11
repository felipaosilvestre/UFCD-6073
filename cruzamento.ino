// Definição dos pinos para o Semáforo 1 (Via Principal)
#define SEM1_VERDE    2
#define SEM1_AMARELO  3
#define SEM1_VERMELHO 4

// Definição dos pinos para o Semáforo 2 (Via Secundária)
#define SEM2_VERDE    5
#define SEM2_AMARELO  6
#define SEM2_VERMELHO 7

// Estados da máquina de estados
enum Estado {
  SEM1_VERDE_SEM2_VERMELHO,
  SEM1_AMARELO_SEM2_VERMELHO,
  SEM1_VERMELHO_SEM2_VERDE,
  SEM1_VERMELHO_SEM2_AMARELO
};

Estado estadoAtual = SEM1_VERDE_SEM2_VERMELHO; // Estado inicial
unsigned long tempoEstado = 0; // Marca o tempo de início do estado

void setup() {
  // Configuração dos pinos como saída para o Semáforo 1
  pinMode(SEM1_VERDE, OUTPUT);
  pinMode(SEM1_AMARELO, OUTPUT);
  pinMode(SEM1_VERMELHO, OUTPUT);

  // Configuração dos pinos como saída para o Semáforo 2
  pinMode(SEM2_VERDE, OUTPUT);
  pinMode(SEM2_AMARELO, OUTPUT);
  pinMode(SEM2_VERMELHO, OUTPUT);

  // Inicializa os semáforos no estado inicial
  tempoEstado = millis();
}

void loop() {
  // Máquina de estados para os semáforos
  switch (estadoAtual) {
    case SEM1_VERDE_SEM2_VERMELHO:
      semaforo1Verde();
      semaforo2Vermelho();
      if (millis() - tempoEstado >= 10000) { // 10 segundos
        estadoAtual = SEM1_AMARELO_SEM2_VERMELHO;
        tempoEstado = millis();
      }
      break;

    case SEM1_AMARELO_SEM2_VERMELHO:
      semaforo1Amarelo();
      semaforo2Vermelho();
      if (millis() - tempoEstado >= 3000) { // 3 segundos
        estadoAtual = SEM1_VERMELHO_SEM2_VERDE;
        tempoEstado = millis();
      }
      break;

    case SEM1_VERMELHO_SEM2_VERDE:
      semaforo1Vermelho();
      semaforo2Verde();
      if (millis() - tempoEstado >= 10000) { // 10 segundos
        estadoAtual = SEM1_VERMELHO_SEM2_AMARELO;
        tempoEstado = millis();
      }
      break;

    case SEM1_VERMELHO_SEM2_AMARELO:
      semaforo1Vermelho();
      semaforo2Amarelo();
      if (millis() - tempoEstado >= 3000) { // 3 segundos
        estadoAtual = SEM1_VERDE_SEM2_VERMELHO;
        tempoEstado = millis();
      }
      break;
  }
}

// Funções para o Semáforo 1 (Via Principal)
void semaforo1Verde() {
  digitalWrite(SEM1_VERDE, HIGH);
  digitalWrite(SEM1_AMARELO, LOW);
  digitalWrite(SEM1_VERMELHO, LOW);
}

void semaforo1Amarelo() {
  digitalWrite(SEM1_VERDE, LOW);
  digitalWrite(SEM1_AMARELO, HIGH);
  digitalWrite(SEM1_VERMELHO, LOW);
}

void semaforo1Vermelho() {
  digitalWrite(SEM1_VERDE, LOW);
  digitalWrite(SEM1_AMARELO, LOW);
  digitalWrite(SEM1_VERMELHO, HIGH);
}

// Funções para o Semáforo 2 (Via Secundária)
void semaforo2Verde() {
  digitalWrite(SEM2_VERDE, HIGH);
  digitalWrite(SEM2_AMARELO, LOW);
  digitalWrite(SEM2_VERMELHO, LOW);
}

void semaforo2Amarelo() {
  digitalWrite(SEM2_VERDE, LOW);
  digitalWrite(SEM2_AMARELO, HIGH);
  digitalWrite(SEM2_VERMELHO, LOW);
}

void semaforo2Vermelho() {
  digitalWrite(SEM2_VERDE, LOW);
  digitalWrite(SEM2_AMARELO, LOW);
  digitalWrite(SEM2_VERMELHO, HIGH);
}
