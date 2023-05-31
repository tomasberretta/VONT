// Incluimos las librerías
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include <iostream>
#include <stack>

using namespace std;

MDNSResponder mdns;

const char *ssid = "AndroidAP4FDD"; // Nombre de la red WIFI
const char *password = "Tomas123";  // Contraseña de la red WIFI

WiFiServer server(80);
String webpage = "";
String header = "";
WiFiClient client = server.available(); // Se conecta mediante WiFi conn la app y se fija si está disponible para enviar o recibir ir información.

// CONJUNTO 0
#define ENABLE0 5
#define IN01 32
#define IN02 33
#define ENC0A 13
#define ENC0B 14

// CONJUNTO 2
#define ENABLE2 22
#define IN21 2
#define IN22 12
#define ENC2A 16
#define ENC2B 17

// CONJUNTO 1
#define ENABLE1 0
#define IN11 19
#define IN12 18
#define ENC1A 4
#define ENC1B 23

// CONJUNTO 3
#define ENABLE3 25
#define IN31 26
#define IN32 27
#define ENC3A 21
#define ENC3B 15

// SENSOR INFRARROJO
#define sensinfDer 34  // derecha s4
#define sensinfIzq 23  // izquierda s2
#define sensinfCent 35 // centro s3

// FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-
// FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-
// FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-
// FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-

