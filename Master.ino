  // Yigit Suoglu, Musab Cevik, Onur Calik, Baran Dereli, Ozgun Sensoy Aug 3, 2016
 // version 1.0.0
// All codes combined

#include <colorBit_Struct.h>
#include <encode_decode.h>
#include <HammingCode.h>
#include <Adafruit_TCS34725.h>
#include <Wire.h>
#include <RGB_Detection.h>

#define redLED 2  //red led port
#define greenLED 3 //bacon & green led port
#define blueLED 4 //acknowledgement & blue led port
#define thErrON 0.9 //threshold multipler HIGH leds
#define thErrOFF 1.5 //threshold multipler LOW leds
#define setupWaitTime 1 //(ms) delay at setup time 
#define fbTime 25 //(ms) feedback led on time
#define cycTime 25 //(ms) feedback led off time
#define sync "MODE_sync" // keyword for start sync seq (transmitter side)
#define recal "MODE_recal" // keyword for start sync seq (receiver side)
#define partyM "MODE_party" // keyword for party mode (easter egg)
#define crdM "MODE_credits" // keyword to show contributors
#define ledContol "MODE_ledC" //open led control modes
#define initDelay 30 //(ms) synchronization sequence delay
#define redONtime 20 //(ms) 
#define redOFFtime 20 //(ms)
#define trnsDELAY 0 //(ms)

void randomLed();
void flashDotOrDash(int color, bool dotOrDash);
void synchronization();
void flashSequence(char sequence);
void flashDotOrDash(int color, bool dotOrDash);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X); //for sensor

String inputHOLD; //string to hold inputs
bool buff[12]; //buffer to store recived and to be send packets
char ch; //store recived char and char to send
colorBit th_Val[8]; //strore all possible combs
uint16_t r, g, b, c; //to store env data

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

  //define and set all LEDs LOW
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  Serial.begin(250000); //start serial at the highest rate
senscheck:
  if (tcs.begin())  //start sensor
  {
    Serial.println("Found sensor");
  }
  else
  {
    Serial.println("Cannot find sensor"); //if fail stuck here
    goto senscheck;
  }

  Serial.print("Getting enviroment values"); //get env
  tcs.getRawData(&r, &g, &b, &c); //store environment values
  th_Val[0].r_t = ((float) r * thErrOFF);
  th_Val[0].g_t = ((float) g * thErrOFF);
  th_Val[0].b_t = ((float) b * thErrOFF);
  Serial.print("\nWaiting for threshold sequence or type ");
  Serial.print(sync);
  Serial.println(" to send threshold sequence");
  uint16_t r_h, g_h, b_h;
