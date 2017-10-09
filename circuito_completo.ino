#include "DHT.h"
//#include <Ethernet.h>
//#include <SPI.h>

// Configuracion del Ethernet Shield
//byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xEE}; // Direccion MAC
//byte ip[] = { 192,168,xx,xx }; // Direccion IP del Arduino
//byte server[] = { 127,0,0,1 }; // Direccion IP del servidor
//EthernetClient client; 
float temperatura;
int analog_pin = 0;

//Se especifica la entrada digital a la placa Arduino desde el sensor DHT22.
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

// Se inicializa la variable "voMeasured" que toma valores entre 0-1023 y que corresponde a la señal analógica,
// la variable "calcVoltage" es la traducción de la señal analógica al nivel de voltaje. "dustDensity" es el
// significado de este voltaje en concentración de partículas en mg/m3. 

float calcVoltage = 0;
float dustDensity = 0;

// "voltajeSalida" es el nivel de voltaje de salida del circuito con termistor. Se traduce en temperatura "temp"
float voltajeSalida = 0.0;
float temp = 0.0;
 
void setup(){
  Serial.begin(9600);
  Ethernet.begin(mac, ip); // Inicializamos el Ethernet Shield
  delay(1000); // Esperamos 1 segundo de cortesia
  dht.begin();
  pinMode(3,OUTPUT);
}
   
void loop(){

  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();
  digitalWrite(3,LOW); // power on the LED

  delayMicroseconds(samplingTime);
 
  delayMicroseconds(deltaTime);
  digitalWrite(3,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
 
  // 0 - 3.3V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = analogRead(A5) * (5.0 / 1023);
 
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.17 * calcVoltage - 0.1;

  //Se obtiene la salida de tensión, al hacer la siguiente relación.
  voltajeSalida = 5.0 * analogRead(A0) / 1023;
  //Para la configuracion con circuito.
  temp = (4.5355 - voltajeSalida) / 0.048;
 
  Serial.print(" - Densidad de Polvo: ");
  Serial.print(dustDensity);
  Serial.print(" mg/m3 ");
 
  Serial.print(" - Humedad: ");
  Serial.print(h);
  Serial.print(" % ");

  Serial.print(" - Temp 1: ");
  Serial.print(temp);
  Serial.print(" °C ");
  
  Serial.print(" - Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C ");
 
  // Proceso de envio de muestras al servidor
  //if (client.connect("192.168.1.75", 80)) {
  // Serial.print("Connected to MySQL server. Sending data...");

  // client.print("POST /enviarDatos.php HTTP/1.1\n");
  // client.print("Host: 127.0.0.1\n");
  // client.print("Connection: close\n");
  // client.print("Content-Type: application/x-www-form-urlencoded\n");
  // client.print("Content-Length: ");
  // client.print(txData.length());
  // client.print("\n\n");
  // client.print(txData);
  // Serial.println("Successfull");
  //}

  //else{
  // Serial.println("Connection failed");
  // Serial.println();

  //}
  //if (!client.connected()) {
  //  Serial.println("Disconnected!");
  //}
  //client.stop();
  //client.flush();
 
  delay(15000);
}
