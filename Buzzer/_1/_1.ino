int redPin=9;     
int greenPin=10;    
int bluePin=11;      

int buzzer = 2;
int pirSensor = 8;

int valPirSensor = 0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(buzzer, OUTPUT);
  pinMode(pirSensor, INPUT);
}

void loop()
{
  valPirSensor = digitalRead(pirSensor);
  noTone(buzzer);
  
  Serial.println(valPirSensor);  
  
  if(valPirSensor == 1)
  {
    ligarAlarme();
  }
}

void ligarAlarme()
{
  Serial.println("ligar");  
  analogWrite(greenPin,0);
  analogWrite(redPin,255);
  tone(buzzer, 1500);
  delay(600);

  noTone(buzzer);
  delay(500);  
  
  tone(buzzer, 1500);
  delay(600); 
  
  desligarAlarme();
}

void desligarAlarme()
{
  Serial.println("ligar");  
  analogWrite(greenPin,255);
  analogWrite(redPin,0);
  noTone(buzzer);
}