setupMain: //come back here untill sync seq start
  if (Serial.available() > 0) //if there is an input data
  {
    inputHOLD = Serial.readString(); //get input

    if (inputHOLD == sync) //check for sync code
    {
      synchronization(); //if true sync
      goto setupMain; //then go back
    }
    else if (inputHOLD == crdM)
    {
      Serial.println("In alphabetic order:\nOnur Calik\nMusab Cevik\nBaran Dereli\nOzgun Sensoy\nYigit Suoglu");
      goto setupMain; //then go back
    }
    else if (inputHOLD == ledContol)
    {
      Serial.print("Enter led code: ");
      while (true)
      {
        if (Serial.available() > 0)
        {
          inputHOLD = Serial.readString();
          if (inputHOLD == "quit")
          {
            digitalWrite(redLED, LOW);
            digitalWrite(greenLED, LOW);
            digitalWrite(blueLED, LOW);
            break;
          }
          short j = (int) inputHOLD[0] - 48;
          ledControl(j);
        }
      }
      goto setupMain; //then go back
    }
    else if (inputHOLD == partyM)
    {
      randomLed();

    }
  }
  tcs.getRawData(&r, &g, &b, &c); //get env info
  //R00
  if (r < th_Val[0].r_t) //go back if red is lower then OFF threshold
  {
    goto setupMain;
  }
  delay(setupWaitTime);
  Serial.print("Getting threshold values");
  Serial.print(".");
  //set threshold for red HIGH
  r_h = g_h = b_h = 0;
  while (true)
  {
    tcs.getRawData(&r, &g, &b, &c); //get env info
    if (r > r_h)
    {
      r_h = r;
      g_h = g;
      b_h = b;
    }
    else
    {
      th_Val[1].r_t = ((float) r_h * thErrON);
      th_Val[1].g_t = ((float) g_h * thErrOFF);
      th_Val[1].b_t = ((float) b_h * thErrOFF);
      break;
    }
  }

  while (r > th_Val[0].r_t) //wait until red is LOW
  {
    tcs.getRawData(&r, &g, &b, &c); //get env info
  }
  Serial.print(".");
  //0G0
  while (g < th_Val[0].g_t)
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until green is HIGH
  }
  delay(setupWaitTime);
  //set threshold for green high
  r_h = g_h = b_h = 0;
  while (true)
  {
    tcs.getRawData(&r, &g, &b, &c); //get env info
    if (g > g_h)
    {
      r_h = r;
      g_h = g;
      b_h = b;
    }
    else
    {
      th_Val[2].r_t = ((float) r_h * thErrOFF);
      th_Val[2].g_t = ((float) g_h * thErrON);
      th_Val[2].b_t = ((float) b_h * thErrOFF);
      break;
    }
  }
  while (g > th_Val[0].g_t) //wait until green is LOW
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  Serial.print(".");
  //00B
  while (b < th_Val[0].b_t)
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until blue is HIGH
  }
  delay(setupWaitTime);
  //set threshold for blue high
  r_h = g_h = b_h = 0;
  while (true)
  {
    tcs.getRawData(&r, &g, &b, &c); //get env info
    if (b > b_h)
    {
      r_h = r;
      g_h = g;
      b_h = b;
    }
    else
    {
      th_Val[3].r_t = ((float) r_h * thErrOFF);
      th_Val[3].g_t = ((float) g_h * thErrOFF);
      th_Val[3].b_t = ((float) b_h * thErrON);
      break;
    }
  }
  while (b > th_Val[0].b_t)
  {
    tcs.getRawData(&r, &g, &b, &c); //wait until blue is LOW
  }
  Serial.print(".");
  //RG0
  while ((r < th_Val[0].r_t) | (g < th_Val[0].g_t)) //wait until red and green is HIGH
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  delay(setupWaitTime);
  //set threshold for red-green high
  r_h = g_h = b_h = 0;
  while (true)
  {
    tcs.getRawData(&r, &g, &b, &c); //get env info
    bool rChange = false;
    if (r > r_h)
    {
      rChange = true;
      r_h = r;
      if (b_h < b)
      {
        b_h = b;
      }
    }
    if (g > g_h)
    {
      g_h = g;
      if (b_h < b)
      {
        b_h = b;
      }
    }
    else if (!rChange)
    {
      th_Val[4].r_t = ((float) r_h * thErrON);
      th_Val[4].g_t = ((float) g_h * thErrON);
      th_Val[4].b_t = ((float) b_h * thErrOFF);
      break;
    }
  }
  while ((r > th_Val[0].r_t) | (g > th_Val[0].g_t)) //wait until red and green is LOW
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  Serial.print(".");
  //R0B
  while ((r < th_Val[0].r_t) | (b < th_Val[0].b_t)) //wait until red and blue is HIGH
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  delay(setupWaitTime);
  //set threshold for red-blue high
  r_h = g_h = b_h = 0;
  while (true)
  {
    bool rNotChage = true;
    tcs.getRawData(&r, &g, &b, &c); //get env info
    if (r > r_h)
    {
      rNotChage = false;
      r_h = r;
      if (g_h < g)
      {
        g_h = g;
      }
    }
    if (b > b_h)
    {
      b_h = b;
      if (g_h < g)
      {
        g_h = g;
      }
    }
    else if (rNotChage)
    {
      th_Val[5].r_t = ((float) r_h * thErrON);
      th_Val[5].g_t = ((float) g_h * thErrOFF);
      th_Val[5].b_t = ((float) b_h * thErrON);
      break;
    }
  }

  while ((r > th_Val[0].r_t) | (b > th_Val[0].b_t)) //wait until red and blue is LOW
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  Serial.print(".");
  //0GB
  while ((g < th_Val[0].g_t) | (b < th_Val[0].b_t)) //wait until green and blue is HIGH
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  delay(setupWaitTime);
  //set threshold for green-blue high
  r_h = g_h = b_h = 0;
  while (true)
  {
    bool bNotCHANGE = true;
    tcs.getRawData(&r, &g, &b, &c); //get env info
    if (b > b_h)
    {
      bNotCHANGE = false;
      b_h = b;
      if (r_h < r)
      {
        r_h = r;
      }
    }
    if (g > g_h)
    {
      g_h = g;
      if (r_h < r)
      {
        r_h = r;
      }
    }
    else if (bNotCHANGE)
    {
      th_Val[6].r_t = ((float) r_h * thErrOFF);
      th_Val[6].g_t = ((float) g_h * thErrON);
      th_Val[6].b_t = ((float) b_h * thErrON);
      break;
    }
  }
  while ((g > th_Val[0].g_t) | (b > th_Val[0].b_t)) //wait until green and blue is LOW
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  Serial.print(".");
  //RGB
  while ((g < th_Val[0].g_t) | (b < th_Val[0].b_t) | (r < th_Val[0].r_t)) //wait until red, green and blue is HIGH
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  delay(setupWaitTime);
  //set threshold for red-green-blue high
  r_h = g_h = b_h = 0;
  while (true)
  {
    bool anyChange = false;
    tcs.getRawData(&r, &g, &b, &c); //get env info
    if (r > r_h)
    {
      anyChange = true;
      r_h = r;
    }
    if (g > g_h)
    {
      anyChange = true;
      g_h = g;
    }
    if (b_h < b)
    {
      anyChange = true;
      b_h = b;
    }
    if (!anyChange)
    {
      th_Val[7].r_t = ((float) r_h * thErrON);
      th_Val[7].g_t = ((float) g_h * thErrON);
      th_Val[7].b_t = ((float) b_h * thErrON);
      break;
    }
  }

  while ((g > th_Val[0].g_t) | (b > th_Val[0].b_t) | (r > th_Val[0].r_t)) //wait until red, green and blue is HIGH
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  Serial.println("Done");
  //print env values
  for (int j = 0; j < 8; j++)
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
  short writtenCH = 0; //to count chars before new line
  bool err = 0;
  tcs.getRawData(&r, &g, &b, &c);
  if (g > th_Val[2].g_t)
  {
    Serial.print("Received:\n");
listenSTR:
    //send start bacon
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

    if (ch != NULL)
    {
      digitalWrite(redLED, HIGH);
      delay(redONtime);
      Serial.print(ch);
      writtenCH++;
      if (writtenCH == 80)
      {
        Serial.print("\n");
        writtenCH = 0;
      }
      digitalWrite(redLED, LOW);
      delay(redOFFtime);
      if (ch != '\n')
        goto listenSTR;
    }
  }



  if (Serial.available() > 0)
  {
    inputHOLD = Serial.readString();

    if (inputHOLD == sync)
      synchronization();
    else if (inputHOLD == crdM)
    {
      Serial.println("In alphabetic order:\nOnur Calik\nMusab Cevik\nBaran Dereli\nOzgun Sensoy\nYigit Suoglu");
    }
    else if (inputHOLD == ledContol)
    {
      Serial.print("Enter led code: ");
      while (true)
      {
        if (Serial.available() > 0)
        {
          inputHOLD = Serial.readString();
          if (inputHOLD == "quit")
          {
            break;
          }
          short j = (int) inputHOLD[0] - 48;
          ledControl(j);
        }
      }
    }
    else if (inputHOLD == partyM)
    {
      randomLed();
    }
    else if (inputHOLD == recal) //start recalabration seq. wait for synchronization seq.
    {
      Serial.print("Getting enviroment values"); //get env
      tcs.getRawData(&r, &g, &b, &c); //store environment values
      th_Val[0].r_t = ((float) r * thErrOFF);
      th_Val[0].g_t = ((float) g * thErrOFF);
      th_Val[0].b_t = ((float) b * thErrOFF);
      Serial.print("\nWaiting for threshold sequence\n");
      uint16_t r_h, g_h, b_h;
setupMain: //come back here untill sync seq start
      if (Serial.available() > 0) //if there is an input data
      {
        inputHOLD = Serial.readString(); //get input

        if (inputHOLD == sync) //check for sync code
        {
          synchronization(); //if true sync
          goto setupMain; //then go back
        }
      }
      tcs.getRawData(&r, &g, &b, &c); //get env info
      //R00
      if (r < th_Val[0].r_t) //go back if red is lower then OFF threshold
      {
        goto setupMain;
      }
      delay(setupWaitTime);
      Serial.print("Getting threshold values");
      Serial.print(".");
      //set threshold for red HIGH
      r_h = g_h = b_h = 0;
      while (true)
      {
        tcs.getRawData(&r, &g, &b, &c); //get env info
        if (r > r_h)
        {
          r_h = r;
          g_h = g;
          b_h = b;
        }
        else
        {
          th_Val[1].r_t = ((float) r_h * thErrON);
          th_Val[1].g_t = ((float) g_h * thErrOFF);
          th_Val[1].b_t = ((float) b_h * thErrOFF);
          break;
        }
      }

      while (r > th_Val[0].r_t) //wait until red is LOW
      {
        tcs.getRawData(&r, &g, &b, &c); //get env info
      }
      Serial.print(".");
      //0G0
      while (g < th_Val[0].g_t)
      {
        tcs.getRawData(&r, &g, &b, &c); //wait until green is HIGH
      }
      delay(setupWaitTime);
      //set threshold for green high
      r_h = g_h = b_h = 0;
      while (true)
      {
        tcs.getRawData(&r, &g, &b, &c); //get env info
        if (g > g_h)
        {
          r_h = r;
          g_h = g;
          b_h = b;
        }
        else
        {
          th_Val[2].r_t = ((float) r_h * thErrOFF);
          th_Val[2].g_t = ((float) g_h * thErrON);
          th_Val[2].b_t = ((float) b_h * thErrOFF);
          break;
        }
      }
      while (g > th_Val[0].g_t) //wait until green is LOW
      {
        tcs.getRawData(&r, &g, &b, &c);
      }
      Serial.print(".");
      //00B
      while (b < th_Val[0].b_t)
      {
        tcs.getRawData(&r, &g, &b, &c); //wait until blue is HIGH
      }
      delay(setupWaitTime);
      //set threshold for blue high
      r_h = g_h = b_h = 0;
      while (true)
      {
        tcs.getRawData(&r, &g, &b, &c); //get env info
        if (b > b_h)
        {
          r_h = r;
          g_h = g;
          b_h = b;
        }
        else
        {
          th_Val[3].r_t = ((float) r_h * thErrOFF);
          th_Val[3].g_t = ((float) g_h * thErrOFF);
          th_Val[3].b_t = ((float) b_h * thErrON);
          break;
        }
      }
      while (b > th_Val[0].b_t)
      {
        tcs.getRawData(&r, &g, &b, &c); //wait until blue is LOW
      }
      Serial.print(".");
      //RG0
      while ((r < th_Val[0].r_t) | (g < th_Val[0].g_t)) //wait until red and green is HIGH
      {
        tcs.getRawData(&r, &g, &b, &c);
      }
      delay(setupWaitTime);
      //set threshold for red-green high
      r_h = g_h = b_h = 0;
      while (true)
      {
        tcs.getRawData(&r, &g, &b, &c); //get env info
        bool rChange = false;
        if (r > r_h)
        {
          rChange = true;
          r_h = r;
          if (b_h < b)
          {
            b_h = b;
          }
        }
        if (g > g_h)
        {
          g_h = g;
          if (b_h < b)
          {
            b_h = b;
          }
        }
        else if (!rChange)
        {
          th_Val[4].r_t = ((float) r_h * thErrON);
          th_Val[4].g_t = ((float) g_h * thErrON);
          th_Val[4].b_t = ((float) b_h * thErrOFF);
          break;
        }
      }
      while ((r > th_Val[0].r_t) | (g > th_Val[0].g_t)) //wait until red and green is LOW
      {
        tcs.getRawData(&r, &g, &b, &c);
      }
      Serial.print(".");
      //R0B
      while ((r < th_Val[0].r_t) | (b < th_Val[0].b_t)) //wait until red and blue is HIGH
      {
        tcs.getRawData(&r, &g, &b, &c);
      }
      delay(setupWaitTime);
      //set threshold for red-blue high
      r_h = g_h = b_h = 0;
      while (true)
      {
        bool rNotChage = true;
        tcs.getRawData(&r, &g, &b, &c); //get env info
        if (r > r_h)
        {
          rNotChage = false;
          r_h = r;
          if (g_h < g)
          {
            g_h = g;
          }
        }
        if (b > b_h)
        {
          b_h = b;
          if (g_h < g)
          {
            g_h = g;
          }
        }
        else if (rNotChage)
        {
          th_Val[5].r_t = ((float) r_h * thErrON);
          th_Val[5].g_t = ((float) g_h * thErrOFF);
          th_Val[5].b_t = ((float) b_h * thErrON);
          break;
        }
      }

      while ((r > th_Val[0].r_t) | (b > th_Val[0].b_t)) //wait until red and blue is LOW
      {
        tcs.getRawData(&r, &g, &b, &c);
      }
      Serial.print(".");
      //0GB
      while ((g < th_Val[0].g_t) | (b < th_Val[0].b_t)) //wait until green and blue is HIGH
      {
        tcs.getRawData(&r, &g, &b, &c);
      }
      delay(setupWaitTime);
      //set threshold for green-blue high
      r_h = g_h = b_h = 0;
      while (true)
      {
        bool bNotCHANGE = true;
        tcs.getRawData(&r, &g, &b, &c); //get env info
        if (b > b_h)
        {
          bNotCHANGE = false;
          b_h = b;
          if (r_h < r)
          {
            r_h = r;
          }
        }
        if (g > g_h)
        {
          g_h = g;
          if (r_h < r)
          {
            r_h = r;
          }
        }
        else if (bNotCHANGE)
        {
          th_Val[6].r_t = ((float) r_h * thErrOFF);
          th_Val[6].g_t = ((float) g_h * thErrON);
          th_Val[6].b_t = ((float) b_h * thErrON);
          break;
        }
      }
      while ((g > th_Val[0].g_t) | (b > th_Val[0].b_t)) //wait until green and blue is LOW
      {
        tcs.getRawData(&r, &g, &b, &c);
      }
      Serial.print(".");
      //RGB
      while ((g < th_Val[0].g_t) | (b < th_Val[0].b_t) | (r < th_Val[0].r_t)) //wait until red, green and blue is HIGH
      {
        tcs.getRawData(&r, &g, &b, &c);
      }
      delay(setupWaitTime);
      //set threshold for red-green-blue high
      r_h = g_h = b_h = 0;
      while (true)
      {
        bool anyChange = false;
        tcs.getRawData(&r, &g, &b, &c); //get env info
        if (r > r_h)
        {
          anyChange = true;
          r_h = r;
        }
        if (g > g_h)
        {
          anyChange = true;
          g_h = g;
        }
        if (b_h < b)
        {
          anyChange = true;
          b_h = b;
        }
        if (!anyChange)
        {
          th_Val[7].r_t = ((float) r_h * thErrON);
          th_Val[7].g_t = ((float) g_h * thErrON);
          th_Val[7].b_t = ((float) b_h * thErrON);
          break;
        }
      }

      while ((g > th_Val[0].g_t) | (b > th_Val[0].b_t) | (r > th_Val[0].r_t)) //wait until red, green and blue is HIGH
      {
        tcs.getRawData(&r, &g, &b, &c);
      }
      Serial.println("Done");
      //print env values
      for (int j = 0; j < 8; j++)
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
      Serial.println("Ready...");
    }
    else
    {
      digitalWrite(greenLED, HIGH);
      Serial.print("Sent:");
      //Serial.print("\n");
      for (int j = 0; j < inputHOLD.length(); ++j)
      {
        if ((j % 80) == 0)
          Serial.print("\n");

        flashSequence(inputHOLD[j]);
      }
      flashSequence('\n');
      //   Serial.print("\n");
    }
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  }
}

