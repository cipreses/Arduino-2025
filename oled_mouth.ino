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
#define RADIO_1 60
#define RADIO_2 10
#define CENTRO_X_1 SCREEN_HEIGHT
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rieASerio() {
  sonrie();
  const int pasos = 30;
  for (int j = 1; j <= pasos; j+=2) { //10,13,16,19,22,25,28
    display.clearDisplay();
    for (int i = 0; i <= ANCHO_LINEA; i++) {
       display.drawCircleHelper(CENTRO_X_1-1, CENTRO_Y_1-(j*2), (RADIO_1-i+j/2), 4, SSD1306_WHITE); // Cuarto inferior izquierdo
       display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1-(j*2), (RADIO_1-i+j/2), 8, SSD1306_WHITE); // Cuarto inferior derecho
       display.drawLine(CENTRO_X_1-RADIO_1, CENTRO_Y_1+i, CENTRO_X_1+RADIO_1, CENTRO_Y_1+i, SSD1306_WHITE);
    }
    display.fillRect(CENTRO_X_1-25, CENTRO_Y_1+3, ANCHO_DIENTE, ALTO_DIENTE-(j+5), SSD1306_WHITE); // Diente izquierdo
    display.fillRect(CENTRO_X_1+25-ANCHO_DIENTE+1, CENTRO_Y_1+3, ANCHO_DIENTE, ALTO_DIENTE-(j+5), SSD1306_WHITE); // Diente derecho
    display.display();
    delay(50); // 30 pasos * 100ms = 3 segundos
  }
  serio();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void serioARie() {
  serio();
  const int pasos = 30;
  for (int j = pasos; j >= 1; j-=2) { //10,13,16,19,22,25,28
    display.clearDisplay();
    for (int i = 0; i <= ANCHO_LINEA; i++) {
       display.drawCircleHelper(CENTRO_X_1-1, CENTRO_Y_1-(j*2), (RADIO_1-i+j/2), 4, SSD1306_WHITE); // Cuarto inferior izquierdo
       display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1-(j*2), (RADIO_1-i+j/2), 8, SSD1306_WHITE); // Cuarto inferior derecho
       display.drawLine(CENTRO_X_1-RADIO_1, CENTRO_Y_1+i, CENTRO_X_1+RADIO_1, CENTRO_Y_1+i, SSD1306_WHITE);
    }
    display.fillRect(CENTRO_X_1-25, CENTRO_Y_1+3, ANCHO_DIENTE, ALTO_DIENTE-(j+5), SSD1306_WHITE); // Diente izquierdo
    display.fillRect(CENTRO_X_1+25-ANCHO_DIENTE+1, CENTRO_Y_1+3, ANCHO_DIENTE, ALTO_DIENTE-(j+5), SSD1306_WHITE); // Diente derecho
    display.display();
    delay(50); // 30 pasos * 100ms = 3 segundos
  }
  sonrie();
}


/////////////////////
void tristeASerio() {
  triste();
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

/////////////////////
void serioATriste() {
  serio();
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
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
   // 3. lengua (arco hacia abajo) 
    display.drawCircleHelper(CENTRO_X_1+1, CENTRO_Y_1+58, RADIO_1-43-i, 1, SSD1306_WHITE); // Cuarto inferior izquierdo
    display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1+58, RADIO_1-43-i, 2, SSD1306_WHITE); // Cuarto inferior derecho
    display.drawCircleHelper(CENTRO_X_1+1, CENTRO_Y_1+58, RADIO_1-43-i-4, 1, SSD1306_WHITE); // Cuarto inferior izquierdo
    display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1+58, RADIO_1-43-i-4, 2, SSD1306_WHITE); // Cuarto inferior derecho
    display.drawCircleHelper(CENTRO_X_1+1, CENTRO_Y_1+58, RADIO_1-43-i-7, 1, SSD1306_WHITE); // Cuarto inferior izquierdo
    display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1+58, RADIO_1-43-i-7, 2, SSD1306_WHITE); // Cuarto inferior derecho
    display.drawCircleHelper(CENTRO_X_1+1, CENTRO_Y_1+58, RADIO_1-43-i-10, 1, SSD1306_WHITE); // Cuarto inferior izquierdo
    display.drawCircleHelper(CENTRO_X_1, CENTRO_Y_1+58, RADIO_1-43-i-10, 2, SSD1306_WHITE); // Cuarto inferior derecho
     
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

