// Se agregan las librerias que se usarán.
#include <DHT.h>
#include <Ethernet.h>
#include <SPI.h>

// Se inicializan las variables
#define DHTPIN 2
#define DHTTYPE DHT22
#define dustPIN 3
#define dustAnalog 5
#define termAnalog 0

DHT dht(DHTPIN, DHTTYPE);
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

// Configuracion del Ethernet Shield
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x51, 0x31}; // Direccion MAC
byte ip[] = { 192,168,1,122 }; // Direccion IP del Arduino
byte server[] = { 192,168,1,144 }; // Direccion IP del servidor
EthernetClient client;

//Se especifica la entrada digital a la placa Arduino desde el sensor DHT22.

void setup(void) {
  Serial.begin(9600);
  Ethernet.begin(mac); // Inicializamos el Ethernet Shield
  delay(1000); // Esperamos 1 segundo de cortesia
  dht.begin();
  pinMode(dustPIN,OUTPUT);
}

void loop(void) {
  double temperatura = Temperatura();
  double humedad = Humedad();
  double dustConc = Polvo();
  
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("°C Humedad: ");
  Serial.print(humedad);
  Serial.print("% Concentracion de polvo: ");
  Serial.print(dustConc);
  Serial.print("ppm");
  
  EnviarDatos();
  delay(10000); // Espero 10 seg antes de tomar otra muestra
}

double Temperatura() {
  double temperatura;
  
  temperatura = analogRead(termAnalog);
  temperatura = 5.0*temperatura/1023.0;
  temperatura = (4.6183 - temperatura) / 0.049;
  
  return temperatura;
}

double Humedad() {
  double humedad;
  humedad = dht.readHumidity();
  return humedad;  
}

double Polvo() {
  double polvo;
  
  digitalWrite(dustPIN,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  delayMicroseconds(deltaTime);
  digitalWrite(dustPIN,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  
  polvo = 5.0*analogRead(A5)/1023.0;
  polvo = (polvo-0.0356)*120000;
  
  return polvo;
}

void EnviarDatos(server,temperatura,humedad,dustConc) {
  // Proceso de envio de muestras al servidor
  Serial.println("Conectando...");
  if (client.connect(server, 80)>0) {  // Conexion con el servidor
    client.print("GET /proyectoTics.php?temperatura="); // Se envian los datos por GET
    client.print(temperatura);
    client.print("&humedad=");
    client.print(humedad);
    client.print("&polvo=");
    client.print(dustConc);
    client.println(" HTTP/1.0");
    client.println("User-Agent: Arduino 1.0");
    client.println();
    Serial.println("Conectado");
  } else {
    Serial.println("Fallo en la conexion");
  }
  if (!client.connected()) {
    Serial.println("Desconectado");
  }
  client.stop();
  client.flush();
}
