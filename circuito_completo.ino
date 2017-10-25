#include <DHT.h>
#include <Ethernet.h>
#include <SPI.h>

// Configuracion del Ethernet Shield
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x51, 0x31}; // Direccion MAC
byte ip[] = { 192,168,1,122 }; // Direccion IP del Arduino
byte server[] = { 192,168,1,144 }; // Direccion IP del servidor
EthernetClient client;

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
float dustConc = 0;

// "voltajeSalida" es el nivel de voltaje de salida del circuito con termistor. Se traduce en temperatura "temp"
float temperatura = 0.0;

void setup(void) {
  Serial.begin(9600);
  Ethernet.begin(mac); // Inicializamos el Ethernet Shield
  delay(1000); // Esperamos 1 segundo de cortesia
  dht.begin();
  pinMode(3,OUTPUT);
}

void loop(void) {
  float humedad = dht.readHumidity();
  digitalWrite(3,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  delayMicroseconds(deltaTime);
  digitalWrite(3,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  dustConc = 5.0*analogRead(A5)/1023.0;
  dustConc = (dustConc-0.0356)*120000;
  
  temperatura = analogRead(A0);
  temperatura = 5.0*temperatura/1023.0;
  temperatura = (4.5355 - temperatura) / 0.048;
  
  // Proceso de envio de muestras al servidor
  Serial.println("Connecting...");
  if (client.connect(server, 80)>0) {  // Conexion con el servidor
    client.print("GET /proyectoTics.php?temperatura="); // Enviamos los datos por GET
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
    Serial.println("Disconnected!");
  }
  client.stop();
  client.flush();
  delay(10000); // Espero 15 seg antes de tomar otra muestra
}
