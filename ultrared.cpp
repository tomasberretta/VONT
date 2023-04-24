#include <Arduino.h>

// Definimos los pines del sensor de ultrasonido
const int trigPin = 1;  // Pin de transmisión (Trig)
const int echoPin = 36;  // Pin de recepción (Echo)

// Definimos variables para almacenar la distancia medida
long duration;  // Duración de la señal de ultrasonido
int distance;   // Distancia medida en centímetros

void setup() {

  // Definimos los pines del ECHO y TRIGGER, como INPUT y OUTPUT respectivamente
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicializamos el puerto serial
  Serial.begin(9600);
}

void loop() {

  // Generar un pulso de 10 microsegundos en el pin Trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Medimos la duración de la señal de ultrasonido en llegar al ECHO
  duration = pulseIn(echoPin, HIGH);

  // Convertimos la duración a distancia en centímetros
  distance = duration * 0.034 / 2;

  // Imprimimos la distancia medida en el puerto serial para un mejor compresion
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Esperamos un segundo antes de medir otra vez
  delay(1000);
}