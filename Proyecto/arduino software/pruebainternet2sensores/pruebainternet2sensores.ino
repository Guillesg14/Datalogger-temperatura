//*Programa realizado por Regata para tallerarduino.wordpress.com*/
/*Medición de temperatura mediante varios sensores 1-wire DS18B20+*/
 
#include <OneWire.h>
#include <DallasTemperature.h>
 
// DQ esta conectado al pin 10 de Arduino
#define ONE_WIRE_BUS 2
 
// Configuramos para comunicar con otros dispositivos 1-Wire
OneWire oneWire(ONE_WIRE_BUS);
 
// Indicamos el pin asignado al sensor 1-Wire a DallasTemperature 
DallasTemperature sensores(&oneWire);
 
int ledverde=11;  //indicamos que le led verde esta conectado en el pin 11 de Arduino
int ledrojo=12;  //indicamos que el led rojo esta conectado en el pin 12 del Arduino
float val=0; // variable donde guardaremos la temperatura leida del sensor
int i;  //variable que contiene el numero de sensores empleados en el caso de ser mas de 1
float tempmin=100;  //Variable donde guardamos la temperatura minima registrada
                    //Le pongo 100 por que en donde lo he probado no llega a esa temperatura
                    //y así puede coger el menor valor de temperatura que aparezca
float tempmax=0;    //Varibale donde guardamos la temperatura maxima registrada
 
void setup(void)
{
  //Indicamos ledverde y ledrojo como salidas  
  pinMode(ledverde,OUTPUT);
  pinMode(ledrojo,OUTPUT);
  // Iniciamos el puerto serie a 9600 baudios
  Serial.begin(9600);
  // Inicializamos la libreria
  sensores.begin();
  //Ponemos a 0 las salidas ledverde y ledrojo
  digitalWrite(ledverde,LOW);
  digitalWrite(ledrojo,LOW);
}
 
void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  float media=0;
  for(i=0;i<=1;i++)
  {
    sensores.requestTemperatures(); //Enviamos el comando para obtener la temperatura  
    Serial.print("Temperatura Sensor ");
    Serial.print(i);
    Serial.print(": ");
    float val =  sensores.getTempCByIndex(i); // Almacenamos la temperatura en la variable val
    media=media+val;  //Vamos sumando para poder calcular la media de las temperaturas
    Serial.println(val);  //Mostramos por puerto serie el valor de la temperatura leida
    if (val<tempmin)
      tempmin=val;
    if (val>tempmax)
      tempmax=val;
  }
    media=media/i;  //Calculamos la media de las temperaturas
    Serial.print("La temperatura media es: ");  //Mostramos la temperatura media de todas las temperaturas
    Serial.println(media);
    Serial.print("La temperatura minima registrada es: ");  //Mostramos la temperatura minima registrada
    Serial.println(tempmin);
    Serial.print("La temperatura maxima registrada es: ");  //Mostramos la temperatura maxima registrada
    Serial.println(tempmax);
    Serial.println();
    delay(1500);  //Esperamos 1500ms
}