void sorpresa() {
  display.clearDisplay();
  display.fillCircle(SCREEN_WIDTH/2, RADIO_2, RADIO_2, SSD1306_WHITE); 
  display.fillCircle(SCREEN_WIDTH/2, RADIO_2, RADIO_2/2, SSD1306_BLACK); 
  display.display();
}

void serioASorpresa() {
  serio();
  const int pasos = 30;
  const int umbral_fase = pasos * 0.6; // Punto de cambio entre fases
  
  for (int j = 0; j <= pasos; j++) {
    display.clearDisplay();
    
    if (j < umbral_fase) {
      // FASE 1: Los trazos horizontales se acortan hacia el centro
      int acortamiento = (RADIO_1 * j) / umbral_fase;
      
      for (int i = 0; i <= ANCHO_LINEA; i++) {
        display.drawLine(CENTRO_X_1 - RADIO_1 + acortamiento, CENTRO_Y_1 + i, 
                         CENTRO_X_1 + RADIO_1 - acortamiento, CENTRO_Y_1 + i, 
                         SSD1306_WHITE);
      }
      
    } else {
      // FASE 2: La línea se transforma en círculo y sube
      int pasos_fase2 = pasos - umbral_fase;
      int avance = j - umbral_fase;
      
      int pos_y = CENTRO_Y_1 - ((CENTRO_Y_1 - RADIO_2) * avance) / pasos_fase2;
      int radio_actual = 2 + ((RADIO_2 - 2) * avance) / pasos_fase2;
      int radio_interior = (RADIO_2 * avance) / (pasos_fase2 * 2);
      
      display.fillCircle(SCREEN_WIDTH/2, pos_y, radio_actual, SSD1306_WHITE);
      if (radio_interior > 0) {
        display.fillCircle(SCREEN_WIDTH/2, pos_y, radio_interior, SSD1306_BLACK);
      }
    }
    
    display.display();
    // delay(50);
  }
  
  sorpresa();
}

/////
void sorpresaASerio() {
  sorpresa();
  const int pasos = 30;
  const int umbral_fase = pasos * 0.6; // Punto de cambio entre fases
  
  for (int j = 0; j <= pasos; j++) {
    display.clearDisplay();
    
    if (j < umbral_fase) {
      // FASE 1: El círculo baja y se achica
      int avance = j;
      
      int pos_y = RADIO_2 + ((CENTRO_Y_1 - RADIO_2) * avance) / umbral_fase;
      int radio_actual = RADIO_2 - ((RADIO_2 - 2) * avance) / umbral_fase;
      int radio_interior = RADIO_2/2 - ((RADIO_2/2) * avance) / umbral_fase;
      
      display.fillCircle(SCREEN_WIDTH/2, pos_y, radio_actual, SSD1306_WHITE);
      if (radio_interior > 0) {
        display.fillCircle(SCREEN_WIDTH/2, pos_y, radio_interior, SSD1306_BLACK);
      }
      
    } else {
      // FASE 2: La línea se expande desde el centro hacia los extremos
      int pasos_fase2 = pasos - umbral_fase;
      int avance = j - umbral_fase;
      
      int acortamiento = RADIO_1 - (RADIO_1 * avance) / pasos_fase2;
      
      for (int i = 0; i <= ANCHO_LINEA; i++) {
        display.drawLine(CENTRO_X_1 - RADIO_1 + acortamiento, CENTRO_Y_1 + i, 
                         CENTRO_X_1 + RADIO_1 - acortamiento, CENTRO_Y_1 + i, 
                         SSD1306_WHITE);
      }
    }
    
    display.display();
    //delay(50);
  }
  
  serio();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  sonrie();
  delay(500);
  rieASerio();
  delay(500);
  serioATriste();
  delay(500);
  tristeASerio(); 
  delay(500);
  serioASorpresa();
  delay(500);
  sorpresaASerio();
  delay(500);
  serioARie();
  delay(500);
}
