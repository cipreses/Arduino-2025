#include "OledMouth.h"

// Constructor: Inicializa la referencia al objeto de la pantalla
OledMouth::OledMouth(Adafruit_SSD1306& display) : _display(display) {}

/*
  Anima la transición entre la sonrisa y la cara seria.
  - Si 'inversa' es 'false', la animación va de 'sonrie' a 'serio'.
  - Si 'inversa' es 'true', la animación va de 'serio' a 'sonrie'.
*/
void OledMouth::animarSonrisa(bool inversa) {
  if (inversa) {
    serio();
  } else {
    sonrie();
  }

  const int pasos = 30;
  int j_inicial = inversa ? pasos : 1;
  int j_final = inversa ? 1 : pasos;
  int j_incremento = inversa ? -2 : 2;

  for (int j = j_inicial; (inversa ? j >= j_final : j <= j_final); j += j_incremento) {
    _display.clearDisplay();
    for (int i = 0; i <= ANCHO_LINEA; i++) {
      _display.drawCircleHelper(CENTRO_X_1 - 1, CENTRO_Y_1 - (j * 2), (RADIO_1 - i + j / 2), 4, SSD1306_WHITE);
      _display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1 - (j * 2), (RADIO_1 - i + j / 2), 8, SSD1306_WHITE);
      _display.drawLine(CENTRO_X_1 - RADIO_1, CENTRO_Y_1 + i, CENTRO_X_1 + RADIO_1, CENTRO_Y_1 + i, SSD1306_WHITE);
    }
    _display.fillRect(CENTRO_X_1 - 25, CENTRO_Y_1 + 3, ANCHO_DIENTE, ALTO_DIENTE - (j + 5), SSD1306_WHITE);
    _display.fillRect(CENTRO_X_1 + 25 - ANCHO_DIENTE + 1, CENTRO_Y_1 + 3, ANCHO_DIENTE, ALTO_DIENTE - (j + 5), SSD1306_WHITE);
    _display.display();
    delay(50);
  }

  if (inversa) {
    sonrie();
  } else {
    serio();
  }
}

/*
  Anima la transición entre la cara seria y la cara triste.
*/
void OledMouth::animarTristeza(bool inversa) {
  if (inversa) {
    triste();
  } else {
    serio();
  }

  const int pasos = 30;
  int j_inicial = inversa ? 10 : pasos;
  int j_final = inversa ? pasos : 10;
  int j_incremento = inversa ? 3 : -3;

  for (int j = j_inicial; (inversa ? j <= j_final : j >= j_final); j += j_incremento) {
    _display.clearDisplay();
    for (int i = 0; i <= ANCHO_LINEA; i++) {
      _display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1 + RADIO_1 * j / 8, (RADIO_1 * j / 8) - i, 1, SSD1306_WHITE);
      _display.drawCircleHelper(CENTRO_X_1 - 1, CENTRO_Y_1 + RADIO_1 * j / 8, (RADIO_1 * j / 8) - i, 2, SSD1306_WHITE);
    }
    _display.display();
    delay(100);
  }

  if (inversa) {
    serio();
  } else {
    triste();
  }
}

