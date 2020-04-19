#include <avr/pgmspace.h>
#include "code.h"

#define TX_PIN 7
#define BUTTON_PIN 2
#define LED_PIN 13

//#define PERIODIC

//uint32_t t0;

//400 -> 853
//800 -> 854
//1200 -> 891
//1600 -> 892

//typedef struct
//{
//  uint16_t len;
//  uint8_t pol;
//} pulse_t;
//
//#define BIT_0 {683, 0}, {341, 1}
//#define BIT_1 {341, 0}, {683, 1}
//pulse_t packet[]={  BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//
//                     BIT_1,
//                     BIT_0,
//                     BIT_0,
//                     BIT_1,
//                     BIT_1,
//                     {10000,0},
//                     {0,0}};

void setup()
{
	pinMode(TX_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, 0);
  Serial.begin(115200);
}

//void sendPulse(uint8_t hl, uint16_t t)
//{
//  digitalWrite(TX_PIN, hl);
//  delayMicroseconds(t-(micros()-t0));
//}

void loop()
{
//  uint16_t nextPulse;
//  uint8_t pulseCounter;
  uint32_t code;
  int8_t pos;
  uint8_t rep;

  digitalWrite(LED_PIN, 0);
  delay(500);


//code=21
//code=0b1000000000000 kornyeke (1000000010011)
  for (code=0b1000000000000; code<=0b1111111111111; code++)
  {
    for (rep=0; rep<40; rep++)
    {
      for (pos=12; pos>=0; pos--)
      {
        if ((code & (1UL<<pos)) != 0)
        {
          digitalWrite(LED_PIN, 1);
          digitalWrite(TX_PIN, 0);
          delayMicroseconds(300);
          digitalWrite(TX_PIN, 1);
          delayMicroseconds(600);
        }
        else
        {
          digitalWrite(LED_PIN, 0);
          digitalWrite(TX_PIN, 0);
          delayMicroseconds(600);
          digitalWrite(TX_PIN, 1);
          delayMicroseconds(300);
        }
      }
      digitalWrite(TX_PIN, 0);
      digitalWrite(LED_PIN, 0);
      Serial.print(code, BIN);
      Serial.print("\n");
      delayMicroseconds(2000);
    }
  }
  digitalWrite(TX_PIN, 0);
  digitalWrite(LED_PIN, 0);
  while(1);
}
