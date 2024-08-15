#include <Arduino.h>
#include <USBComposite.h>

USBXBox360 XBox360;

void setup() {
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, HIGH);
  XBox360.begin();  
  while (!USBComposite);
}

void loop() {
  XBox360.X(-32767);
  XBox360.Y(-32767);
  digitalWrite(PC13, HIGH);
  delay(1000);  
  XBox360.X(32767);
  XBox360.Y(32767);
  XBox360.button(0, 1);
  digitalWrite(PC13, LOW);
  delay(1000);  
}