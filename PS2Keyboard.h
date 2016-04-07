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

#ifndef PS2KEYBOARD_H
#define PS2KEYBOARD_H

#include "PS2Device.h"
#include <Arduino.h>

#define MAX_KEYS_PRESSED 6

class PS2Keyboard : public PS2Device
{
public:
	PS2Keyboard(uint8_t clockPin, uint8_t dataPin);
	~PS2Keyboard();
	bool init();
	bool available();
	bool consumerKeysAvailable();
	uint8_t * getKeysPressed();
	uint8_t getKeyModifiers();
	uint16_t getConsumerKeys();
	
private:
	uint8_t _keyPressed[MAX_KEYS_PRESSED];	//stored as btCodes
	uint8_t _keyModifiers;
	uint16_t _consumerKeys;
	bool _consumerKeysChanged;
	bool _isInitialized;
	bool initReset();
	bool tryRead();
	bool processKey(uint8_t btCode, bool isPressed);
};

#endif //PS2KEYBOARD_H
