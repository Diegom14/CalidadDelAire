#include "DHT.h"

//Se especifica la entrada digital a la placa Arduino desde el sensor DHT22.
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Se le asignan las entradas desde el sensor de partículas de polvo, para la entrada analógica
// se cambia el entero "measurePin". Para la entrada digital se cambia la variable "ledPower".
int measurePin = 5;
int ledPower = 3;
 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

// Se inicializa la variable "voMeasured" que toma valores entre 0-1023 y que corresponde a la señal analógica,
// la variable "calcVoltage" es la traducción de la señal analógica al nivel de voltaje. "dustDensity" es el
// significado de este voltaje en concentración de partículas en mg/m3. 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

// "Vr" es el nivel de voltaje de salida del circuito con termistor. Se traduce en temperatura "T1"
float Vr = 0.0;
float T1 = 0.0;
 
void setup(){
  Serial.begin(9600);
  dht.begin();
  pinMode(ledPower,OUTPUT);
}
   
void loop(){

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  digitalWrite(ledPower,LOW); // power on the LED

  delayMicroseconds(samplingTime);
 
  voMeasured = analogRead(measurePin); // read the dust value
 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
 
  // 0 - 3.3V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1023);
 
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.17 * calcVoltage - 0.1;

  //Se obtiene la salida de tensión, al hacer la siguiente relación.
  Vr = 5.0 * analogRead(A0) / 1023;
  //Para la configuracion con circuito.
  T1 = (4.5355 - Vr) / 0.048;
 
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
 
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
 
  Serial.print(" - Dust Density: ");
  Serial.print(dustDensity);

  Serial.print(" - Humedad: ");
  Serial.print(h);
  Serial.print(" % ");

  Serial.print(" - Temp 1: ");
  Serial.print(T1);
  Serial.print(" °C ");
  
  Serial.print(" - Temperature: ");
  Serial.print(t);
  Serial.println(" °C ");
 
  delay(1000);
}
