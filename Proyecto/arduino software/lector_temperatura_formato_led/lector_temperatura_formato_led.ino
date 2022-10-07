#include <SD.h>

File myFile;

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
    digitalWrite(3, HIGH);
  }
  Serial.println("inicializacion exitosa");
  digitalWrite(2, HIGH);
}

void loop()
{
  myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo
  
  if (myFile) { 
        Serial.print("Escribiendo SD: ");
        int sensor1 = analogRead(0);

        myFile.print("Tiempo = ");
        myFile.print(millis());
        myFile.print(",temperatura = ");
        myFile.println(sensor1);
        
        myFile.close(); //cerramos el archivo


  } else {
    Serial.println("Error al abrir el archivo");
  }
  delay(100);
}
