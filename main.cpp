//Incluimos las librerías
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HardwareSerial.h> 
#include <Arduino.h>
#include <iostream>

MDNSResponder mdns;

const char* ssid = "iPhone de Juana (2)"; //Nombre de la red WIFI
const char* password = "hola1234"; //Contraseña de la red WIFI

WiFiServer  server(80);
String webpage = "";
String header = "";

//CONJUNTO 0 
#define ENABLE0 5
#define IN01 32
#define IN02 33
#define ENC0A 13
#define ENC0B 14

//CONJUNTO 2
#define ENABLE2 22
#define IN21 2
#define IN22 12
#define ENC2A 16
#define ENC2B 17

//CONJUNTO 1
#define ENABLE1 0
#define IN11 19
#define IN12 18
#define ENC1A 4
#define ENC1B 23

//CONJUNTO 3
#define ENABLE3 25
#define IN31 26
#define IN32 27
#define ENC3A 21
#define ENC3B 15

//FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-
//FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-
//FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-
//FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-FUNCIONES-

void iniciarWIFI(){ //Función para conectar el ESP32 a la red WIFI

  Serial.print("Conectando a  ");
  Serial.println(ssid);
  //Conectamos el esp a la red wifi
  WiFi.begin(ssid, password);
  //Intentamos conectarnos a la red
  while (WiFi.status() != WL_CONNECTED) { //Imprimimos cuanodo ya estamos conectados
    delay(500);
    Serial.print(".");
  }
  //Si logramos conectarnos mostramos la ip a la que nos conectamos
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
 }

void setup() {

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

  // Energizamos los PUENTE H para poder cambiar la direccion de los motores
  digitalWrite(ENABLE0, HIGH);
  digitalWrite(ENABLE2, HIGH);
  digitalWrite(ENABLE1, HIGH);
  digitalWrite(ENABLE3, HIGH);

  iniciarWIFI();
}

//FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - 
//FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - 
//FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - 
//FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - FUNCIONES MOVIMIENTO - 

// Establecemos todas las funciones de movimiento funciones de movimiento, cada una envía una señal a ciertos pines analógicos para que se mueva
// o gire en la dirección pretenida según los vectores definicdos.
void ADELANTE()  { 
  analogWrite(IN01, 150);
  analogWrite(IN02, 0); 

  analogWrite(IN11, 150); 
  analogWrite(IN12, 0);

  analogWrite(IN21, 150);
  analogWrite(IN22, 0);

  analogWrite(IN31, 150); 
  analogWrite(IN32, 0);
}

void ATRAS() {
  analogWrite(IN01, 0); 
  analogWrite(IN02, 150);

  analogWrite(IN11, 0); 
  analogWrite(IN12, 150);

  analogWrite(IN21, 0);
  analogWrite(IN22, 150);

  analogWrite(IN31, 0); 
  analogWrite(IN32, 150);
}

void ROTACION_HORARIA() {
  analogWrite(IN01, 0); 
  analogWrite(IN02, 255);

  analogWrite(IN11, 255); 
  analogWrite(IN12, 0);

  analogWrite(IN21, 0);
  analogWrite(IN22, 255);

  analogWrite(IN31, 255); 
  analogWrite(IN32, 0);
}

void ROTACION_ANTIHORARIA() {
  analogWrite(IN01, 255); 
  analogWrite(IN02, 0);

  analogWrite(IN11, 0); 
  analogWrite(IN12, 255);

  analogWrite(IN21, 255);
  analogWrite(IN22, 0);

  analogWrite(IN31, 0); 
  analogWrite(IN32, 255);
}

void IZQUIERDA() {
  analogWrite(IN01, 255); 
  analogWrite(IN02, 0);

  analogWrite(IN11, 0); 
  analogWrite(IN12, 255);

  analogWrite(IN21, 0);
  analogWrite(IN22, 255);

  analogWrite(IN31, 255); 
  analogWrite(IN32, 0);
}

