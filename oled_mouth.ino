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
#define SCREEN_HEIGHT 64

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

void drawSmile() {
  display.clearDisplay();

  // Dibuja una sonrisa de boca abierta con dos dientes.
  // El contorno tiene un grosor de aprox. 2px.

  // 1. Contorno inferior (arco)
  // El centro del círculo está en (64, 40) con un radio de 22
  display.drawCircleHelper(64, 40, 22, 4, SSD1306_WHITE); // Cuarto inferior izquierdo
  display.drawCircleHelper(64, 40, 22, 8, SSD1306_WHITE); // Cuarto inferior derecho
  display.drawCircleHelper(64, 41, 22, 4, SSD1306_WHITE); // Dibuja un segundo arco para grosor
  display.drawCircleHelper(64, 41, 22, 8, SSD1306_WHITE);

  // 2. Contorno superior (línea recta)
  // Conecta los extremos del arco
  display.drawLine(42, 40, 86, 40, SSD1306_WHITE);
  display.drawLine(42, 39, 86, 39, SSD1306_WHITE);

  // 3. Dientes (dos rectángulos blancos)
  display.fillRect(56, 40, 8, 8, SSD1306_WHITE); // Diente izquierdo
  display.fillRect(68, 40, 8, 8, SSD1306_WHITE); // Diente derecho

  display.display();
}

void drawSerious() {
  display.clearDisplay();
  // Dibuja una línea recta para una boca seria
  // Usamos un rectángulo relleno para un grosor de 5px.
  display.fillRect(34, 44, 61, 5, SSD1306_WHITE);
  display.display();
}

void drawSad() {
  display.clearDisplay();
  // Dibuja una boca triste usando un arco invertido
  // Para hacerla más gruesa, dibujamos múltiples arcos.
  display.drawCircleHelper(64, 60, 30, 1, SSD1306_WHITE); // Cuarto superior derecho
  display.drawCircleHelper(64, 60, 30, 2, SSD1306_WHITE); // Cuarto superior izquierdo
  display.drawCircleHelper(64, 61, 30, 1, SSD1306_WHITE);
  display.drawCircleHelper(64, 61, 30, 2, SSD1306_WHITE);
  display.drawCircleHelper(64, 62, 30, 1, SSD1306_WHITE);
  display.drawCircleHelper(64, 62, 30, 2, SSD1306_WHITE);
  display.drawCircleHelper(64, 63, 30, 1, SSD1306_WHITE);
  display.drawCircleHelper(64, 63, 30, 2, SSD1306_WHITE);
  display.display();
}

void transicionSonrisaASerio() {
  const int pasos = 30;
  for (int i = 0; i <= pasos; i++) {
    display.clearDisplay();
    float p = (float)i / pasos; // Progreso de la animación (0.0 a 1.0)

    // --- Animar la línea superior ---
    // Se mueve desde y=39 hasta y=44 (la parte superior de la boca seria)
    int y_upper = round(39.0 + (44.0 - 39.0) * p);
    display.drawLine(42, y_upper, 86, y_upper, SSD1306_WHITE);
    display.drawLine(42, y_upper + 1, 86, y_upper + 1, SSD1306_WHITE);

    // --- Animar el arco inferior (se aplana y sube) ---
    // Interpolamos los puntos clave del arco
    float y_endpoints = 40.0 + (45.0 - 40.0) * p; // Los extremos suben de y=40 a y=45
    float y_bottom = 62.0 - (62.0 - 46.0) * p;    // La parte inferior del arco sube de y=62 a y=46
    float sag = y_bottom - y_endpoints; // "sag" es la curvatura, que se reduce a casi 0

    // Calculamos los parámetros del círculo (k=centro_y, r=radio) a partir de los puntos clave
    float k, r;
    if (sag > 0.5) { // Evitamos la división por cero cuando el arco está casi plano
      k = (sag * sag + 2 * sag * y_endpoints - 484.0) / (2.0 * sag);
      r = y_bottom - k;
      // Dibujamos el arco
      display.drawCircleHelper(64, round(k), round(r), 4, SSD1306_WHITE);
      display.drawCircleHelper(64, round(k), round(r), 8, SSD1306_WHITE);
      display.drawCircleHelper(64, round(k) + 1, round(r), 4, SSD1306_WHITE); // para grosor
      display.drawCircleHelper(64, round(k) + 1, round(r), 8, SSD1306_WHITE);
    } else {
      // Cuando está plano, dibujamos una línea
      display.drawLine(42, round(y_bottom), 86, round(y_bottom), SSD1306_WHITE);
      display.drawLine(42, round(y_bottom) + 1, 86, round(y_bottom) + 1, SSD1306_WHITE);
    }

    // --- Animar los dientes ---
    // La altura del diente está determinada por el espacio entre la línea superior y el arco inferior
    float y_lower_arc_at_teeth;
    if (sag > 0.5) {
      float x_dist_sq = 64; // (56-64)^2 o (72-64)^2
      if (r * r > x_dist_sq) {
        y_lower_arc_at_teeth = k + sqrt(r * r - x_dist_sq);
      } else {
        y_lower_arc_at_teeth = y_bottom; // Si está fuera de los límites del círculo, usamos el punto más bajo
      }
    } else {
      y_lower_arc_at_teeth = y_bottom;
    }

    int tooth_top_y = y_upper + 2; // Posicionamos los dientes justo debajo de la línea superior
    int tooth_height = round(y_lower_arc_at_teeth) - tooth_top_y;

    if (tooth_height > 0) {
      display.fillRect(56, tooth_top_y, 8, tooth_height, SSD1306_WHITE);
      display.fillRect(68, tooth_top_y, 8, tooth_height, SSD1306_WHITE);
    }

    display.display();
    delay(100); // 30 pasos * 100ms = 3 segundos
  }
}

