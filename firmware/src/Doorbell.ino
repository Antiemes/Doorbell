#include <avr/pgmspace.h>

#define TX_PIN 7
#define BUTTON_PIN 2
#define LED_PIN 13

void setup()
{
	pinMode(TX_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, 0);
  Serial.begin(115200);
}

void loop()
{
  int8_t pos;
  uint8_t rep;

  digitalWrite(LED_PIN, 0);
  delay(500);

	uint32_t id=14;
	uint32_t pattern;

	pattern=0b10011; //Full chime
	//pattern=0b10101; //Short chime, ding-ding
	//pattern=0b11001; //Short chime, ding-dong


	uint32_t code=(id<<7) | pattern;
	//code |= 0x1000; //First bit can be set to 0 or 1 (ignored)

//  for (code=0b0011110000000; code<=0b1111111111111; code++)
//  {
    for (rep=0; rep<100; rep++)
    {
      for (pos=12; pos>=0; pos--)
      {
        if ((code & (1UL<<pos)) != 0)
        {
          digitalWrite(LED_PIN, 1);
          digitalWrite(TX_PIN, 0);
          delayMicroseconds(338);
          digitalWrite(TX_PIN, 1);
          delayMicroseconds(675);
        }
        else
        {
          digitalWrite(LED_PIN, 0);
          digitalWrite(TX_PIN, 0);
          delayMicroseconds(675);
          digitalWrite(TX_PIN, 1);
          delayMicroseconds(338);
        }
      }
      digitalWrite(TX_PIN, 0);
      digitalWrite(LED_PIN, 0);
      Serial.print(code, BIN);
      Serial.print("\n");
      delayMicroseconds(11084);
    }
//  }
  digitalWrite(TX_PIN, 0);
  digitalWrite(LED_PIN, 0);
	//code^=0b0110000000000;
	delay(10000);
  //while(1);
}
