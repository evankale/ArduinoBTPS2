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

#include "PS2Keyboard.h"
#include "BTKeyCodes.h"
#include "KeyTable.h"

//PS2 keycodes:
//http://www.computer-engineering.org/ps2keyboard/scancodes2.html

#define _DEBUG 0

PS2Keyboard::PS2Keyboard(uint8_t clockPin, uint8_t dataPin)
	:PS2Device(clockPin, dataPin)
{
	_isInitialized = false;

	for (uint8_t i = 0; i < MAX_KEYS_PRESSED; ++i)
		_keyPressed[i] = BTKC_NONE;

	_keyModifiers = BTMC_NONE;
	_consumerKeys = BTCC_NONE;
	_consumerKeysChanged = false;
}

PS2Keyboard::~PS2Keyboard()
{
}

bool PS2Keyboard::init()
{
	bool resetStatus = initReset();
	if (!resetStatus)
		return false;

	delayMicroseconds(100);

	_isInitialized = true;
	return true;
}

uint8_t * PS2Keyboard::getKeysPressed()
{
	return _keyPressed;
}

uint8_t PS2Keyboard::getKeyModifiers()
{
	return _keyModifiers;
}

uint16_t PS2Keyboard::getConsumerKeys()
{
	_consumerKeysChanged = false;
	return _consumerKeys;
}

bool PS2Keyboard::initReset()
{
	bool resetStatus = write(0xff, false);  // Reset signal - 0xFF

	if (!resetStatus)
	{
#if _DEBUG
		Serial.println("PS2Keyboard init timed out");
#endif
		return false;
	}

	read(NULL, false);  // Acknowledge - 0xFA

	// Self-test result, 0xAA00 when OK, 0xFC00 on error
	uint8_t result = 0x00;
	read(&result, false);

	if (result != 0xAA)
	{
#if _DEBUG
		Serial.println("PS2Keyboard init result error");
#endif
		return false;
	}

	return true;
}

bool PS2Keyboard::available()
{
	if (!_isInitialized)
		return false;

	if (tryRead())
		return true;

	return false;
}

bool PS2Keyboard::consumerKeysAvailable()
{
	if (!_isInitialized)
		return false;

	return _consumerKeysChanged;
}

bool PS2Keyboard::tryRead()
{
	uint8_t keyCode;
	uint8_t btCode = BTKC_NONE;
	bool pressed = false;

	if (read(&keyCode, true))
	{
		//Serial.println(keyCode, HEX);

		//Read the rest of the incoming bytes with blocking

		if (keyCode == 0xF0) //a standard key released
		{
			read(&keyCode, false);
			//Serial.println(keyCode, HEX);

			btCode = KeyTable::getBTCode(keyCode, false);
			pressed = false;
		}
		else if (keyCode == 0xE0) //an extended key
		{
			read(&keyCode, false);
			//Serial.println(keyCode, HEX);

			if (keyCode == 0xF0) //an extended key released
			{
				read(&keyCode, false);
				//Serial.println(keyCode, HEX);

				//The one exception to this case is Print Screen
				// Make: E0,12,E0,7C
				// Break: E0,F0,7C,E0,F0,12
				// So hardcode the case where 7C is read
				if (keyCode == 0x7C)
				{
					keyCode = 0x12;
					//skip over remaining 3 bytes
					read(NULL, false);
					read(NULL, false);
					read(NULL, false);
				}

				btCode = KeyTable::getBTCode(keyCode, true);
				pressed = false;
			}

			//The one exception to this case is Print Screen
			// Make: E0,12,E0,7C
			// Break: E0,F0,7C,E0,F0,12
			else if (keyCode == 0x12)
			{
				//skip over remaining 2 bytes
				read(NULL, false);
				read(NULL, false);
			}

			else //an extended key pressed
			{
				btCode = KeyTable::getBTCode(keyCode, true);
				pressed = true;
			}
		}
		else if (keyCode == 0xE1)
		{
			//There's only 1 E1 extension in the table of scancodes (PAUSE key)
			// (there's no release code for this key either)
			btCode = BTKC_PAUSE;
			pressed = true;

			//skip over remaning 7 bytes
			read(NULL, false);
			read(NULL, false);
			read(NULL, false);
			read(NULL, false);
			read(NULL, false);
			read(NULL, false);
			read(NULL, false);
		}
		else
		{
			btCode = KeyTable::getBTCode(keyCode, false);
			pressed = true;
		}

		return processKey(btCode, pressed);
	}	
	return false;
}

