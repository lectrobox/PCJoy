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
	PCJoy(uint8_t xAnalogPin, uint8_t yAnalogPin, uint8_t aDigitalPin, uint8_t bDigitalPin);
	PCJoy_State getState(void);

 private:
	uint8_t _xAnalogPin;
	uint8_t _yAnalogPin;
	uint8_t _aDigitalPin;
	uint8_t _bDigitalPin;
	PCJoy_State _prevState;

	static int8_t _adcTo100(uint16_t adc);
	int8_t _maybeReadPosition(uint8_t analogPin, PCJoy_State *retval);
	static bool _maybeReadButton(uint8_t digitalPin);
};

	

#endif // _PCJoy_h__
