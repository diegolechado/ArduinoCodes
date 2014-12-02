#include <dht.h>
#include <SPI.h>
#include <Ethernet.h>

#define dht_dpin A1 //DHT DATA PIN

//Ethernet Configurations
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "diegolecha.dominiotemporario.com";
IPAddress ip(192,168,0,189);
EthernetClient client;

boolean clientConnected = false;

dht DHT; //Inicializa o sensor

void setup()
{
  Serial.begin(9600);
  delay(1000);
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  
  delay(1000);
  Serial.println("connecting...");  
  
  
  
}

void loop()
{
  DHT.read11(dht_dpin);

  if (client.connect(server, 80)) 
  {
    Serial.println("connected");
    clientConnected = true;
  }
  else
  {
      Serial.println("disconnected");
      clientConnected = false;
  }

  if(clientConnected)
  {
    Serial.println("sending...");
    client.print("GET /Arduino/Service1.svc/SetTemperature/");
    client.print(DHT.temperature);
    client.println(" HTTP/1.1");
    client.println("Host: diegolecha.dominiotemporario.com");
    //client.println("Connection: close");
    client.println();
    
    client.stop();
    client.flush();
  }
  

  Serial.print("Umidade = ");
  Serial.print(DHT.humidity);
  Serial.print(" %  ");
  Serial.print("Temperatura = ");
  Serial.print(DHT.temperature); 
  Serial.println(" Celsius  ");
  
  delay(5000);  
}
