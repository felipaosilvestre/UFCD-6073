// Definição dos pinos para os LEDs RGBW
#define PIN_RED    9
#define PIN_GREEN  10
#define PIN_BLUE   11
#define PIN_WHITE  12

// Pino para o botão
#define BUTTON_PIN 2

// Estados da máquina de estados
enum Estado {
  VERDE,
  AMARELO,
  VERMELHO
};

Estado estadoAtual = VERDE;     // Estado inicial
unsigned long tempoEstado = 0;  // Marca o tempo de início do estado

// Variável para armazenar o estado do botão
bool botaoPressionado = false;

void setup() {
  // Configuração dos pinos como saída para os LEDs
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  pinMode(PIN_WHITE, OUTPUT);

  // Configuração do pino do botão como entrada com pull-up
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Inicializa o tempo do estado
  tempoEstado = millis();
}

void loop() {
  
  // Máquina de estados
  switch (estadoAtual) {
    case VERDE:
      acenderVerde();

      // Verifica se o botão foi pressionado
      if (digitalRead(BUTTON_PIN) == LOW) {
        botaoPressionado = true;
      }

      if (millis() - tempoEstado >= 10000 || botaoPressionado) { // 10 segundos ou botão pressionado
        estadoAtual = AMARELO;
        tempoEstado = millis();
        botaoPressionado = false;
      }
      break;

    case AMARELO:
      acenderAmarelo();
      if (millis() - tempoEstado >= 5000) { // 5 segundos
        estadoAtual = VERMELHO;
        tempoEstado = millis();
      }
      break;

    case VERMELHO:
      acenderVermelho();
      if (millis() - tempoEstado >= 10000) { // 10 segundos
        estadoAtual = VERDE;  // Volta corretamente para VERDE
        tempoEstado = millis();
      }
      break;
  }
}

// Funções para acender as cores específicas
void acenderVerde() {
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, LOW);
  digitalWrite(PIN_WHITE, LOW);
}

void acenderAmarelo() {
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, LOW);
  digitalWrite(PIN_WHITE, LOW);
}

void acenderVermelho() {
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, LOW);
  digitalWrite(PIN_WHITE, LOW);
}
