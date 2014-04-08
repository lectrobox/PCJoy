//
// Lectrobox PC Joystick Shield
// Arduino library v1.0, Feb 2014
// This code is in the public domain. Enjoy!
//
// info@lectrobox.com
//

#ifndef _PCJoy_h__
#define _PCJoy_h__

#include <stdint.h>

class PCJoy_State
{
 public:
	bool isConnected;
	bool aDown;
	bool bDown;
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	int8_t xPos;
	int8_t yPos;
};

class PCJoy
{
 public:
	PCJoy(uint8_t xChan, uint8_t yChan, uint8_t aChan, uint8_t bChan);
	PCJoy_State getState(void);

 private:
	uint8_t _xChan;
	uint8_t _yChan;
	uint8_t _aChan;
	uint8_t _bChan;
	PCJoy_State _prevState;

	int8_t _adcTo100(uint16_t adc);
};

	

#endif // _PCJoy_h__
