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

#ifndef PS2MOUSE_H
#define PS2MOUSE_H

#include "PS2Device.h"
#include <Arduino.h>


struct PS2MouseState
{
	uint8_t btnState1;
	uint8_t btnState2;
	int16_t deltaX;
	int16_t deltaY;
	int8_t deltaZ;
	bool newStateAvailable;
};

class PS2Mouse : public PS2Device
{
public:
	PS2Mouse(uint8_t clockPin, uint8_t dataPin);
	~PS2Mouse();
	bool init();
	bool available();
	int16_t getDeltaX();
	int16_t getDeltaY();
	int8_t getDeltaZ();
	uint8_t getBtnState();
		
private:
	PS2MouseState _mouseState;
	bool _hasMouseWheel;
	bool _has5Btns;
	bool _isInitialized;
	bool initReset();
	void initSetStreamMode();
	void initCheckMouseWheel();
	void initCheck5Buttons();
	bool tryRead();
	void printMouseState();	
};

#endif //PS2MOUSE_H

