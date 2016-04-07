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

#include "PS2Device.h"

PS2Device::PS2Device(uint8_t clockPin, uint8_t dataPin)
{
	_clockPin = clockPin;
	_dataPin = dataPin;
	gohi(_clockPin);
	gohi(_dataPin);
}

PS2Device::~PS2Device()
{
}

bool PS2Device::write(uint8_t data, bool enableTimeout)
{
	bool parity = true;

	gohi(_dataPin);
	gohi(_clockPin);
	delayMicroseconds(300);
	golo(_clockPin);
	delayMicroseconds(300);
	golo(_dataPin);
	delayMicroseconds(10);
	gohi(_clockPin);

	//wait for clock lo
	if (enableTimeout)
	{
		startTimeoutCtr();
		while (digitalRead(_clockPin) == HIGH && !hasTimedOut(TIMEOUT_WRITE_WAIT))
			; //busy wait
		if (_timedOut)
			return false;
	}
	else
	{
		while (digitalRead(_clockPin) == HIGH)
			; //busy wait
	}

	//data bits
	for (uint8_t i = 0; i < 8; i++)
	{
		if (data & (1 << i))
		{
			parity = !parity;
			gohi(_dataPin);
		}
		else
		{
			golo(_dataPin);
		}

		//clock cycle
		while (digitalRead(_clockPin) == LOW);
		while (digitalRead(_clockPin) == HIGH);
	}

	//parity bit
	if (parity)
		gohi(_dataPin);
	else
		golo(_dataPin);

	//clock cycle
	while (digitalRead(_clockPin) == LOW);
	while (digitalRead(_clockPin) == HIGH);

	//stop bit
	delayMicroseconds(30);
	gohi(_dataPin);
	
	//ack
	while (digitalRead(_clockPin) == HIGH);

	//mode switch
	while ((digitalRead(_clockPin) == LOW) || (digitalRead(_dataPin) == LOW));

	//hold up incoming data
	golo(_clockPin);

	return true;
}

bool PS2Device::read(uint8_t * data, bool enableTimeout)
{
	//clear data
	*data = 0;

	gohi(_dataPin);

	if(enableTimeout)
	{
		startTimeoutCtr();
		gohi(_clockPin);
		while (digitalRead(_clockPin) == HIGH  && !hasTimedOut(TIMEOUT_READ_WAIT))
			; //busy wait
		if (_timedOut)
		{
			//hold up incoming data
			golo(_clockPin);
			return false;
		}
	}
	else
	{
		gohi(_clockPin);
		while (digitalRead(_clockPin) == HIGH)
			; //busy wait
	}

	//start bit
	while (digitalRead(_clockPin) == LOW);

	//data bits
	for (uint8_t i = 0; i < 8; i++)
	{
		//wait for clock lo
		while (digitalRead(_clockPin) == HIGH);

		if (digitalRead(_dataPin) == HIGH && data != NULL)
		{
			*data |= (1 << i);
		}

		//wait for clock hi
		while (digitalRead(_clockPin) == LOW);
	}

	//parity bit (ignore it)
	while (digitalRead(_clockPin) == HIGH);
	while (digitalRead(_clockPin) == LOW);

	//stop bit
	while (digitalRead(_clockPin) == HIGH);
	while (digitalRead(_clockPin) == LOW);

	//hold incoming data
	golo(_clockPin);	

	return true;
}

void PS2Device::golo(uint8_t pin)
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

void PS2Device::gohi(uint8_t pin)
{
	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
}

void PS2Device::startTimeoutCtr()
{
	_timeoutStartCtr = micros();
	_timedOut = false;
}

bool PS2Device::hasTimedOut(uint64_t usecsToTimeOut)
{
	uint64_t deltaTime = micros() - _timeoutStartCtr;
	if (deltaTime > usecsToTimeOut)
	{
		_timedOut = true;
		return true;
	}

	return false;
}
