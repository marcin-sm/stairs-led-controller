#include <Arduino.h>

#include <ChainableLED.h>

#define NUM_LEDS  6
#define DATA_PIN 5 //1D1
#define CLOCK_PIN 4 //D2
#define STAIRS_SWITH 2 //D4
#define ANALOG A0

ChainableLED leds(CLOCK_PIN, DATA_PIN, NUM_LEDS);

void setup()
{
  //leds.init();
  pinMode(STAIRS_SWITH, INPUT_PULLUP);
  Serial.begin(9100);
}

int animation = 5;
int tresholdmax = 40;
int AnalogTreshold = 1020;
int LastState = LOW;

void lightsup();
void lightsdown();
void dim_black();
void black();


//leds.setColorRGB(i, R, G, B);
void loop()
{
  int SwitchState = analogRead(ANALOG);
  Serial.println(SwitchState);

  if (SwitchState > AnalogTreshold && LastState == LOW)
  {
    //lightsdown();
  
    //dim_black();
    
    lightsdown();
    LastState = HIGH;
    //dim_black();
  }
  
  else if (SwitchState < AnalogTreshold&& LastState == HIGH)
  {
    dim_black();
    black();
    LastState = LOW;
  }

  else

  {
    if (SwitchState > AnalogTreshold){LastState=HIGH;}
    else if (SwitchState < AnalogTreshold){LastState=LOW;}
    
    
  }

 
  
  delay(10);
}

   

 void lightsup()
 {
   for (int i=0; i<NUM_LEDS; i++)
  {
    for (int j=0; j<3; j++)
    {
      for (int b=0; b<(tresholdmax+1)/animation; b++)
      {
        if (j==0)
           leds.setColorRGB(i, 0, animation*b, 0);
        else if (j==1)
           leds.setColorRGB(i, animation*b, tresholdmax, 0);
        else if (j==2)
           leds.setColorRGB(i, tresholdmax, tresholdmax, animation*b);
        //Serial.println(b);
        delay(animation);
      }
    }
  }
 }

 void lightsdown()
 {
   for (int i=NUM_LEDS-1; i>=0; i--)
  {
    for (int j=3; j>0; j--)
    {
      for (int b=0; b<(tresholdmax+1)/animation; b++)
      {
        if (j==3)
           leds.setColorRGB(i, 0, 0, animation*b);
        else if (j==2)
           leds.setColorRGB(i, animation*b, 0, tresholdmax);
        else if (j==1)
           leds.setColorRGB(i, tresholdmax, animation*b, tresholdmax);
        //Serial.println(b);
        delay(5);
      }
    }
  }
 }

 void black()
 {
   for (int i=0; i<NUM_LEDS; i++)
  {
    leds.setColorRGB(i, 0, 0, 0);
  }
 }
 
 void dim_black ()
 {
  for (int b=0; b<(tresholdmax+1); b++)
  {
    for (int i=0; i<NUM_LEDS; i++)
    {

        leds.setColorRGB(i, tresholdmax-b, tresholdmax-b, tresholdmax-b);

        delay(5);
      }
  }
  black();
  } 
 

  void white()
 {
    for (int i=0; i<NUM_LEDS; i++)
  {
    leds.setColorRGB(i, 255, 255, 255);
  }
 }

 void randomise ()
 {
  //enjoy
 }
 
