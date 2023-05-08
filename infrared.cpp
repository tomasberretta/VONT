#include <Arduino.h>

// Definimos los pines digitales de los sensores que utilizaremos para el sensor INFRARROJO
// Utilizaremos los pines digitales 23 para el S2 y 21 para el S3
// El sigueinte codigo funciona solamente para uno de los dos sensores, en este caso el S2
// En el caso de necesitar el S3, repetir el procedimiento

// #define sensinf1 23 
#define sensinf1 39 


void setup() {

  // Inciamos el monitor serial
  Serial.begin(9600);
 
  // Definimos el pin del sensor como INPUT para poder recibir la señar
  pinMode(sensinf1, INPUT); 
}

void loop() {  

// Verificamos que no se esté enviando señales. En ese caso la luz del sensor estara apagada y significa que esta "Lejos".
// Mostramos en el monitor serie lo que esta sucediendo para una myor comprension 
if (digitalRead(sensinf1) == LOW) {
  Serial.println("lejos");
}
else {
  Serial.println("cerca");
}
delay(1000);
Serial.println("vuelta loop");
}