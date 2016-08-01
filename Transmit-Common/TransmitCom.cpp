#include "TransmitCom.h"


void flashSequence(char sequence, uint16_t ered, uint16_t  egreen, uint16_t eblue)
{
    
    uint16_t red, green, blue, c;
    
    bool buff[12];
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

void synchronization(int initDelay)
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