/*
  Anima la transición entre la cara seria y la cara de sorpresa.
*/
void OledMouth::animarSorpresa(bool inversa) {
  if (inversa) {
    sorpresa();
  } else {
    serio();
  }

  const int pasos = 30;
  const int umbral_fase = pasos * 0.6;

  for (int j = 0; j <= pasos; j++) {
    _display.clearDisplay();
    if (inversa) {
      if (j < umbral_fase) {
        int avance = j;
        int pos_y = RADIO_2 + ((CENTRO_Y_1 - RADIO_2) * avance) / umbral_fase;
        int radio_actual = RADIO_2 - ((RADIO_2 - 2) * avance) / umbral_fase;
        int radio_interior = RADIO_2 / 2 - ((RADIO_2 / 2) * avance) / umbral_fase;
        _display.fillCircle(_display.width() / 2, pos_y, radio_actual, SSD1306_WHITE);
        if (radio_interior > 0) {
          _display.fillCircle(_display.width() / 2, pos_y, radio_interior, SSD1306_BLACK);
        }
      } else {
        int pasos_fase2 = pasos - umbral_fase;
        int avance = j - umbral_fase;
        int acortamiento = RADIO_1 - (RADIO_1 * avance) / pasos_fase2;
        for (int i = 0; i <= ANCHO_LINEA; i++) {
          _display.drawLine(CENTRO_X_1 - RADIO_1 + acortamiento, CENTRO_Y_1 + i, CENTRO_X_1 + RADIO_1 - acortamiento, CENTRO_Y_1 + i, SSD1306_WHITE);
        }
      }
    } else {
      if (j < umbral_fase) {
        int acortamiento = (RADIO_1 * j) / umbral_fase;
        for (int i = 0; i <= ANCHO_LINEA; i++) {
          _display.drawLine(CENTRO_X_1 - RADIO_1 + acortamiento, CENTRO_Y_1 + i, CENTRO_X_1 + RADIO_1 - acortamiento, CENTRO_Y_1 + i, SSD1306_WHITE);
        }
      } else {
        int pasos_fase2 = pasos - umbral_fase;
        int avance = j - umbral_fase;
        int pos_y = CENTRO_Y_1 - ((CENTRO_Y_1 - RADIO_2) * avance) / pasos_fase2;
        int radio_actual = 2 + ((RADIO_2 - 2) * avance) / pasos_fase2;
        int radio_interior = (RADIO_2 * avance) / (pasos_fase2 * 2);
        _display.fillCircle(_display.width() / 2, pos_y, radio_actual, SSD1306_WHITE);
        if (radio_interior > 0) {
          _display.fillCircle(_display.width() / 2, pos_y, radio_interior, SSD1306_BLACK);
        }
      }
    }
    _display.display();
  }

  if (inversa) {
    serio();
  } else {
    sorpresa();
  }
}

void OledMouth::sonrie() {
  _display.clearDisplay();
  for (int i = 0; i <= ANCHO_LINEA; i++) {
    _display.drawCircleHelper(CENTRO_X_1 - 1, CENTRO_Y_1, RADIO_1 - i, 4, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1, RADIO_1 - i, 8, SSD1306_WHITE);
    _display.drawLine(CENTRO_X_1 - RADIO_1, CENTRO_Y_1 + i, CENTRO_X_1 + RADIO_1, CENTRO_Y_1 + i, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1 + 1, CENTRO_Y_1 + 58, RADIO_1 - 43 - i, 1, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1 + 58, RADIO_1 - 43 - i, 2, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1 + 1, CENTRO_Y_1 + 58, RADIO_1 - 43 - i - 4, 1, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1 + 58, RADIO_1 - 43 - i - 4, 2, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1 + 1, CENTRO_Y_1 + 58, RADIO_1 - 43 - i - 7, 1, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1 + 58, RADIO_1 - 43 - i - 7, 2, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1 + 1, CENTRO_Y_1 + 58, RADIO_1 - 43 - i - 10, 1, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1 + 58, RADIO_1 - 43 - i - 10, 2, SSD1306_WHITE);
  }
  _display.fillRect(CENTRO_X_1 - 25, CENTRO_Y_1 + 3, ANCHO_DIENTE, ALTO_DIENTE, SSD1306_WHITE);
  _display.fillRect(CENTRO_X_1 + 25 - ANCHO_DIENTE + 1, CENTRO_Y_1 + 3, ANCHO_DIENTE, ALTO_DIENTE, SSD1306_WHITE);
  _display.display();
}

void OledMouth::serio() {
  _display.clearDisplay();
  for (int i = 0; i <= ANCHO_LINEA; i++) {
    _display.drawLine(CENTRO_X_1 - RADIO_1, CENTRO_Y_1 + i, CENTRO_X_1 + RADIO_1, CENTRO_Y_1 + i, SSD1306_WHITE);
  }
  _display.display();
}

void OledMouth::triste() {
  _display.clearDisplay();
  for (int i = 0; i <= ANCHO_LINEA; i++) {
    _display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1 + RADIO_1, RADIO_1 - i, 1, SSD1306_WHITE);
    _display.drawCircleHelper(CENTRO_X_1 - 1, CENTRO_Y_1 + RADIO_1, RADIO_1 - i, 2, SSD1306_WHITE);
  }
  _display.display();
}

void OledMouth::sorpresa() {
  _display.clearDisplay();
  _display.fillCircle(_display.width() / 2, RADIO_2, RADIO_2, SSD1306_WHITE);
  _display.fillCircle(_display.width() / 2, RADIO_2, RADIO_2 / 2, SSD1306_BLACK);
  _display.display();
}