bool PS2Keyboard::processKey(uint8_t btCode, bool isPressed)
{
	bool stateUpdated = false;

	//check if is a virtual key
	if ((btCode >> 7) & 1)
	{
		if (0x80 <= btCode && btCode <= 0x87)
		{
			//0x80 to 0x87 are modifer keys
			// the lower 7 bits defines how much 0x1 is shifted left to get the modifier code
			// ie) BTKC_ALT_LEFT = 0x82 (10000010b)
			//       lower 7 bits = 0x02 (0000010b)
			//       0x1 << 2 = 100b = 0x04 = BTMC_ALT_LEFT

			uint8_t modifierBitNum = btCode & 0b01111111;

			//if pressed state and not already set in modifier state
			if (isPressed && !((_keyModifiers >> modifierBitNum) & 1))
			{
				//set the modifier state
				_keyModifiers |= (1 << modifierBitNum);
				stateUpdated = true;
			}
			//else if released state and is set in modifier state
			else if(!isPressed && (_keyModifiers >> modifierBitNum) & 1)
			{
				//clear the modifier state
				_keyModifiers &= ~(1 << modifierBitNum);
				stateUpdated = true;
			}

		}
		else if (0xC0 <= btCode && btCode <= 0xD0)
		{
			//0xC0 to 0xD0 are consumer keys
			// the lower 6 bits defines how much 0x1 is shifted left to get the 2 byte consumer code
			// ie) BTKC_VOLUME_UP = 0xC4 (11000100b)
			//       lower 6 bits = 0x04 (000100b)
			//       0x1 << 4 = 10000b = 0x0010 = BTCC_VOLUME_UP

			uint16_t consumerKeyBitNum = btCode & 0b00111111;

			//if pressed state and not already set in consumer key state
			if (isPressed && !((_consumerKeys >> consumerKeyBitNum) & 1))
			{
				//set the consumer key state
				_consumerKeys |= (1 << consumerKeyBitNum);
				stateUpdated = true;
				_consumerKeysChanged = true;
			}
			//else if released state and is set in consumer key state
			else if (!isPressed && (_consumerKeys >> consumerKeyBitNum) & 1)
			{
				//clear the consumer key state
				_consumerKeys &= ~(1 << consumerKeyBitNum);
				stateUpdated = true;
				_consumerKeysChanged = true;
			}
		}

	}

	//otherwise, it is just a bluetooth key code
	else
	{
		int8_t btCodeIndex = -1;
		int8_t nextAvailableSlot = -1;
		for (uint8_t i = 0; i < MAX_KEYS_PRESSED; ++i)
		{
			if (_keyPressed[i] == btCode)
			{
				btCodeIndex = i;
			}
			if (_keyPressed[i] == BTKC_NONE)
			{
				nextAvailableSlot = i;
			}
		}

		//if is pressed and not already in _keyPressed, then add to _keyPressed
		if (isPressed && btCodeIndex == -1 && nextAvailableSlot !=-1)
		{
			_keyPressed[nextAvailableSlot] = btCode;
			stateUpdated = true;
		}

		//else if is released and is in _keyPressed, then remove it from _keyPressed
		else if (!isPressed && btCodeIndex != -1)
		{
			_keyPressed[btCodeIndex] = BTKC_NONE;
			stateUpdated = true;
		}
	}


	return stateUpdated;
}

