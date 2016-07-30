 // Yigit Suoglu Jul 28, 2016
// Reciever code with threshold detection

#include <colorBit_Struct.h>
#include <encode_decode.h>
#include <HammingCode.h>
#include <Adafruit_TCS34725.h>
#include <Wire.h>
#include <RGB_Detection.h>

#define greenLED 12 //bacon
#define blueLED 13 //acknowledgement
#define thErrON 0.9
#define thErrOFF 1.3
#define setupWaitTime 10 //(ms)
#define fbTime 1000 // feedback led high time
#define cycTime 1000 // feedback led low time
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X);


bool buff[12];
char ch;

colorBit th_Val[8];
uint16_t r, g, b, c;


void setup() 
{
  th_Val[0].bits[0] = 0; //values for environment
  th_Val[0].bits[1] = 0;
  th_Val[0].bits[2] = 0;
  th_Val[1].bits[0] = 1; //values for R
  th_Val[1].bits[1] = 0;
  th_Val[1].bits[2] = 0;
  th_Val[2].bits[0] = 0; //valurs for G
  th_Val[2].bits[1] = 1;
  th_Val[2].bits[2] = 0;
  th_Val[3].bits[0] = 0; //values for B
  th_Val[3].bits[1] = 0;
  th_Val[3].bits[2] = 1;
  th_Val[4].bits[0] = 1; //values for RG
  th_Val[4].bits[1] = 1;
  th_Val[4].bits[2] = 0;
  th_Val[5].bits[0] = 1; //values for RB
  th_Val[5].bits[1] = 0;
  th_Val[5].bits[2] = 1;
  th_Val[6].bits[0] = 0; //values for GB
  th_Val[6].bits[1] = 1;
  th_Val[6].bits[2] = 1; 
  th_Val[7].bits[0] = 1; //values for RGB
  th_Val[7].bits[1] = 1;
  th_Val[7].bits[2] = 1;

  Serial.begin(250000);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("Cannot find sensor");
    while (1);
  }
  Serial.print("Getting threshold values");
  tcs.getRawData(&r, &g, &b, &c); //store environment values
  th_Val[0].r_t = (r * thErrOFF);
  th_Val[0].g_t = (g * thErrOFF);
  th_Val[0].b_t = (b * thErrOFF);
  while(r < (1.5 * th_Val[0].r_t))
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until red is high
  } 
  Serial.print(".");
  delay(setupWaitTime);
  //set threshold for red high
  th_Val[1].r_t = (r * thErrON); 
  th_Val[1].g_t = (g * thErrOFF);
  th_Val[1].b_t = (b * thErrOFF);
  
   while((r > th_Val[1].r_t)/* | (g < (1.5 * th_Val[0].g_t))*/) //commented out due to low program storage space
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until green is high and red is low
  }
  Serial.print("."); 
  delay(setupWaitTime);
  //set threshold for green high
  th_Val[2].r_t = (r * thErrOFF); 
  th_Val[2].g_t = (g * thErrON);
  th_Val[2].b_t = (b * thErrOFF); 

   while((g > th_Val[2].g_t)/* | (b < (1.5 * th_Val[0].b_t))*/) //commented out due to low program storage space
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until blue is high and green is low
  }
  Serial.print(".");
  delay(setupWaitTime); 
  //set threshold for blue high
  th_Val[3].r_t = (r * thErrOFF); 
  th_Val[3].g_t = (g * thErrOFF);
  th_Val[3].b_t = (b * thErrON); 

  while((b > th_Val[3].b_t))
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until blue is low
  }
  Serial.print(".");
  delay(setupWaitTime); 
  //set threshold for red-green high
  th_Val[4].r_t = (r * thErrON); 
  th_Val[4].g_t = (g * thErrON);
  th_Val[4].b_t = (b * thErrOFF);

    while((g > th_Val[4].g_t))
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until green is low
  }
  Serial.print(".");
  delay(setupWaitTime); 
  //set threshold for red-blue high
  th_Val[5].r_t = (r * thErrON); 
  th_Val[5].g_t = (g * thErrOFF);
  th_Val[5].b_t = (b * thErrON); 
  
    while((r > th_Val[5].r_t))
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until red is low
  }
  Serial.print(".");
  delay(setupWaitTime); 
  //set threshold for green-blue high
  th_Val[6].r_t = (r * thErrOFF); 
  th_Val[6].g_t = (g * thErrON);
  th_Val[6].b_t = (b * thErrON); 
    
    while((r < th_Val[6].r_t))
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until red is high
  }
  Serial.print(".");
  delay(setupWaitTime); 
  //set threshold for red-green-blue high
  th_Val[7].r_t = (r * thErrON); 
  th_Val[7].g_t = (g * thErrON);
  th_Val[7].b_t = (b * thErrON); 
  Serial.println("Done");
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT); 
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW);
  
  for(int j = 0; j < 8; j++)
  {
    Serial.print("Env ");
    Serial.print(j);
    Serial.print(" R: ");
    Serial.print(th_Val[j].r_t);
    Serial.print(" G: ");
    Serial.print(th_Val[j].g_t);
    Serial.print(" B: ");
    Serial.println(th_Val[j].b_t);
  }
  Serial.println("Starting...");
}

void loop() 
{
  bool err = 0;
  digitalWrite(greenLED, HIGH);
  delay(fbTime);
  digitalWrite(greenLED, LOW);
  delay(cycTime);
  
  tcs.getRawData(&r, &g, &b, &c);

  detect_rgb(r, g, b, th_Val, buff[0], buff[1], buff[2]);

  digitalWrite(blueLED, HIGH);
  delay(fbTime);
  digitalWrite(blueLED, LOW);
  delay(cycTime);

  tcs.getRawData(&r, &g, &b, &c);

  detect_rgb(r, g, b, th_Val, buff[3], buff[4], buff[5]);

  digitalWrite(blueLED, HIGH);
  delay(fbTime);
  digitalWrite(blueLED, LOW);
  delay(cycTime);

  tcs.getRawData(&r, &g, &b, &c);

  detect_rgb(r, g, b, th_Val, buff[6], buff[7], buff[8]);

  digitalWrite(blueLED, HIGH);
  delay(fbTime);
  digitalWrite(blueLED, LOW);
  delay(cycTime);

    tcs.getRawData(&r, &g, &b, &c);

  detect_rgb(r, g, b, th_Val, buff[9], buff[10], buff[11]);

  checkParity(buff[2], buff[4], buff[5], buff[6], buff[8], buff[9], buff[10], buff[11], buff[0], buff[1], buff[3], buff[7], err);
  
  ch = decodeASCII(buff[2], buff[4], buff[5], buff[6], buff[8], buff[9], buff[10], buff[11]);
  
  if(ch != NULL)
    Serial.print(ch);  
  
}
