#include <IRremote.h>

int IR_Recv = 3;   //IR Receiver Pin 3
int g_ledPin = 5;  //green LED pin 5
int y_ledPin = 6;  //yellow LED pin 6
int r_ledPin = 9;  //red LED pin 9
int b_ledPin = 10; //blue LED pin 10
float controllerValue;
boolean power = false;

IRrecv irrecv(IR_Recv);
decode_results results;

void setup(){
  Serial.begin(9600);  //starts serial communication
  irrecv.enableIRIn(); // Starts the receiver
  pinMode(g_ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(y_ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(r_ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(b_ledPin, OUTPUT);      // sets the digital pin as output
}

void PiscarTodosLeds()
{
  Serial.println("Entrou !!!!");
  digitalWrite(g_ledPin, HIGH);
  digitalWrite(b_ledPin, HIGH);
  digitalWrite(r_ledPin, HIGH);
  digitalWrite(y_ledPin, HIGH);
  
  delay(300);

  digitalWrite(g_ledPin, LOW);
  digitalWrite(b_ledPin, LOW);
  digitalWrite(r_ledPin, LOW);
  digitalWrite(y_ledPin, LOW);  
}

void loop(){
  //decodes the infrared input
  if (irrecv.decode(&results))
  {
    Serial.print("Valor lido : ");  
    Serial.println(results.value);  
    controllerValue = results.value;  
    
    if(controllerValue == 551494365)
    {
      if(!power)
      {
        power = true;
        PiscarTodosLeds();
      }
      else
      {
        power = false;
        PiscarTodosLeds();
        PiscarTodosLeds();
      }
    }
    else if(controllerValue == 551485695)
    {
      digitalWrite(b_ledPin, HIGH);     
    }
    else if(controllerValue == 551502015)
    {
      digitalWrite(r_ledPin, HIGH);     
    }
    else if(controllerValue == 551518335)
    {
      digitalWrite(y_ledPin, HIGH);     
    }
    else if(controllerValue == 551534655)
    {
      digitalWrite(g_ledPin, HIGH);     
    }
    
    irrecv.resume();
  }
}
