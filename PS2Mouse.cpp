/*
 * Copyright (c) 2015 Evan Kale
 * Email: EvanKale91@gmail.com
 * Website: www.ISeeDeadPixel.com
 *          www.evankale.blogspot.ca
 *
 * This file is part of ArduinoBTPS2.
 *
 * ArduinoBTPS2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//PS2 mouse references:
//http://wiki.osdev.org/PS/2_Mouse
//https://www.win.tue.nl/~aeb/linux/kbd/scancodes-13.html

#include "PS2Mouse.h"

#define _DEBUG 0

PS2Mouse::PS2Mouse(uint8_t clockPin, uint8_t dataPin)
	:PS2Device(clockPin, dataPin)
{
	_isInitialized = false;
}

PS2Mouse::~PS2Mouse()
{
}

bool PS2Mouse::init()
{
	bool resetStatus = initReset();
	if (!resetStatus)
		return false;

	
	initCheckMouseWheel();
	initCheck5Buttons();
	initSetStreamMode();

	delayMicroseconds(100);

	_mouseState.btnState1 = 0;
	_mouseState.btnState2 = 0;
	_mouseState.deltaX = 0;
	_mouseState.deltaY = 0;
	_mouseState.deltaZ = 0;
	_mouseState.newStateAvailable = false;

	_isInitialized = true;

	return true;
}

bool PS2Mouse::initReset()
{
	bool resetStatus = write(0xff, true);  // Reset signal - 0xFF

	if (!resetStatus)
	{
#if _DEBUG
		Serial.println("PS2Mouse init timed out");
#endif
		return false;
	}

	read(NULL, false);  // Acknowledge - 0xFA

	// Self-test result, 0xAA00 when OK, 0xFC00 on error
	uint8_t result = 0x00;
	read(&result, false);
	read(NULL, false);

	if (result != 0xAA)
	{
#if _DEBUG
		Serial.println("PS2Mouse init result error");
#endif
		return false;
	}

	return true;
}

void PS2Mouse::initSetStreamMode()
{
	write(0xE8, false);		// Set resolution
	read(NULL, false);		// Acknowledge - 0xFA
	write(0x02, false);		// 4 Counts / mm
	read(NULL, false);		// Acknowledge - 0xFA
	write(0xE6, false);		// Set Scaling 1 : 1
	read(NULL, false);		// Acknowledge - 0xFA
	write(0xF3, false);		// Set Sample Rate
	read(NULL, false);		// Acknowledge - 0xFA
	write(0x64, false);		// decimal 100
	read(NULL, false);		// Acknowledge - 0xFA
	write(0xEA, false);		// set stream mode
	read(NULL, false);		// Acknowledge - 0xFA
	write(0xF4, false);		// Enable data reporting
	read(NULL, false);		// Acknowledge - 0xFA

	//write(0xf0, false);  // Set Remote Mode signal - 0xFF
	//read(NULL, false);  // Acknowledge - 0xFA

}

void PS2Mouse::initCheckMouseWheel()
{
	// Check for mouse wheel by sending the intellimouse sequence (f3 c8 f3 64 f3 50)
	// Every command is followed by an acknowledge byte return
	write(0xf3, false);
	read(NULL, false);
	write(0xC8, false);
	read(NULL, false);
	write(0xf3, false);
	read(NULL, false);
	write(0x64, false);
	read(NULL, false);
	write(0xf3, false);
	read(NULL, false);
	write(0x50, false);
	read(NULL, false);

	// Get Device ID after intellimouse sequence
	// 0x03 returned if mouse is intellimouse (ie, has mouse wheel)
	write(0xf2, false);  // Get Device ID signal
	read(NULL, false);  // Acknowledge - 0xFA
	uint8_t deviceID = 0x00;
	read(&deviceID, false);
	if (deviceID == 0x03)
		_hasMouseWheel = true;
	else
		_hasMouseWheel = false;

#if _DEBUG
	Serial.print("Device ID = ");
	Serial.println(deviceID, DEC);
#endif
}

void PS2Mouse::initCheck5Buttons()
{
	//this check is only valid after intellimouse sequence check returns valid (ie, has mouse wheel)
	if (_hasMouseWheel)
	{
		// Check for 5-btn mouse by sending the intellimouse explorer sequence (f3 c8 f3 c8 f3 50)
		// Every command is followed by an acknowledge byte return
		write(0xf3, false);
		read(NULL, false);
		write(0xC8, false);
		read(NULL, false);
		write(0xf3, false);
		read(NULL, false);
		write(0xC8, false);
		read(NULL, false);
		write(0xf3, false);
		read(NULL, false);
		write(0x50, false);
		read(NULL, false);

		// Get Device ID after intellimouse explorer sequence
		// 0x04 returned if mouse is intellimouse (ie, has 5 btns)
		write(0xf2, false);  // Get Device ID signal
		read(NULL, false);  // Acknowledge - 0xFA
		uint8_t deviceID = 0x00;
		read(&deviceID, false);
		if (deviceID == 0x04)
			_has5Btns = true;
		else
			_has5Btns = false;

#if _DEBUG
		Serial.print("Device ID = ");
		Serial.println(deviceID, DEC);
#endif
	}
}

int16_t PS2Mouse::getDeltaX()
{
	return _mouseState.deltaX;
}

int16_t PS2Mouse::getDeltaY()
{
	return _mouseState.deltaY;
}


int8_t PS2Mouse::getDeltaZ()
{
	return _mouseState.deltaZ;
}

uint8_t PS2Mouse::getBtnState()
{
	return _mouseState.btnState2;
}

bool PS2Mouse::available()
{
	if (!_isInitialized)
		return false;
	
	if (tryRead())
		return true;

	return false;
}

bool PS2Mouse::tryRead()
{
	uint8_t byte1 = 0x00;

	if (read(&byte1, true))
	{
		uint8_t byte2 = 0x00;
		uint8_t byte3 = 0x00;
		read(&byte2, false);
		read(&byte3, false);

		uint8_t byte4 = 0x00;
		if (_hasMouseWheel)
		{
			read(&byte4, false);
		}

		//bit 0, 1, 2 of byte1 holds button states
		_mouseState.btnState2 = byte1 & 0b00000111;

		if (_has5Btns)
		{
			_mouseState.btnState2 |= (byte4 & 0b00110000) >> 1;
		}

		//xy deltas are 9-bit two's complement values
		//bit 0..8 of byte2/3 holds the delta value
		//bit 4/5 of byte1 holds the sign

		//get xy-axis delta values
		_mouseState.deltaX = byte2;
		_mouseState.deltaY = byte3;

		//bit 4 of byte1 holds X-Axis sign bit
		if ((byte1 >> 4) & 1)
		{
			//set short as negative
			_mouseState.deltaX |= 0xFF00;
		}

		//bit 5 of byte1 holds Y-Axis sign bit
		if ((byte1 >> 5) & 1)
		{
			//set short as negative
			_mouseState.deltaY |= 0xFF00;
		}

		if (_hasMouseWheel)
		{
			//byte4 is available if mouse has a wheel (and was activated by the intellimouse sequence)
			//bit 0..4 holds mouse wheel (Z-axis) delta in two's complement
			//ie, bit 0..3 holds value, bit 4 holds sign

			_mouseState.deltaZ = byte4 & 0b00000111;
			if ((byte4 >> 3) & 1)
			{
				_mouseState.deltaZ |= 0b11111000;
			}

		}

		if (!(_mouseState.deltaX == 0								//not no movement
			&& _mouseState.deltaY == 0
			&& _mouseState.deltaZ == 0)
			|| (_mouseState.btnState2 != _mouseState.btnState1))	// or button states have changed
		{
			_mouseState.newStateAvailable = true;
			_mouseState.btnState1 = _mouseState.btnState2;
#if _DEBUG
			printMouseState();
#endif
		}

		return true;
	}
	return false;
}

void PS2Mouse::printMouseState()
{
#if _DEBUG
	Serial.print("dX = ");
	Serial.print(_mouseState.deltaX);
	Serial.print("   dY = ");
	Serial.print(_mouseState.deltaY);
	Serial.print("   btn = ");
	Serial.print(_mouseState.btnState2, BIN);
	Serial.print("   wheel = ");
	Serial.print(_mouseState.deltaZ);
	Serial.println();
#endif
}