void flashSequence(char sequence)
{

  encodeASCII(sequence, buff[2], buff[4], buff[5], buff[6], buff[8], buff[9], buff[10], buff[11]);
  addParity(buff[2], buff[4], buff[5], buff[6], buff[8], buff[9], buff[10], buff[11], buff[0], buff[1], buff[3], buff[7]);


  Serial.print(sequence); //for testing **********************************************
  //Serial.print(": ");

  tcs.getRawData(&r, &g, &b, &c);
  while (g < th_Val[2].g_t)
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  digitalWrite(greenLED, LOW);

  while (g > th_Val[0].g_t)
  {
    tcs.getRawData(&r, &g, &b, &c);
  }
  bool first = true;
  int j = 0;
  while (j < 12)
  {
    if (!first)
    {
      tcs.getRawData(&r, &g, &b, &c); //store environment values
      while (b > th_Val[0].b_t)
      {
        tcs.getRawData(&r, &g, &b, &c); //store environment values
      }
    }

    first = false;

    flashDotOrDash(redLED, buff[j]);
    j++;

    flashDotOrDash(greenLED, buff[j]);
    j++;

    flashDotOrDash(blueLED, buff[j]);
    j++;
    if (j < 12)
    {
      while (b < th_Val[3].b_t)
      {
        tcs.getRawData(&r, &g, &b, &c); //store environment values
      }
    }
    else
    {
      while (r < th_Val[1].r_t)
      {
        tcs.getRawData(&r, &g, &b, &c); //store environment values
      }
    }
    flashDotOrDash(redLED, false);
    flashDotOrDash(blueLED, false);
    flashDotOrDash(greenLED, false);
    // Serial.print(" ");
    delay(trnsDELAY);
  }
  //Serial.println(); //for testing **************************************

}

