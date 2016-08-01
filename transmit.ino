#include <Adafruit_TCS34725.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X);
uint16_t red, green, blue, c, ered, egreen, eblue;
int r = 2;
int g = 3;
int b = 4;
int ledState = LOW;
int initDelay = 500;
int i = 0;
  


void setup() {
  // put your setup code here, to run once:

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  Serial.begin(250000);

    if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("Cannot find sensor");
    while (1);
  }
  tcs.getRawData(&ered, &egreen, &eblue, &c); //store environment values

}

void loop()
{
  // put your main code here, to run repeatedly:

  String str;
  if (Serial.available() > 0)
  {
    str = Serial.readString(); // read a single letter if (ch >= 'a' && ch <= 'z')

    if(str == "sync")
      synchronization();
    else
    {
    for(int j=0; j<str.length(); ++j)
    {
      Serial.print(str[j] + ": ");
      flashSequence(str[j]);
      i = 0;
    }
    }
    digitalWrite(r, LOW);
    digitalWrite(g, LOW);
    digitalWrite(b, LOW);
//delay(dotDelay * 4);

    }
}

void flashSequence(char sequence)
{
  bool out[8], parity[4];
  
  encodeASCII(sequence, out);
  addParity(out, parity);
  bool buff[12] = {parity[0], parity[1], out[0], parity[2], out[1], out[2], out[3], parity[3], 
          out[4], out[5], out[6], out[7]};
  
  Serial.print(sequence);
  Serial.print(": ");

  tcs.getRawData(&red, &green, &blue, &c); //store environment values
  while(green < egreen*2)
  {
    tcs.getRawData(&red, &green, &blue, &c); //store environment values
  }
  bool first = true;
  while(i<12)
  {
    if(!first)
    {
      tcs.getRawData(&red, &green, &blue, &c); //store environment values
      while(blue < eblue*2)
      {
        tcs.getRawData(&red, &green, &blue, &c); //store environment values
      }
      while(blue < eblue*2)
      {
        tcs.getRawData(&red, &green, &blue, &c); //store environment values
      }
    }
    
    first = false;
    if(i % 3 == 0)
    {
      flashDotOrDash(2, buff[i]);
      i++;
    }
    if(i % 3 == 1)
    {
      flashDotOrDash(3, buff[i]);
      i++;
    }
    if(i % 3 == 2)
    {
      flashDotOrDash(4, buff[i]);
      i++;
    }
    delay(1000);
  }
  Serial.println();
  
}


void flashDotOrDash(int color, bool dotOrDash)
{
  Serial.print(dotOrDash);
  if(dotOrDash)
    digitalWrite(color, HIGH);
  else
   digitalWrite(color, LOW);
}

void synchronization(void)
{
  digitalWrite(r, HIGH);
  delay(initDelay);
  digitalWrite(r, LOW);
  
  digitalWrite(g, HIGH);
  delay(initDelay);
  digitalWrite(g, LOW);
  
  digitalWrite(b, HIGH);
  delay(initDelay);
  digitalWrite(b, LOW);
  

  digitalWrite(r, HIGH);
  digitalWrite(g, HIGH);
  delay(initDelay);
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  
  digitalWrite(r, HIGH);
  digitalWrite(b, HIGH);
  delay(initDelay);
  digitalWrite(r, LOW);
  digitalWrite(b, LOW);
 
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  delay(initDelay);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
  

  digitalWrite(r, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(b, HIGH);
  delay(initDelay);
  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
  delay(initDelay);
}


void encodeASCII(char in, bool out[])
{
    for(int j = 0; j < 8; j++)
        out[j] = 0;
    
    out[0] = 0;
    if(in % 2)
        out[7] = 1;
    in = in / 2;
    if(in % 2)
        out[6] = 1;
    in = in / 2;
    if(in % 2)
        out[5] = 1;
    in = in / 2;
    if(in % 2)
        out[4] = 1;
    in = in / 2;
    if(in % 2)
        out[3] = 1;
    in = in / 2;
    if(in % 2)
        out[2] = 1;
    in = in / 2;
    if(in % 2)
        out[1] = 1;
    in = in / 2;
}

void addParity(bool data[], bool parity[])
{
  
  parity[0]=data[0]^data[1]^data[3]^data[4]^data[6];
  parity[1]=data[0]^data[2]^data[3]^data[5]^data[6];
  parity[2]=data[1]^data[2]^data[3]^data[7];
  parity[3]=data[4]^data[5]^data[6]^data[7];  
}

