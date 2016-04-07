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
 
#ifndef  BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>

class Bluetooth
{
public:
	Bluetooth(uint32_t baudRate, bool useSoftwareSerial, uint8_t softwareRXPin, uint8_t softwareTXPin);
	~Bluetooth();

	void sendMouseState(uint8_t btnState, uint8_t deltaX, uint8_t deltaY, uint8_t deltaZ);
	void sendKeyboardState(uint8_t modifiers, uint8_t * keysPressed);
	void sendConsumerReport(uint16_t consumerKeys);
	void getKeyboardLEDState();

private:
	bool _useSoftwareSerial;
	Stream * _serialStream;
};

#endif // ! BLUETOOTH_H
