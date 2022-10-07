int pinled = 5;
int pinboton = 3;
int valorboton = 0;
long millisanteriores = 0;
long intervalo = 1000;
int estadoled = HIGH;
void setup() {
  // put your setup code here, to run once:
pinMode(5, OUTPUT);
pinMode(3, INPUT);
}

void loop() {
valorboton = digitalRead(pinboton);
if(valorboton == HIGH){ 
unsigned long  millisactuales = millis();
  if(millisactuales - millisanteriores>intervalo) 
  {
    millisanteriores = millisactuales;
    if(estadoled ==LOW)
    {
      estadoled = HIGH;
    }
    else
    {
      (estadoled = LOW);
    }
    digitalWrite(pinled, estadoled);
  }
}

else
{
  digitalWrite(pinled, LOW);  
}

}
