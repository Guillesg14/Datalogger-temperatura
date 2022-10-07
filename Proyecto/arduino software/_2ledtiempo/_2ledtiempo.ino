int pinled = 3;           
int pinled2 = 5;
int pinboton = 2;
int valorboton = 0;
long millisanteriores = 0;      
long millisanteriores2 = 0;
long intervalo = 1000;         
long intervalo2 = 2000;
int estadoled = HIGH;           
int estadoled2 = HIGH;

void setup() {


pinMode(5, OUTPUT);            
pinMode(3, OUTPUT);
pinMode(2, INPUT);
}

void loop() {
valorboton = digitalRead(pinboton);
if(valorboton == HIGH)
{ 
  digitalWrite(pinled2, LOW);
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
unsigned long  millisactuales = millis();
  if(millisactuales - millisanteriores > intervalo2) 
  {
    millisanteriores = millisactuales;
    if(estadoled2 ==LOW)
    {
      estadoled2 = HIGH;
    }
    else
    {
      (estadoled2 = LOW);
    }
    digitalWrite(pinled2, estadoled2);
  }
} 
}
