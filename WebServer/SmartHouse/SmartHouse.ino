#include <SPI.h>
#include <Ethernet.h>  // Biblioteca utilizada para comunicação com o Arduino
 
// A linha abaixo permite definir o endereço físico (MAC ADDRESS) da placa de rede. 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte ip[] = { 192, 168, 0, 184 };  // Define o endereço IP.
    
EthernetServer server(80);  // Porta onde estará aberta para comunicação Internet e Arduino.
 
String readString;
int PIN_LED1 = 7;  //  Pino digital onde será ligado e desligado o LED.
int PIN_LED2 = 6;
int PIN_LED3 = 5;
int PIN_LED4 = 4;
 
void setup(){
  pinMode(PIN_LED1, OUTPUT); 
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
  Ethernet.begin(mac, ip);  // Chama o MAC e o endereço IP da placa Ethernet.
  server.begin();  //  Inicia o servidor que esta inserido junto a placa Ethernet.
}
 
void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
 
        if (readString.length() < 100) {
          readString += c;             
        }

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
    
           // A partir daqui começa os códigos html.
    
          client.println("<HTML>");
          client.println("<BODY style='font-family:Arial'>");
          client.println("<center>");
          client.println("<H1 style="">Smart House Diego</H1>");
          client.println("<br />");
          
          client.println("<a style='text-decoration:none;background-color: #3598DC;color: white;padding: 10px;' href=\"/diegofl/LedOn\"\">LED ON</a>");
          client.println("<a style='text-decoration:none;background-color: #3598DC;color: white;padding: 10px;' href=\"/diegofl/LedOff\"\">LED OFF</a><br />");   
          
          client.println("</BODY>");
          client.println("</HTML>");
          
          delay(1);
          client.stop();
          
          if(readString.indexOf("diegofl/LedOn") > 0)
          {
            digitalWrite(PIN_LED1, HIGH);
            digitalWrite(PIN_LED2, HIGH);
            digitalWrite(PIN_LED3, HIGH);
            digitalWrite(PIN_LED4, HIGH);
          }
          else {
            if(readString.indexOf("diegofl/LedOff") > 0)
            {
              digitalWrite(PIN_LED1, LOW);
              digitalWrite(PIN_LED2, LOW);
              digitalWrite(PIN_LED3, LOW);
              digitalWrite(PIN_LED4, LOW);
            }
          }
          readString="";    
        }
      }
    }
  }
}
