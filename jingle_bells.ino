// Definición de las notas musicales y sus frecuencias (notación en español)
#define NOTA_SI3  247
#define NOTA_MI4  330
#define NOTA_SOL4 392
#define NOTA_LA4  440
#define NOTA_SI4  494
#define NOTA_DO5  523
#define NOTA_RE5  587
#define NOTA_MI5  659
#define NOTA_FA5  698
#define NOTA_SOL5 784
#define NOTA_LA5  880
#define NOTA_SI5  988

// Pin del zumbador
const int buzzerPin = 8;

// Melodía de "Jingle Bells"
int melody[] = {
  NOTA_MI5, NOTA_MI5, NOTA_MI5,
  NOTA_MI5, NOTA_MI5, NOTA_MI5,
  NOTA_MI5, NOTA_SOL5, NOTA_DO5, NOTA_RE5,
  NOTA_MI5,
  NOTA_FA5, NOTA_FA5, NOTA_FA5, NOTA_FA5,
  NOTA_FA5, NOTA_MI5, NOTA_MI5, NOTA_MI5, NOTA_MI5,
  NOTA_MI5, NOTA_RE5, NOTA_RE5, NOTA_MI5,
  NOTA_RE5, NOTA_SOL5
};

// Duración de las notas
int noteDurations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 8, 8,
  8, 8, 8, 8,
  4, 4
};

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  playJingleBells();
  delay(1000); // Espera un segundo antes de volver a tocar
}

void playJingleBells() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int); thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
}
