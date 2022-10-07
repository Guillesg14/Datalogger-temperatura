#include <OneWire.h>                
#include <DallasTemperature.h>
#include <SD.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
String texto_fila = "Temperatura Media";

File myFile; 
OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

int pinled = 5;            //led leer temperaturas
int pinled2 = 6;           //led pausa lectura
int pinboton = 9;          //pin interruptor inicio/parar tomas
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
pinMode(9, INPUT);        //


delay(1000);              //evitar error en primera lectura
Serial.begin(9600);
sensors.begin();          //Se inicia el sensor
lcd.begin(16, 2);         //se inicia la antalla a 16x2

if (!SD.begin(4))         //pin 4 como pin de comunicacion(NO USAR)
{
 return;
}
}


void loop() 
{
  int tam_texto=texto_fila.length();

  valorboton = digitalRead(pinboton);               //leemos el pulsador
if (valorboton == HIGH)                             //si el valor es alto
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
             media=media/i;  //Calculamos la media de las temperaturas
                           lcd.setCursor(0, 0);
              lcd.print("T. Media:");
              lcd.setCursor(0, 1);
              lcd.print("-");
              lcd.setCursor(2, 1);
              lcd.print(tempmin);
              lcd.setCursor(11, 0);
              lcd.print(media);
              lcd.setCursor(9, 1);
              lcd.print("+");
              lcd.setCursor(11, 1);
              lcd.print(tempmax);
            
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
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PAUSA");
  delay(100);
 }
}
