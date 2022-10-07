#include <TimerOne.h>
const int led = 13;  // the pin with a LED
int ledState = LOW;    // El LED empieza apagado
volatile unsigned long blinkCount = 0; // Somos muy obedientes

void setup(void)
{
  pinMode(led, OUTPUT);
  Timer1.initialize(250000);         // Dispara cada 250 ms
  Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la asocia a ISR_Blink
  Serial.begin(9600);
  
}

void ISR_Blink()
{
  ledState = !ledState ;
  blinkCount++    ;     // Para saber cuantas veces se enciende el LED
}

void loop(void)
{
  unsigned long N;  // holds a copy of the blinkCount
  digitalWrite(led, ledState);
    
  noInterrupts();
  N = blinkCount;
  interrupts();

  Serial.print("blinkCount = ");
  Serial.println(N);
  delay(100);
}
