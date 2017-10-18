#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>


byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x51, 0x31};
byte server [] = {127,0,0,1};

EthernetClient client;

void setup(){

  Serial.begin(9600);
  Ethernet.begin(mac);
}


void loop() {
  
  Serial.print("Hello world");
  Serial.write("Hello world");
  delay(1000);
  
}
