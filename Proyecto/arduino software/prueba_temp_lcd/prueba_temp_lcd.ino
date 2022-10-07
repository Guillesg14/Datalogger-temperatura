#include <OneWire.h>                
#include <DallasTemperature.h>
#include <SD.h>
unsigned long intervalo=1000;
unsigned long millisprevios=0;
 
File myFile; 

OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
 
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

 
void setup() 
{

pinMode(4, OUTPUT);    
pinMode(5, OUTPUT);  
unsigned long millisactuales = millis();
Serial.begin(9600);
sensors.begin();   //Se inicia el sensor

if (!SD.begin(4)) {
    return;
  }

}


void loop() 
{
  
unsigned long millisactuales = millis();

    myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo

    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
    float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

    
if ((unsigned long)(millisactuales - millisprevios) >= intervalo) {

              
    if (myFile) 
          { 
            myFile.print("sensor1=");
            myFile.print(temp);
            myFile.println(",");
            myFile.close(); //cerramos el archivo
            digitalWrite(4,HIGH);
          }
     
     else 
          {
            digitalWrite(5, HIGH);
          }
millisprevios= millis();
   }
}
