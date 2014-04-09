Library for the Lectrobox Arduino PC Joystick Shield for 15-pin PC joysticks
============================================================================

This is the Arduino library for the Lectrobox PC Joystick Shield. More
information can be found at

http://lectrobox.com/joystick

The shield lets you attach any old-style PC joystick with a 15-pin
game port interface to your Arduino. (USB joysticks are not supported.)

The X and Y movement of the stick are returned in steps from -100
(fully up or left) to +100 (fully down or right). Your sketch can also
detect button-pushes for up to two joystick buttons.

The shield has jumpers that allow configuration which of the Arduino's
analog and digital input pins are used. The X and Y axes can use your
choice of analog inputs A0, A1, A2 and A3; the buttons can use digital
inputs 6, 7, 8, or 9. This flexibility ensures maximum compatibility
by letting you avoid pin conflicts if your sketch is using other
Arduino pins. Jumpers can be left off completely if the functions are
not needed.

The library requires four values when initialized, for example:

  PCJoy myJoy(A0, A1, 6, 7);

These four values indicate which analog (X, Y) and digital (button 1,
button 2) pins are in use and should match the values configured with
the physical jumpers on the shield.

The Joystick Shield comes with Arduino Stacking Headers, making it
easy to combine with other shields to build more complex sketches.
You can stack two of the Joystick Shields on top of each other and use
two separate joysticks from your sketch by setting the digital and
analog inputs of the two shields to non-conflicting values.

The shield also comes with a prototyping area consisting of a 15x8
matrix of 0.1" spaced holes, useful if your project needs space for
other discrete components.

A joystick with a 15-pin game port interface is required, and not
included with the shield. (USB Joysticks are not supported.)  If you
don't have a game-port joystick in your junk drawer, many are
available at low cost from your local thrift store, PC recycling shop,
and auction web sites such as EBay.
