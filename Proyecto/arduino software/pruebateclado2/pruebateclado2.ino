#include <Keypad.h>
#include <Wire.h>
#include <TimerOne.h>
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <SD.h>
#include <LiquidCrystal.h>
#include <Rtc_Pcf8563.h>


const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'E','0','P','D'}
};
byte rowPins[ROWS] = {30,32,34,36}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {38,40,42,44}; //Columnas (pines del 5 al)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );




 

Rtc_Pcf8563 rtc;

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

File myFile; 
OneWire ourWire(2);                       //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire);      //Se declara una variable u objeto para nuestro sensor

int pinled = 5;                           //led leer temperaturas
int pinled2 = 6;                          //led pausa lectura
int pinboton = 9;                         //pin interruptor inicio/parar tomas
int valorboton = 0;       
long intervalo = 5000;                   
long millisanteriores = 0;                //variable para intervalos
long intervalo2 = 100;
long millisanteriores2 = 0;
long intervalo4h  = 10000;               //intervalo entre grabar medidas
long millisanteriores3 = 0;
long intervalo3 = 500;
float tempmin=100;
float tempmax=0;
float val=0;
int i;
int s;
int a=0;
void setup() 
{

pinMode(5, OUTPUT);       //
pinMode(6, OUTPUT);       //pines leds y botones
pinMode(9, INPUT);        //
pinMode(7, OUTPUT);

delay(1000);              //evitar error en primera lectura
Serial.begin(9600);
sensors.begin();          //Se inicia el sensor
lcd.begin(16, 2);         //se inicia la antalla a 16x2

if (!SD.begin(4))         //pin 4 como pin de comunicacion(NO USAR)
{
 return;
}

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("INICIANDO");
delay(intervalo);
lcd.clear();
/////////////////////////////////////////////////////////////////////////////////////////////

  //rtc.initClock();
  /* dianumero, diasemana, mes, siglo(0siempre), año */
  
 //rtc.setDate(25, 4, 5, 0, 17);
  /* hr, min, sec */
  //rtc.setTime(21, 15, 40);                                        /////poner en hora el reloj
  /* el pin de la allarma es low cuando ocurre
   * min, hr, dia, diasemana 
   * 99 = nno hay valor de alarma
   */
  //rtc.setAlarm(16, 99, 99, 99);
//////////////////////////////////////////////////////////////////////////////////////////
}
void loop() 
{


char key = keypad.getKey();
switch(key)
{ 
      case 'E':
        { 
    digitalWrite(7, LOW);         
    digitalWrite(pinled2, LOW);                                 //apagamos led de pausa
    digitalWrite(pinled, HIGH);                                 //encendemos led de lectura

      myFile = SD.open("datalog.txt", FILE_WRITE);                //abrimos  el archivo      
     if (myFile) 
          { 
            
           float media=0;
           for(i=0;i<=1;i++)
            {
              sensors.requestTemperatures();                     //Enviamos el comando para obtener la temperatura  
              float val =  sensors.getTempCByIndex(i);           // Almacenamos la temperatura en la variable val
              media=media+val;                                   //Vamos sumando para poder calcular la media de las temperaturas
              if (val<tempmin)
              tempmin=val;
              if (val>tempmax)
              tempmax=val;            
              unsigned long millisactuales2 = millis();          //actualizamos el contador actual
 
              if(millisactuales2 - millisanteriores2>intervalo2) //diferencia del intervalo marcado
                 {
                  millisanteriores2 = millisactuales2;
                 }
            }
            media=media/i;                                        //Calculamos la media de las temperaturas
              
                        lcd.clear();
                        lcd.setCursor(0, 0);
                        lcd.print(rtc.formatTime());
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            
            
                    unsigned long millisactuales3 = millis();                 //actualizamos el contador actual 
              if(millisactuales3 - millisanteriores3>intervalo4h)         //diferencia del intervalo marcado
              {
                    millisanteriores3 = millisactuales3;
                      myFile.print(rtc.formatTime());
                      myFile.print("  ");
                      myFile.print(rtc.formatDate());
                      myFile.print(" ; ");
                       unsigned long millisactuales2 = millis();                       //actualizamos el contador actual 
                        if(millisactuales2 - millisanteriores2>intervalo2)              //diferencia del intervalo marcado
                            {
                              millisanteriores2 = millisactuales2;
                            }
                      
                     for(s=0;s<=1;s++)
                       {
                             sensors.requestTemperatures();                                  //Enviamos el comando para obtener la temperatura  
                             float val =  sensors.getTempCByIndex(s);                        // Almacenamos la temperatura en la variable val
                              myFile.print(val);                                              //Mostramos por puerto serie el valor de la temperatura leida
                              myFile.print(" ; ");           
                              unsigned long millisactuales2 = millis();                       //actualizamos el contador actual 
                              if(millisactuales2 - millisanteriores2>intervalo2)              //diferencia del intervalo marcado
                                 {
                                  millisanteriores2 = millisactuales2;
                                 }
                                                                    
                         }
                            myFile.println(" ");  
              }         

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
            
            myFile.close();                             //cerramos el archivo
        }
break;

      case 'P':
      {
        digitalWrite(7, LOW);
         digitalWrite(pinled2, HIGH);                          //encendemos el led de pausa                    
  digitalWrite(pinled, LOW);                            //apagamos el led de lectura
unsigned long millisactuales2 = millis();               //actualizamos el contador actual 
   if(millisactuales2 - millisanteriores2>intervalo2)   //diferencia del intervalo marcado
     {
      millisanteriores2 = millisactuales2;
      digitalRead(pinboton);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PAUSA");
     }    
      }
break;

//default:
digitalWrite(7, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("a la espera");
  unsigned long millisactuales2 = millis();          //actualizamos el contador actual
  if(millisactuales2 - millisanteriores2>intervalo3) //diferencia del intervalo marcado
   {
      millisanteriores2 = millisactuales2;
   }
   
break;
}

}
