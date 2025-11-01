/*
  Instrucciones de Conexión (Pantalla OLED SSD1306 I2C a Arduino):
  - VCC a 5V
  - GND a GND
  - SDA a A4 (o pin SDA)
  - SCL a A5 (o pin SCL)

  Nota: Si usas una placa diferente a Arduino Uno, los pines SDA/SCL pueden variar.
  - Arduino Mega: SDA (20), SCL (21)
  - Arduino Leonardo: SDA (2), SCL (3)
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Dimensiones de la pantalla en píxeles
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT CENTRO_X_1
#define RADIO_1 60
#define CENTRO_X_1 64
#define CENTRO_Y_1 0
#define ALTO_DIENTE 20
#define ANCHO_DIENTE 20
#define ANCHO_LINEA 4

// Dirección I2C del display OLED. Comunes son 0x3C o 0x3D.
// Asegúrate de usar la correcta para tu pantalla.
#define OLED_ADDR 0x3C

// Declaración de un objeto display de Adafruit
// El pin de reset (-1) no se usa en este caso, compartiendo el pin de reset de Arduino.
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  // Inicializar el display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("Fallo al inicializar SSD1306"));
    for(;;); // Bucle infinito si falla
  }

  // Limpiar el buffer de la pantalla
  display.clearDisplay();
  display.display(); // Actualizar la pantalla
}

void sonrie() {
  display.clearDisplay();
  // Dibuja una sonrisa de boca abierta con dos dientes.
  // El contorno tiene un grosor de ANCHOLINEA px.
 for (int i = 0; i <= ANCHO_LINEA; i++) {
   // 1. Contorno inferior (arco)
   // El centro del círculo está en (CENTRO_X_1, CENTRO_Y_1) con un radio de RADIO_1 y dibuja ANCHO_LINEA veces para darle espesor
    display.drawCircleHelper(CENTRO_X_1-1, CENTRO_Y_1, RADIO_1-i, 4, SSD1306_WHITE); // Cuarto inferior izquierdo
    display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1, RADIO_1-i, 8, SSD1306_WHITE); // Cuarto inferior derecho
   // 2. Contorno superior (línea recta)
   // Conecta los extremos del arco y lo dibuja ANCHO_LINEA veces
    display.drawLine(CENTRO_X_1-RADIO_1, CENTRO_Y_1+i, CENTRO_X_1+RADIO_1, CENTRO_Y_1+i, SSD1306_WHITE);
  }
  // 3. Dientes (dos rectángulos blancos)
  display.fillRect(CENTRO_X_1-25, CENTRO_Y_1+3, ANCHO_DIENTE, ALTO_DIENTE, SSD1306_WHITE); // Diente izquierdo
  display.fillRect(CENTRO_X_1+25-ANCHO_DIENTE+1, CENTRO_Y_1+3, ANCHO_DIENTE, ALTO_DIENTE, SSD1306_WHITE); // Diente derecho
  display.display();
}


void serio() {
  display.clearDisplay();
  // Dibuja una línea recta para una boca seria
  // Usamos un rectángulo relleno para un grosor de 5px.
 for (int i = 0; i <= ANCHO_LINEA; i++) {
  display.drawLine(CENTRO_X_1-RADIO_1, CENTRO_Y_1+i, CENTRO_X_1+RADIO_1, CENTRO_Y_1+i, SSD1306_WHITE);
 }
  display.display();
}

void triste() {
  display.clearDisplay();
  // Dibuja una cara triste.
  // El contorno tiene un grosor de ANCHOLINEA px.
 for (int i = 0; i <= ANCHO_LINEA; i++) {
   // 1. Contorno inferior (arco)
   // El centro del círculo está en (CENTRO_X_1, CENTRO_Y_1) con un radio de RADIO_1 y dibuja ANCHO_LINEA veces para darle espesor
    display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1+RADIO_1, RADIO_1-i, 1, SSD1306_WHITE); // Cuarto inferior izquierdo
    display.drawCircleHelper(CENTRO_X_1-1, CENTRO_Y_1+RADIO_1, RADIO_1-i, 2, SSD1306_WHITE); // Cuarto inferior derecho
  }
  display.display();
}


void transicionSonrisaASerio() {
  const int pasos = 30;
  for (int i = 0; i <= pasos; i++) {
   // Dibuja una línea recta para una boca seria
    for (int i = 0; i <= ANCHO_LINEA; i++) {
    display.drawLine(CENTRO_X_1-RADIO_1, CENTRO_Y_1+i, CENTRO_X_1+RADIO_1, CENTRO_Y_1+i, SSD1306_WHITE);
    }
   
    display.display();
    delay(100); // 30 pasos * 100ms = 3 segundos
  }
}

void tristeASerio() {
  triste();
  delay(500);
  const int pasos = 30;
  for (int j = 10; j <= pasos; j+=3) {
    display.clearDisplay();
   
    // Cara triste
    for (int i = 0; i <= ANCHO_LINEA; i++) {
      // El centro del círculo está en (CENTRO_X_1, CENTRO_Y_1) con un radio de RADIO_1 y dibuja ANCHO_LINEA veces para darle espesor
      display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1+RADIO_1*j/8, (RADIO_1*j/8)-i, 1, SSD1306_WHITE); // Cuarto inferior izquierdo
      display.drawCircleHelper(CENTRO_X_1-1, CENTRO_Y_1+RADIO_1*j/8, (RADIO_1*j/8)-i, 2, SSD1306_WHITE); // Cuarto inferior derecho
    }

    display.display();
    delay(100); 
  }
  serio();
}


void serioATriste() {
  serio();
  delay(500);
  const int pasos = 30;
  for (int j = pasos; j >= 10; j-=3) {
    display.clearDisplay();
   
    // Cara triste
    for (int i = 0; i <= ANCHO_LINEA; i++) {
      // El centro del círculo está en (CENTRO_X_1, CENTRO_Y_1) con un radio de RADIO_1 y dibuja ANCHO_LINEA veces para darle espesor
      display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1+RADIO_1*j/8, (RADIO_1*j/8)-i, 1, SSD1306_WHITE); // Cuarto inferior izquierdo
      display.drawCircleHelper(CENTRO_X_1-1, CENTRO_Y_1+RADIO_1*j/8, (RADIO_1*j/8)-i, 2, SSD1306_WHITE); // Cuarto inferior derecho
    }

    display.display();
    delay(100); 
  }
  triste();
}



void loop() {
  // Ciclo completo de animación con transiciones

  // 1. Inicia con una sonrisa por 5 segundos
  //sonrie();
  //delay(5000);
  //serio();
  //delay(5000);
  //triste();
  delay(5000);
  tristeASerio();
  delay(5000);
  serioATriste();
  // 2. Transición de sonrisa a serio (3 segundos)
  //transicionSonrisaASerio();

  // 3. Mantiene la boca seria por 5 segundos
  //delay(5000);

  // 4. Transición de serio a triste (3 segundos)
  //transicionSerioATriste();

  // 5. Mantiene la boca triste por 5 segundos
  //delay(5000);

  // 6. Transición de triste a serio (3 segundos)
  //tristeASerio();

  // 7. Mantiene la boca seria por 5 segundos
  //delay(5000);

  // 8. Transición de serio a sonrisa para reiniciar el ciclo (3 segundos)
  //transicionSerioASonrisa();
}
