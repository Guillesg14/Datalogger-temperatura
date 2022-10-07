#include <OneWire.h>                
#include <DallasTemperature.h>
#include <SD.h>
 
File myFile; 

OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
 
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

 
void setup() 
{

pinMode(8, OUTPUT);    
pinMode(7, OUTPUT);  
Serial.begin(9600);
sensors.begin();   //Se inicia el sensor
delay(100);
if (!SD.begin(4)) {
    return;
  }

}


void loop() 
{
    myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo

    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
    float temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
    delay(1000);
    if (myFile) 
          { 
            myFile.print("sensor1=");
            myFile.print(temp);
            myFile.println(",");
            myFile.close(); //cerramos el archivo
            digitalWrite(8,HIGH);
            
          }
     
     else 
          {
            digitalWrite(7, HIGH);
          }

   }
