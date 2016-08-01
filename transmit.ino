#include <Adafruit_TCS34725.h>
#include <encode_decode.h>
#include <HammingCode.h>
#include <Wire.h>

#define r 2
#define g 3
#define b 4
#define initDelay 500

void synchronization(void);
void flashDotOrDash(int color, bool dotOrDash);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X);
uint16_t red, green, blue, c, ered, egreen, eblue;
bool buff[12];


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
    str = Serial.readString();

    if(str == "sync")
      synchronization();
    else
    {
      for(int j=0; j<str.length(); ++j)
       {
        Serial.print(str[j] + ": ");
        flashSequence(str[j]);
       }
    }
    digitalWrite(r, LOW);
    digitalWrite(g, LOW);
    digitalWrite(b, LOW);

   }
}

void flashSequence(char sequence)
{
    
    encodeASCII(sequence, buff[2],buff[4],buff[5],buff[6],buff[8],buff[9],buff[10],buff[11]);
    addParity(buff[2],buff[4],buff[5],buff[6],buff[8],buff[9],buff[10],buff[11], buff[0],buff[1],buff[3],buff[7]);
    
    
    Serial.print(sequence);
    Serial.print(": ");
    
    tcs.getRawData(&red, &green, &blue, &c);
    while(green < egreen*2)
    {
        tcs.getRawData(&red, &green, &blue, &c);
    }
    bool first = true;
    int j = 0;
    while(j<12)
    {
        if(!first)
        {
            tcs.getRawData(&red, &green, &blue, &c);
            while(blue > eblue*2)
            {
                tcs.getRawData(&red, &green, &blue, &c);
            }
            while(blue < eblue*2)
            {
                tcs.getRawData(&red, &green, &blue, &c);
            }
        }
        
        first = false;

        flashDotOrDash(2, buff[j]);
        j++;
        

        flashDotOrDash(3, buff[j]);
        j++;
        

        flashDotOrDash(4, buff[j]);
        j++;
        
    }    
}


void flashDotOrDash(int color, bool dotOrDash)
{
    Serial.print(dotOrDash);
    if(dotOrDash)
        digitalWrite(color, HIGH);
    else
        digitalWrite(color, LOW);
}

void synchronization()
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



