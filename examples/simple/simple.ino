#include <ButtonHandler.h>

ButtonHandler Btn;
void setup(){
  pinMode(2,INPUT_PULLUP);
}

void loop(){
  int events = Btn.events(digitalRead(2));
}
