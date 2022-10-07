#include <OneWire.h>                
#include <DallasTemperature.h>
#include <SD.h>

  
const int interruptor = 4;
int value = 0;
File myFile; 

OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
 
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

 
void setup() 
{
pinMode(interruptor, INPUT);
pinMode(6, OUTPUT);    
pinMode(7, OUTPUT);  
pinMode(8, OUTPUT);
delay(1000);
Serial.begin(9600);
sensors.begin();   //Se inicia el sensor

if (!SD.begin(4)) {
    return;
  }


}


 
void loop() 
{
value = digitalRead(interruptor);

if (value == HIGH)
  {
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
            digitalWrite(7,HIGH);
          }
     
     else 
          {
            digitalWrite(6, HIGH);
            delay(10);
          }

  }

else
{
  digitalWrite(8, HIGH);
  delay(10);
}

}

