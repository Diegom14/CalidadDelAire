#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>



byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x51, 0x31};

// Direccion del servidor
IPAddress server(127,0,0,1);

EthernetClient client;

// Variable de tiempo de la ultima conexion en milisegundos
unsigned long ultimaConexion = 0;          
// Estado de la ultima conexion
boolean ultimoEstado = false;
// Intervalo en milisegundos entre conexiones
const unsigned long intervaloConexion = 2000;   




// Configura Arduino 
void setup() {
Serial.begin(9600);
Serial.println("InternetdelasCosas.cl\n\nPrueba de sensor DHTxx!");

// Espera 1 segundo para que se inicie la tarjeta Ethernet
delay(1000);
Ethernet.begin(mac);
Serial.print("Direccion IP: ");
Serial.println(Ethernet.localIP());
}

void loop() {
// Espera dos segundos para realizar la primera medición.
delay(1000);
// Obtiene la Temperatura en Celsius




      if (client.connect(server, 80)) {

// Envia el dato al puerto serial 

// Envia el requerimiento al servidor via GET
Serial.println("Iniciando conexion...");
client.print("GET /telecoconta/domotica.php?t=");
client.print("Hello world");

client.println(" HTTP/1.1");
client.print("Host: ");
client.println(server);
client.println("User-Agent: Arduino-Ethernet");
client.println("Connection: close");
client.println();

// Actualiza el tiempo en milisegundos de la ultima conexion
ultimaConexion = millis();
} 
else {
// Si la conexion fallo se desconecta
Serial.println("Error al conectarse al servidor");
Serial.println("Desconectando...");
client.stop();
}

}


