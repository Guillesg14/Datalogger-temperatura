#include <OneWire.h>                
#include <DallasTemperature.h>
#include <SD.h>

File myFile; 
OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

int pinled = 5;            //led leer temperaturas
int pinled2 = 6;           //led pausa lectura
int pinboton = 7;          //pin interruptor inicio/parar tomas
int valorboton = 0;       
long intervalo = 1000;     //intervalo 1 seg entre medidas
long millisanteriores = 0; //variable para intervalos

float tempmin=100;
float tempmax=0;
float val=0;
int i;
void setup() 
{

pinMode(5, OUTPUT);       //
pinMode(6, OUTPUT);       //pines leds y botones
pinMode(7, INPUT);        //


delay(1000);              //evitar error en primera lectura
Serial.begin(9600);
sensors.begin();          //Se inicia el sensor

if (!SD.begin(4))         //pin 4 como pin de comunicacion(NO USAR)
{
 return;
}
}


void loop() 
{
    
  valorboton = digitalRead(pinboton);               //leemos el pulsador
if (valorboton == HIGH)                           //si el valor es alto
  {
    myFile = SD.open("datalog.txt", FILE_WRITE);    //abrimos  el archivo
    digitalWrite(pinled2, LOW);                     //apagamos led de pausa
    digitalWrite(pinled, HIGH);                     //encendemos led de lectura
    unsigned long millisactuales = millis();        //actualizamos el contador actual 
    if(millisactuales - millisanteriores>intervalo) //diferencia del intervalo marcado
     {
      millisanteriores = millisactuales;
     if (myFile) 
          { 
            float media=0;
              myFile.print(" hora de medida ");
              
              myFile.print("; ");
           for(i=0;i<=1;i++)
            {
              sensors.requestTemperatures(); //Enviamos el comando para obtener la temperatura  

              float val =  sensors.getTempCByIndex(i); // Almacenamos la temperatura en la variable val
              media=media+val;  //Vamos sumando para poder calcular la media de las temperaturas
              myFile.print(val);  //Mostramos por puerto serie el valor de la temperatura leida
              myFile.print(" ; ");
                           
              if (val<tempmin)
              tempmin=val;
              if (val>tempmax)
              tempmax=val;
              delay(100);
            }
            myFile.println(" ");  
                      //quite delay 1500
            }
            myFile.close();                       //cerramos el archivo
           
          }
    }
 else                                             //si el valor es bajo
 {
  digitalWrite(pinled2, HIGH);                    //encendemos el led de pausa                    
  digitalWrite(pinled, LOW);                     //apagamos el led de lectura
 }
}
