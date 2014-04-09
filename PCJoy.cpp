//
// Lectrobox PC Joystick Shield
// Arduino library v1.0, Feb 2014
// This code is in the public domain. Enjoy!
//
// info@lectrobox.com
//


#include "Arduino.h"
#include "PCJoy.h"

PCJoy::PCJoy(uint8_t xAnalogPin, uint8_t yAnalogPin, uint8_t aDigitalPin, uint8_t bDigitalPin)
{
	_xAnalogPin = xAnalogPin;
	_yAnalogPin = yAnalogPin;
	_aDigitalPin = aDigitalPin;
	_bDigitalPin = bDigitalPin;

	if (_aDigitalPin > 0) {
		pinMode(_aDigitalPin, INPUT_PULLUP);
	}

	if (_bDigitalPin > 0) {
		pinMode(_bDigitalPin, INPUT_PULLUP);
	}

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

#define RAW_ADC_DISCONNECTED_THRESHOLD 10

bool PCJoy::_maybeReadButton(uint8_t digitalPin)
{
	if (digitalPin == 0)
		return false;
	else
		return digitalRead(digitalPin) == HIGH ? false : true;
}

// Read an analog stick axis position from the ADC and convert,
// IFF the channel is configured.
// Returns the -100 to +100 scale, and (as a side effect) will
// clear isConnected if a channel is defined and reads below threshold.
int8_t PCJoy::_maybeReadPosition(uint8_t analogPin, PCJoy_State *retval)
{
	if (analogPin > 0) {
		uint16_t adcVal = analogRead(analogPin);

		if (adcVal < RAW_ADC_DISCONNECTED_THRESHOLD) {
			retval->isConnected = false;
		} else {
			return _adcTo100(adcVal);
		}
	} else {
		// Analog channel not in use; return default value
		return 0;
	}
}

PCJoy_State PCJoy::getState(void)
{
	PCJoy_State retval = _prevState;

	uint16_t xAdc = 0;
	uint16_t yAdc = 0;

	// Read from the X and Y channels if they're in use.
	// If they are in use, also detect whether the joystick is connected.
	retval.isConnected = true;
	retval.xPos = _maybeReadPosition(_xAnalogPin, &retval);
	retval.yPos = _maybeReadPosition(_yAnalogPin, &retval);

	// If one of the analog channels is in use and detected
	// a disconnected joystick, return.
	if (!retval.isConnected) {
		return retval;
	}

	// Compute the left/right/up/down bits using hysteresis.
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

	// If buttons are in use, compute their states		
	retval.aDown = _maybeReadButton(_aDigitalPin);
	retval.bDown = _maybeReadButton(_bDigitalPin);

	_prevState = retval;
	return retval;
}

