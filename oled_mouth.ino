/*
  Instrucciones de Conexión (Pantalla OLED SSD1306 I2C a Arduino):
  - VCC a 5V
  - GND a GND
  - SDA a A4 (o pin SDA)
  - SCL a A5 (o pin SCL)
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OledMouth.h" // Incluimos la nueva biblioteca

// --- Constantes de Configuración de la Pantalla ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

// --- Inicialización de Objetos ---
// Objeto de la pantalla
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Objeto de nuestra biblioteca, pasándole la pantalla que controlará
OledMouth boca(display);

void setup() {
  Serial.begin(9600);

  // Inicializar el display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("Fallo al inicializar SSD1306"));
    for(;;); // Bucle infinito si falla
  }

  // Limpiar el buffer de la pantalla al inicio
  display.clearDisplay();
  display.display();
}

void loop() {
  boca.sonrie();
  delay(500);
  boca.animarSonrisa(false); // sonrie -> serio
  delay(500);
  boca.animarTristeza(false); // serio -> triste
  delay(500);
  boca.animarTristeza(true); // triste -> serio
  delay(500);
  boca.animarSorpresa(false); // serio -> sorpresa
  delay(500);
  boca.animarSorpresa(true); // sorpresa -> serio
  delay(500);
  boca.animarSonrisa(true); // serio -> sonrie
  delay(500);
}
