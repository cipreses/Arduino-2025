
#include <Servo.h>

Servo Lefttop,Righttop,Leftbottom,Rightbottom, Servoloco1, Servoloco2;

// Face should be in front of you
/*
                 --------------- 
                |     O   O     |
                |---------------|
Lefttop =>      |               |    <= Righttop
                 --------------- 
                    ||     ||
Leftbottom =>     -----   ------     <= Rightbottom
                 |-----   ------|


Servoloco 1 y servoloco 2 sirven para mover servos en todo su recorrido y probar movimienros                  
*/

int pos = 90;    // variable to store the servo position
int posloco = 0;
//make sure all motors are at 90 degree


void setup() {
  Lefttop.attach(8);  // attaches the servo on pin 8 to the servo object
  Righttop.attach(9);  // attaches the servo on pin 9 to the servo object
  Leftbottom.attach(10);  // attaches the servo on pin 10 to the servo object
  Rightbottom.attach(11);  // attaches the servo on pin 11 to the servo object
  Servoloco1.attach(12); //Lo mueve como loco.
  Servoloco2.attach(13); //Lo mueve como loco.

}

void loop() {
  
    Lefttop.write(pos);           
    Righttop.write(pos);              
    Leftbottom.write(pos);              
    Rightbottom.write(pos);  

  for (posloco = 0; posloco <= 180; posloco += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Servoloco1.write(posloco);              // tell servo to go to position in variable 'pos'
    Servoloco2.write(posloco);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (posloco = 180; posloco >= 0; posloco -= 1) { // goes from 180 degrees to 0 degrees
    Servoloco1.write(posloco);              // tell servo to go to position in variable 'pos'
    Servoloco2.write(posloco);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }


}
