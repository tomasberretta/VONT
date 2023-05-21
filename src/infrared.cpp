#include <Arduino.h>

// Definimos los pines digitales de los sensores que utilizaremos para el sensor INFRARROJO
// Utilizaremos los pines digitales 23 para el S2 y 21 para el S3
// El sigueinte codigo funciona solamente para uno de los dos sensores, en este caso el S2
// En el caso de necesitar el S3, repetir el procedimiento

#define sensinfDer 34 // derecha s4 
#define sensinfIzq 23 // izquierda s2 
#define sensinfCent 35 // centro s3 


void setup() {

  // Inciamos el monitor serial
  Serial.begin(9600);
 
  // Definimos el pin del sensor como INPUT para poder recibir la señar
  pinMode(sensinfDer, INPUT); 
  pinMode(sensinfIzq, INPUT);
  pinMode(sensinfCent, INPUT);
}

void loop() {  

// Verificamos que no se esté enviando señales. En ese caso la luz del sensor estara apagada y significa que esta "Lejos".
// Mostramos en el monitor serie lo que esta sucediendo para una myor comprension 

if (digitalRead(sensinfDer) == LOW) { // blanco es LOW
  Serial.println("Blancho Derecha");
} 
if (digitalRead(sensinfDer) == HIGH){
  Serial.println("Negro Derecha");
}
if (digitalRead(sensinfIzq) == LOW) {
  Serial.println("Blanco Izquierda");
}
if (digitalRead(sensinfIzq) == HIGH){
  Serial.println("Negro Izquierda");
}
if (digitalRead(sensinfCent) == LOW) {
  Serial.println("Blanco Centro");
}
if (digitalRead(sensinfCent) == HIGH){
  Serial.println("Negro Centro");
}
delay(1000);
Serial.println("-------------------------------------");
}


/*

//Mientras el sensor del medio detecta la linea sigue avanzando hacia delante
/*En caso de que el sensore del medio deje de detectar

if(not medio){
    if(not left && not right){
        while(not medio){
            rota derecha mientras que la rotacion sea menor a 90
            
            if(rotacion a derecha es mayor o igual a 90){
                vuelvo a centro y empiezo a rotar para la izquierda 
                if(rotacion a izquierda es mayor o igual a 90){
                    error ;)
                }
            }
        }
    }else if (yes right){
        rota para la derecha hasta que sensor del medio vuelve a detectar la linea
    }else if (yes left){
        rota para la izquierda hasta que sensor del medio vuelve a detectar la linea

    }
}else{
    avanza hacia adelante
}

*/