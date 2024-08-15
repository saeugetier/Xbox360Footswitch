#include <Arduino.h>
#include <USBComposite.h>

USBXBox360 XBox360;

struct x360PinMapping
{
  uint8_t pin;
  uint8_t button;
  bool buttonState;
  bool latchedState;
};

x360PinMapping pinButtonMapping[] = {
  {PA0, XBOX_DUP, false, false},
  {PA1, XBOX_DDOWN, false, false},
  {PA2, XBOX_DLEFT, false, false},
  {PA3, XBOX_DRIGHT, false, false},
  {PA4, XBOX_START, false, false},
  {PA5, XBOX_BACK, false, false},
  {PA6, XBOX_LSHOULDER, false, false},
  {PA7, XBOX_RSHOULDER, false, false},
  {PA8, XBOX_GUIDE, false, false},
  {PA9, XBOX_A, false, false},
  {PA10, XBOX_B, false, false},
  {PA15, XBOX_X, false, false},
  {PB0, XBOX_Y, false, false}
};

int blinkDelay = 0;


void setup() 
{
  XBox360.begin();
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, HIGH);
  for(int i = 0; i < sizeof(pinButtonMapping) / sizeof(x360PinMapping); i++)
  {
    pinMode(pinButtonMapping[i].pin, INPUT_PULLUP);
  }

  //while (!USBComposite);
}

void loop() 
{
  uint16_t buttons = 0;
  
  for(int i = 0; i < sizeof(pinButtonMapping) / sizeof(x360PinMapping); i++)
  {
    bool pressed = !digitalRead(pinButtonMapping[i].pin);
    if(pressed == pinButtonMapping[i].buttonState)
    {
      pinButtonMapping[i].latchedState = pressed;
    }
    else
    {
      pinButtonMapping[i].buttonState = pressed;
    }

    if(pinButtonMapping[i].latchedState)
    {
      buttons |= 1 << (pinButtonMapping[i].button - 1);
    }
  }

  XBox360.buttons(buttons);
  
  delay(1); 

    blinkDelay++;
  
  if(blinkDelay == 10)
  {
     digitalWrite(PC13,!digitalRead(PC13));
     blinkDelay = 0;
  }
  
}