void synchronization()
{
  digitalWrite(redLED, HIGH);
  delay(initDelay);
  digitalWrite(redLED, LOW);
  delay(initDelay);

  digitalWrite(greenLED, HIGH);
  delay(initDelay);
  digitalWrite(greenLED, LOW);
  delay(initDelay);

  digitalWrite(blueLED, HIGH);
  delay(initDelay);
  digitalWrite(blueLED, LOW);
  delay(initDelay);

  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, HIGH);
  delay(initDelay);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  delay(initDelay);

  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, HIGH);
  delay(initDelay);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(initDelay);

  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  delay(initDelay);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  delay(initDelay);

  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(blueLED, HIGH);
  delay(initDelay);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
}

void flashDotOrDash(int color, bool dotOrDash)
{
  // Serial.print(dotOrDash); //for testing ******************************************
  if (dotOrDash)
    digitalWrite(color, HIGH);
  else
    digitalWrite(color, LOW);
}

void ledControl(int led)
{
  if (led == 0)
  {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  }
  else if (led == 1)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  }
  else if (led == 2)
  {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, LOW);
  }
  else if (led == 3)
  {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
  }
  else if (led == 4)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, LOW);
  }
  else if (led == 5)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
  }
  else if (led == 6)
  {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, HIGH);
  }
  else if (led == 7)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, HIGH);
  }
  else
    Serial.println("Please enter a number between 0 and 7!!");
}

void randomLed()
{
  Serial.println("Party mode ON!!!!!!!!");
  int readRand;
  int dly = 50;
  while (true)
  {
    if (Serial.available() > 0)
    {
      inputHOLD = Serial.readString();
      if (inputHOLD == "quit")
        break;
      else
      {
        dly = 25 * ((int) inputHOLD[0] - 48);
        if (dly < 0)
        {
          dly = -1 * dly;
        }
        if (dly > 500)
        {
          Serial.println("Troll was here");
          dly = 500;
        }
        Serial.print("Current delay is ");
        Serial.println(dly);
      }

    }
    readRand = random(8);
    ledControl(readRand);
    delay(dly);
  }
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);

}

