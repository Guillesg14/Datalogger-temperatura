#include <Keypad.h>


const byte ROWS = 4;
const byte COLS = 4;

byte rowPins[ROWS] = {30,32,34,36}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {38,40,42,44}; //Columnas (pines del 5 al)

char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'E','0','P','D'}
};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );




void setup() {
  Serial.begin(9600);

}

void loop() {
char key = keypad.getKey();
if (key !=0)
Serial.print(key); 

}
