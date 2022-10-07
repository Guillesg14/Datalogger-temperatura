#include <OneWire.h>                
#include <DallasTemperature.h>
#include <SD.h>

 
File myFile; 

OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
 
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

void setup() 
{

pinMode(8, OUTPUT);    
pinMode(5, OUTPUT);  

delay(1000);
Serial.begin(9600);
sensors.begin();   //Se inicia el sensor

if (!SD.begin(4)) {
    return;
  }

}


void loop() 
{

              digitalWrite(8, HIGH);
            delay(100);
            digitalWrite(8, LOW);

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

          }
     
     else 
          {
            digitalWrite(5, HIGH);
            delay(10);
          }

}