void iniciarWIFI()
{ // Función para conectar el ESP32 a la red WIFI

  Serial.print("Conectando a  ");
  Serial.println(ssid);
  // Conectamos el esp a la red wifi
  WiFi.begin(ssid, password);
  // Intentamos conectarnos a la red
  while (WiFi.status() != WL_CONNECTED)
  { // Imprimimos cuanodo ya estamos conectados
    delay(500);
    Serial.print(".");
  }
  // Si logramos conectarnos mostramos la ip a la que nos conectamos
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void setup()
{

  // Inicia el monitor serie
  Serial.begin(9600);

  // Definimos lo pines de los motores como OUTPUT para poder energizar los motores
  pinMode(IN01, OUTPUT);
  pinMode(IN02, OUTPUT);
  pinMode(IN21, OUTPUT);
  pinMode(IN22, OUTPUT);
  pinMode(IN11, OUTPUT);
  pinMode(IN12, OUTPUT);
  pinMode(IN31, OUTPUT);
  pinMode(IN32, OUTPUT);
  pinMode(ENABLE0, OUTPUT);
  pinMode(ENABLE2, OUTPUT);
  pinMode(ENABLE1, OUTPUT);
  pinMode(ENABLE3, OUTPUT);

  // Definimos los pines de los sensores infrarrojos
  pinMode(sensinfDer, INPUT);
  pinMode(sensinfIzq, INPUT);
  pinMode(sensinfCent, INPUT);

  // Energizamos los PUENTE H para poder cambiar la direccion de los motores
  digitalWrite(ENABLE0, HIGH);
  digitalWrite(ENABLE2, HIGH);
  digitalWrite(ENABLE1, HIGH);
  digitalWrite(ENABLE3, HIGH);

  iniciarWIFI();
}

// FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO -
// FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO -
// FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO -
// FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO -

// Establecemos todas las funciones de movimiento funciones de movimiento, cada una envía una señal a ciertos pines analógicos para que se mueva
// o gire en la dirección pretenida según los vectores definidos.
void ADELANTE()
{
  analogWrite(IN01, 100);
  analogWrite(IN02, 0);

  analogWrite(IN11, 100);
  analogWrite(IN12, 0);

  analogWrite(IN21, 100);
  analogWrite(IN22, 0);

  analogWrite(IN31, 100);
  analogWrite(IN32, 0);
}

void ATRAS()
{
  analogWrite(IN01, 0);
  analogWrite(IN02, 150);

  analogWrite(IN11, 0);
  analogWrite(IN12, 150);

  analogWrite(IN21, 0);
  analogWrite(IN22, 150);

  analogWrite(IN31, 0);
  analogWrite(IN32, 150);
}

void ROTACION_HORARIA()
{
  analogWrite(IN01, 0);
  analogWrite(IN02, 140); // de 255 a 190

  analogWrite(IN11, 140); // de 255 a 190
  analogWrite(IN12, 0);

  analogWrite(IN21, 0);
  analogWrite(IN22, 140); // de 255 a 190

  analogWrite(IN31, 140); // de 255 a 190
  analogWrite(IN32, 0);
}

void ROTACION_ANTIHORARIA()
{
  analogWrite(IN01, 140); // de 255 a 190
  analogWrite(IN02, 0);

  analogWrite(IN11, 0);
  analogWrite(IN12, 140); // de 255 a 190

  analogWrite(IN21, 140); // de 255 a 190
  analogWrite(IN22, 0);

  analogWrite(IN31, 0);
  analogWrite(IN32, 140); // de 255 a 190
}

void IZQUIERDA()
{
  analogWrite(IN01, 190);
  analogWrite(IN02, 0);

  analogWrite(IN11, 0);
  analogWrite(IN12, 190);

  analogWrite(IN21, 0);
  analogWrite(IN22, 190);

  analogWrite(IN31, 190);
  analogWrite(IN32, 0);
}

void DERECHA()
{
  analogWrite(IN01, 0);
  analogWrite(IN02, 190);

  analogWrite(IN11, 190);
  analogWrite(IN12, 0);

  analogWrite(IN21, 190);
  analogWrite(IN22, 0);

  analogWrite(IN31, 0);
  analogWrite(IN32, 190);
}

void FRENAR()
{

  analogWrite(IN01, 0);
  analogWrite(IN02, 0);

  analogWrite(IN11, 0);
  analogWrite(IN12, 0);

  analogWrite(IN21, 0);
  analogWrite(IN22, 0);

  analogWrite(IN31, 0);
  analogWrite(IN32, 0);
}

bool followingLine = false; // variable para mantener el loop del seguimiento de linea
bool lastDirectionClockwise = false;
stack<bool> rotationMovements;

int CENTER = 0;
int LEFT = 1;
int RIGHT = 2;

int sensorPins[] = {sensinfCent, sensinfIzq, sensinfDer};

bool sensorValues[] = {false, false, false};

int arbitraryRotationCount = 30;

void readSensors()
{
  for (int i = 0; i < sizeof(sensorPins) / sizeof(sensorPins[0]); i++)
  {
    if (
        digitalRead(sensorPins[i]) == HIGH) // si el sensor lee HIGH lo tomamos como true, es decir leyó una línea
    {
      sensorValues[i] = true;
    }
    else
    {
      sensorValues[i] = false;
    }
  }
  if (sensorValues[LEFT])
  {
    lastDirectionClockwise = false;
  }
  else if (sensorValues[RIGHT])
  {
    lastDirectionClockwise = true;
  }
}

void printSensors()
{
  Serial.println("--------------------------");
  if (sensorValues[RIGHT])
  {
    Serial.println("Derecha: Blanco");
  }
  else
  {
    Serial.println("Derecha: Negro");
  }
  if (sensorValues[CENTER])
  {
    Serial.println("Centro: Blanco");
  }
  else
  {
    Serial.println("Centro: Negro");
  }
  if (sensorValues[LEFT])
  {
    Serial.println("Izquierda: Blanco");
  }
  else
  {
    Serial.println("Izquierda: Negro");
  }
  Serial.println("--------------------------");
}

void performOneRotationMovement(bool clockwise){
  if (clockwise)
    {
      ROTACION_HORARIA();
      delay(50);
      FRENAR();
    }
    else
    {
      ROTACION_ANTIHORARIA();
      delay(50);
      FRENAR();
    }
}

void undoRotation()
{
  while (rotationMovements.size() != 0)
  {
    bool rotationToPerform = rotationMovements.top();
    performOneRotationMovement(!rotationToPerform);
    delay(200);
    rotationMovements.pop();
  }
}

bool rotate(bool clockwise, int rotationCounter) // rota hacia algun sentido con un contador arbitrario (para que no rote 180 y vuelva por donde vino)
{

  while (!sensorValues[CENTER]) // rota mientras no haya detectado la linea con el sensor del medio
  {
    clockwise = lastDirectionClockwise;
    if (rotationCounter == 0) // llego al limite de rotacion arbitraria
      break;
    else
    {
      if (clockwise || sensorValues[RIGHT])
      {
        performOneRotationMovement(true);
        rotationMovements.push(true);
      }
      else if (!clockwise || sensorValues[LEFT])
      {
        performOneRotationMovement(false);
        rotationMovements.push(false);
      }
      rotationCounter--; // resta al contador arbitrario
    }
    readSensors();
    printSensors();
  }
  return rotationCounter != 0; // devuelve si terminó por haber encontrado la linea
}

void FOLLOW_LINE()
{
  while (followingLine)
  {
    readSensors();
    printSensors();
    if (!sensorValues[CENTER]) // no encuentra la linea en el centro
    {
      FRENAR();
      if (!sensorValues[LEFT] && !sensorValues[RIGHT]) // no encuentra la linea en la izquierda ni en la derecha
      {
        bool foundLine = rotate(lastDirectionClockwise, arbitraryRotationCount); // busca sentido antihorario
        if (foundLine)
          continue; // encontro la linea, asi que sigue con el loop
        else
        {
          undoRotation();
          foundLine = rotate(!lastDirectionClockwise, arbitraryRotationCount); // realiza la busqueda para el otro lado
          if (foundLine)
            continue; // encontro la linea, asi que sigue con el loop
          else
          {
            followingLine = false; // no encontro la linea, asi que finaliza el loop de seguimiento de la linea
            return;
          }
        }
      }
      else if (sensorValues[RIGHT]) // si encuentra la linea a la derecha
      {
        readSensors();
        printSensors();
        while (!sensorValues[CENTER]) // rota mientras no encuentre la linea con el sensor del medio
        {
          performOneRotationMovement(true);
          readSensors();
          printSensors();
          if (sensorValues[LEFT]){
            performOneRotationMovement(false);
            break;
          }
        }
        FRENAR();
      }
      else if (sensorValues[LEFT]) // si encuentra la linea a la izquierda
      {
        readSensors();
        printSensors();
        while (!sensorValues[CENTER]) // rota mientras no encuentre la linea con el sensor del medio
        {
          performOneRotationMovement(false);
          readSensors();
          printSensors();
          if (sensorValues[RIGHT]){
            performOneRotationMovement(true);
            break;
          }
        }
        FRENAR();
      }
    }
    else
    {
      ADELANTE(); // sigue para adelante mientras la linea este en el centro
    }
  }
}

void casos(String header2)
{
  Serial.println("ESTE ES EL HEADER BIENVENIDOS MUCHAS GRACIAS"); // Manera de identificar cual es el header, es decir la IP que recibe el ESP32
  Serial.println(header2);

  char str_valor = header2[5]; // Guarda en str_valor el caracter que recibe de la app.
  Serial.println(str_valor);
  String input = "";
  input = str_valor;

  Serial.print("Input recibido: ");
  Serial.println(input); // Imprime el dato recibido en el monitor serie para un mejor comprension
  // En función del INPUT recibido por la app, llamamos a la funcion de movimiento necesaria
  if (input == "W") // Llama a la funcion que corresponde a Avanzar
  {

    ADELANTE();
  }
  else if (input == "S") // Llama a la funcion que corresponde a ir hacia atras
  {
    ATRAS();
  }
  else if (input == "A") // Llama a la funcion que corresponde a moverese a la izquierda
  {
    IZQUIERDA();
  }
  else if (input == "D") // Llama a la funcion que corresponde a mover a la derecha
  {
    DERECHA();
  }
  else if (input == "E") // Llama a la funcion que corresponde a rotar sobre su propio eje en sentido horario
  {
    ROTACION_HORARIA();
  }
  else if (input == "Q") // Llama a la funcion que corresponde a rotar sobre su propio eje en sentido anti-horario
  {
    ROTACION_ANTIHORARIA();
  }
  else if (input == "F") // Llama a la funcion que corresponde a frenar
  {
    FRENAR();
  }
  else if (input == "L") // Llama a la funcion que al seguimiento de la linea
  {
    followingLine = true; // Settea la variable del loop en true
    rotationMovements.empty();
    FOLLOW_LINE();        // Inicia el loop de seguimiento
  }
  else
  {
    Serial.println("VALOR INCORRECTO"); // En caso de que input contenga un caracter no contemplado, devuelve el aviso de valor incorrecto.
  }
}

void parametrosWiFi()
{                              // Esta es la función principal, que se encarga de traer la IP desde la app y comunicarsela al VONT.
  client = server.available(); // Se conecta mediante WiFi conn la app y se fija si está disponible para enviar o recibir ir información.
  if (client)
  {

    String currentline = ""; // Para guardar la info que llega del client

    while (client.connected())
    { // Lleva a cabo las siguientes instrucciones siempre y cuando la app se mantenga conectada al ESP#"32
      if (client.available())
      {                         // Ejecuta en función de si la app está disponible para enviar o recibir info
        char c = client.read(); // En caso de que esté disponible, lee la IP y la almacena en la variable c.
        Serial.write(c);        // Escribe la IP leída para realizar seguimiento
        header += c;

        if (c == '\n')
        { // Revisa si la cadena de la IP terminó.

          if (currentline.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            break; // Salir del ciclo while:
          }
          else
          { // si tiene una nueva línea, borra currentLine:
            currentline = "";
          }
        }
        else if (c != '\r')
        { // Si se vuelva al inicio de la cadena, anexa c a currenline para no perderlo.
          currentline = +c;
        }
      }
    }

    casos(header); // Con el valor de header corre la función casos para comunicarse y mover al VONT en función del carácter dado.
    header = "";   // Vacía la variable header para poder volver a correr esta función
    client.stop(); // Y Corta comunicación con la app.
  }
}

void loop()
{
  parametrosWiFi(); // Corre la función parametrosWiFi, que es la que se encarga de la comunicación y con la app y movimiento del VONT en loop.
}