void DERECHA() {
  analogWrite(IN01, 0); 
  analogWrite(IN02, 255);

  analogWrite(IN11, 255); 
  analogWrite(IN12, 0);

  analogWrite(IN21, 255);
  analogWrite(IN22, 0);

  analogWrite(IN31, 0); 
  analogWrite(IN32, 255);
}

void FRENAR() { 

  analogWrite(IN01, 0); 
  analogWrite(IN02, 0);

  analogWrite(IN11, 0); 
  analogWrite(IN12, 0);

  analogWrite(IN21, 0);
  analogWrite(IN22, 0);

  analogWrite(IN31, 0); 
  analogWrite(IN32, 0);

}

void casos(String header2){
      Serial.println("ESTE ES EL HEADER BIENVENIDOS MUCHAS GRACIAS"); //Manera de identificar cual es el header, es decir la IP que recibe el ESP32
      Serial.println(header2);

    char str_valor = header2[5]; // Guarda en str_valor el caracter que recibe de la app.
    Serial.println(str_valor);
    String input = "";
    input=str_valor;

    Serial.print("Input recibido: ");
    Serial.println(input); // Imprime el dato recibido en el monitor serie para un mejor comprension
    
    // En función del INPUT recibido por la app, llamamos a la funcion de movimiento necesaria
    if (input=="W") //Llama a la funcion que corresponde a Avanzar
      {
        ADELANTE();
      }
      else if (input=="S") //Llama a la funcion que corresponde a ir hacia atras
      {
        ATRAS();
      } 
      else if (input=="A") //Llama a la funcion que corresponde a moverese a la izquierda
      {
        IZQUIERDA();
      } 
      else if (input=="D") //Llama a la funcion que corresponde a mover a la derecha
      {
        DERECHA();
      } 
      else if (input=="E") //Llama a la funcion que corresponde a rotar sobre su propio eje en sentido horario
      {
        ROTACION_HORARIA();
      } 
      else if (input=="Q") //Llama a la funcion que corresponde a rotar sobre su propio eje en sentido anti-horario
      {
        ROTACION_ANTIHORARIA();
      } 
      else if (input=="F") //Llama a la funcion que corresponde a frenar
      {
        FRENAR();
      } 
      else 
      {
        Serial.println("VALOR INCORRECTO"); //En caso de que input contenga un caracter no contemplado, devuelve el aviso de valor incorrecto.
      }

}


void parametrosWiFi(){ //Esta es la función principal, que se encarga de traer la IP desde la app y comunicarsela al VONT.

WiFiClient client = server.available(); //Se conecta mediante WiFi conn la app y se fija si está disponible para enviar o recibir ir información.

if (client){
  
    String currentline = ""; //Para guardar la info que llega del client

  while(client.connected()){ //Lleva a cabo las siguientesi instruccipones siempre y cuando la app se mantenga conectada al ESP#"32
    if (client.available()){  // Ejecuta en función de si la app está disponible para enviar o recibir info 
      char c = client.read(); //En caso de que esté disponible, lee la IP y la almacena en la variable c.
      Serial.write(c); //Escribe la IP leída para realizar seguimiento
      header += c ;      
      
      if (c == '\n'){ //Revisa si la cadena de la IP terminó.

        if(currentline.length() == 0 ){
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          break; // Salir del ciclo while:
          
        }else { //si tiene una nueva línea, borra currentLine:
          currentline = "";
        }

      }else if (c != '\r'){ // Si se vuelva al inicio de la cadena, anexa c a currenline para no perderlo.
        currentline =+ c;
      }
      
    }
  }
  
  casos (header); //Con el valor de header corre la función casos para comunicarse y mover al VONT en función del carácter dado.
  header = ""; //Vvacía la variable header para poder volver a correr esta función
  client.stop(); //Y Corta comunicación con la app.
 }
 
}


void loop() {
  parametrosWiFi(); //Corre la función parametrosWiFi, que es la que se encarga de la comunicación y con la app y movimiento del VONT en loop.
}