#include <SD.h>

File myFile;
void setup()
{
  Serial.begin(9600);
  Serial.print(" iniciando sd ");
  if (!SD.begin(4)) {
    Serial.println(" No se pudo inicializar ");
    return;
  }
  Serial.println(" inicializacion exitosa ");
}

void loop()
{
  myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo
  
  if (myFile) { 
  
        int sensor1 = analogRead(0);

        myFile.print(" tiempo = ");
        myFile.print(millis());
        myFile.print(" ,temperatura = ");
        myFile.println(sensor1);
        delay(100);
        
  }
  
  else {
    Serial.println("Error al abrir el archivo");
  }
  myFile.close(); //cerramos el archivo
  delay(100);
}

