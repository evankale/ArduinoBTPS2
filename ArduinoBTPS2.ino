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
 
#include "PS2Mouse.h"
#include "PS2Keyboard.h"
#include "Bluetooth.h"

#define MOUSE_CLOCK 2
#define MOUSE_DATA 3
#define KEYBOARD_CLOCK 4
#define KEYBOARD_DATA 5

#define HARDWARE_SERIAL_RATE 115200

PS2Mouse mouse(MOUSE_CLOCK, MOUSE_DATA);
PS2Keyboard keyboard(KEYBOARD_CLOCK, KEYBOARD_DATA);
Bluetooth bluetooth;

void setup()
{
  Serial.begin(HARDWARE_SERIAL_RATE);
	delay(300);
	mouse.init();
	keyboard.init();
}

void loop()
{
	if (mouse.available())
	{
		bluetooth.sendMouseState(mouse.getBtnState(), mouse.getDeltaX(), -mouse.getDeltaY(), -mouse.getDeltaZ());
	}

	if (keyboard.available())
	{
		bluetooth.sendKeyboardState(keyboard.getKeyModifiers(), keyboard.getKeysPressed());
	}

}