void transicionSerioATriste() {
  const int pasos = 30;
  for (int i = 0; i <= pasos; i++) {
    display.clearDisplay();

    // La línea se curva hacia abajo para formar la boca triste
    // El radio del círculo disminuye desde un valor muy grande hasta 30
    // El centro del círculo se mueve hacia arriba
    int radio = 500 - (470 * i / pasos);
    int centroY = 60 + (440 * (pasos - i) / pasos);

    display.drawCircleHelper(64, centroY, radio, 1, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY, radio, 2, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 1, radio, 1, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 1, radio, 2, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 2, radio, 1, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 2, radio, 2, SSD1306_WHITE);

    display.display();
    delay(100); // 30 pasos * 100ms = 3 segundos
  }
}

void transicionTristeASerio() {
  const int pasos = 30;
  for (int i = 0; i <= pasos; i++) {
    display.clearDisplay();

    // La boca triste se aplana para convertirse en una línea
    int radio = 30 + (470 * i / pasos);
    int centroY = 60 + (440 * i / pasos);

    display.drawCircleHelper(64, centroY, radio, 1, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY, radio, 2, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 1, radio, 1, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 1, radio, 2, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 2, radio, 1, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 2, radio, 2, SSD1306_WHITE);

    display.display();
    delay(100); // 30 pasos * 100ms = 3 segundos
  }
}

void transicionSerioASonrisa() {
  const int pasos = 30;
  for (int i = 0; i <= pasos; i++) {
    display.clearDisplay();

    // El arco inferior se forma a partir de la línea recta
    int radio = 500 - (478 * i / pasos); // De radio grande a 22
    int centroY = 45 - (5 * i / pasos);   // El centro sube

    // Dibujamos el arco que se forma
    display.drawCircleHelper(64, centroY, radio, 4, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY, radio, 8, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 1, radio, 4, SSD1306_WHITE);
    display.drawCircleHelper(64, centroY + 1, radio, 8, SSD1306_WHITE);

    // La línea superior sube a su posición final
    int lineaY = 44 - (5 * i / pasos);
    display.drawLine(42, lineaY, 86, lineaY, SSD1306_WHITE);
    display.drawLine(42, lineaY + 1, 86, lineaY + 1, SSD1306_WHITE);

    // Los dientes crecen gradualmente
    int alturaDiente = (8 * i / pasos);
    if (alturaDiente > 0) {
      display.fillRect(56, 40, 8, alturaDiente, SSD1306_WHITE);
      display.fillRect(68, 40, 8, alturaDiente, SSD1306_WHITE);
    }

    display.display();
    delay(100); // 30 pasos * 100ms = 3 segundos
  }
}

void loop() {
  // Ciclo completo de animación con transiciones

  // 1. Inicia con una sonrisa por 5 segundos
  drawSmile();
  delay(5000);

  // 2. Transición de sonrisa a serio (3 segundos)
  transicionSonrisaASerio();

  // 3. Mantiene la boca seria por 5 segundos
  delay(5000);

  // 4. Transición de serio a triste (3 segundos)
  transicionSerioATriste();

  // 5. Mantiene la boca triste por 5 segundos
  delay(5000);

  // 6. Transición de triste a serio (3 segundos)
  transicionTristeASerio();

  // 7. Mantiene la boca seria por 5 segundos
  delay(5000);

  // 8. Transición de serio a sonrisa para reiniciar el ciclo (3 segundos)
  transicionSerioASonrisa();
}
