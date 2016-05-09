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

#include "Bluetooth.h"
#include "PS2Keyboard.h"

Bluetooth::Bluetooth()
{
}

Bluetooth::~Bluetooth()
{
}

void Bluetooth::sendMouseState(uint8_t btnState, uint8_t deltaX, uint8_t deltaY, uint8_t deltaZ)
{
	Serial.write((uint8_t)0xFD);
	Serial.write((uint8_t)0x05);
	Serial.write((uint8_t)0x02);
	Serial.write(btnState);
	Serial.write(deltaX);
	Serial.write(deltaY);
	Serial.write(deltaZ);
}

void Bluetooth::sendKeyboardState(uint8_t modifiers, uint8_t * keysPressed)
{
	Serial.write((uint8_t)0xFD);
	Serial.write((uint8_t)0x09);
	Serial.write((uint8_t)0x01);
	Serial.write(modifiers);
	Serial.write((uint8_t)0x00);
	for (uint8_t i = 0; i < MAX_KEYS_PRESSED; ++i)
	{
		Serial.write(keysPressed[i]);
	}
}

void Bluetooth::sendConsumerReport(uint16_t consumerKeys)
{
	Serial.write((uint8_t)0xFD);
	Serial.write((uint8_t)0x00);
	Serial.write((uint8_t)0x02);
	Serial.write((uint8_t)((consumerKeys >> 8) & 0xFF));
	Serial.write((uint8_t)(consumerKeys & 0xFF));
	Serial.write((uint8_t)0x00);
	Serial.write((uint8_t)0x00);
	Serial.write((uint8_t)0x00);
	Serial.write((uint8_t)0x00);
}

void Bluetooth::getKeyboardLEDState()
{
	Serial.write((uint8_t)0xFF);
	Serial.write((uint8_t)0x02);

	//TODO
	//what to read from BT device?
}
