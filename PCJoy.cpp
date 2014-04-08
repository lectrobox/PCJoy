//
// Lectrobox PC Joystick Shield
// Arduino library v1.0, Feb 2014
// This code is in the public domain. Enjoy!
//
// info@lectrobox.com
//


#include "Arduino.h"
#include "PCJoy.h"

PCJoy::PCJoy(uint8_t xChan, uint8_t yChan, uint8_t aChan, uint8_t bChan)
{
	_xChan = xChan;
	_yChan = yChan;
	_aChan = aChan;
	_bChan = bChan;

	pinMode(_aChan, INPUT_PULLUP);
	pinMode(_bChan, INPUT_PULLUP);

	_prevState.isLeft = false;
	_prevState.isRight = false;
	_prevState.isUp = false;
	_prevState.isDown = false;
}

int8_t PCJoy::_adcTo100(uint16_t adc)
{
	int32_t retval = ((int32_t) 79794 / adc) - 178;

	if (retval < -99)
		return -99;
	else if (retval > 99)
		return 99;
	else
		return retval;
}

#define ACTUATION_THRESHOLD 50
#define RELEASE_THRESHOLD 30

PCJoy_State PCJoy::getState(void)
{
	PCJoy_State retval = _prevState;

	uint16_t xAdc = analogRead(_xChan);
	uint16_t yAdc = analogRead(_yChan);

	retval.isConnected = xAdc >= 10 && yAdc >= 10;

	if (!retval.isConnected) {
		return retval;
	}

	// Serial.print(xAdc);
	// Serial.print("\t");
	// Serial.print(yAdc);
	// Serial.println("");

	retval.xPos = _adcTo100(xAdc);
	retval.yPos = _adcTo100(yAdc);

	// Compute the left/right/up/down bits using histeresis.
	if (retval.xPos < -ACTUATION_THRESHOLD)
		retval.isLeft = true;
	if (retval.xPos > -RELEASE_THRESHOLD)
		retval.isLeft = false;
	if (retval.xPos > ACTUATION_THRESHOLD)
		retval.isRight = true;
	if (retval.xPos < RELEASE_THRESHOLD)
		retval.isRight = false;

	if (retval.yPos < -ACTUATION_THRESHOLD)
		retval.isUp = true;
	if (retval.yPos > -RELEASE_THRESHOLD)
		retval.isUp = false;
	if (retval.yPos > ACTUATION_THRESHOLD)
		retval.isDown = true;
	if (retval.yPos < RELEASE_THRESHOLD)
		retval.isDown = false;
		
	retval.aDown = digitalRead(_aChan) == HIGH ? false : true;
	retval.bDown = digitalRead(_bChan) == HIGH ? false : true;

	_prevState = retval;
	return retval;
}

