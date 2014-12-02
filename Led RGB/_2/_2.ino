int redpin=9;      //Pin 9
int greenpin=10;    //Pin 10
int bluepin=11;      //Pin 11
int var=0;
int var1=0;


void setup()
{
}

void loop()
{
  analogWrite(redpin,0);  //RED
  analogWrite(greenpin,0);
  analogWrite(bluepin,255);  
  delay(2000);
  
  for(var=0;var<255;var++)
  {
    analogWrite(redpin,0);  //RED
    analogWrite(greenpin,var);
    analogWrite(bluepin,(255 - var));
    delay(30);
  }

  analogWrite(redpin,255);  //RED
  analogWrite(greenpin,0);
  analogWrite(bluepin,0);  
  delay(2000);
  
  for(var=0;var<255;var++)
  {
    analogWrite(redpin,255);  //RED
    analogWrite(greenpin,255);
    analogWrite(bluepin,var);
    delay(30);
  }  
}

