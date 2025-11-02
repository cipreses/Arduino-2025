#ifndef OLED_MOUTH_H
#define OLED_MOUTH_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OledMouth {
public:
  // Constructor: Recibe una referencia al objeto de la pantalla
  OledMouth(Adafruit_SSD1306& display);

  // Funciones para dibujar las expresiones estáticas
  void sonrie();
  void serio();
  void triste();
  void sorpresa();

  // Funciones para animar las transiciones entre expresiones
  void animarSonrisa(bool inversa);
  void animarTristeza(bool inversa);
  void animarSorpresa(bool inversa);

private:
  // Referencia al objeto de la pantalla
  Adafruit_SSD1306& _display;

  // Constantes de dibujo. Se hacen estáticas para que no ocupen memoria en cada instancia.
  static const int RADIO_1 = 60;
  static const int RADIO_2 = 10;
  static const int CENTRO_X_1 = 64; // Reemplazando SCREEN_HEIGHT
  static const int CENTRO_Y_1 = 0;
  static const int ALTO_DIENTE = 20;
  static const int ANCHO_DIENTE = 20;
  static const int ANCHO_LINEA = 4;
};

#endif // OLED_MOUTH_H
