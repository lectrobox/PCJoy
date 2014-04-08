#include <PCJoy.h>

PCJoy myJoy(A0, A1, 6, 7);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Query the joystick for its state
  PCJoy_State joyState = myJoy.getState();
  
  // Print the state
  if (joyState.isConnected)
  {
    // X position
    Serial.print("x=");
    Serial.print(joyState.xPos);
    Serial.print(" (");
    
    if (joyState.isLeft) {
      Serial.print("left");
    } else if (joyState.isRight) {
      Serial.print("right");
    } else {
      Serial.print("horiz-center");
    }
    Serial.print(")");
    
    // Y position
    Serial.print(" y=");
    Serial.print(joyState.yPos);
    Serial.print(" (");
    if (joyState.isUp) {
      Serial.print("up");
    } else if (joyState.isDown) {
      Serial.print("down");
    } else {
      Serial.print("vert-center");
    }
    Serial.print(")");
    
    // Button state
    Serial.print(" a=");
    Serial.print(joyState.aDown ? "DOWN" : " UP ");
    Serial.print(" b=");
    Serial.print(joyState.bDown ? "DOWN" : " UP ");
  }
  else
  {
    Serial.print("Joystick disconnected");
  }
  
  Serial.println();
  
  delay(200);
}

  

