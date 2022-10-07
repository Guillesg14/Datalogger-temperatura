const int pin_led = 13;
int estado_led = LOW;             // estado_led usado para configurar el LED
long millis_anteriores = 0;        //  Almacenara la ultima vez que el LED fue actualizado
long intervalo = 1000;           // intervaloo en el cual parpadea (millisegundos)
int pin_interruptor = 7;
int value = 0;
void setup() {
  
  pinMode(pin_led, OUTPUT);  
  pinMode(pin_interruptor, INPUT); 
}

void loop()
{
value = digitalRead(pin_interruptor);
if(value == LOW);
{

   unsigned long millis_actuales = millis();
 
  if(millis_actuales - millis_anteriores > intervalo) 
  {
    // almacena la ultima vez que parpadeo el LED
    millis_anteriores = millis_actuales;  

    // si el LED esta apagado, entonces se prende o viceversa.
    if (estado_led == LOW) 
    {
      estado_led = HIGH;
    } 
    else 
    {
      estado_led = LOW;
    }
    // configura el LED con la variable estado_led
    digitalWrite(pin_led, estado_led);
  }
}
value = digitalRead(pin_interruptor);
if(value == HIGH);
{
  estado_led = HIGH;
  digitalWrite(pin_led, estado_led);
}

}


