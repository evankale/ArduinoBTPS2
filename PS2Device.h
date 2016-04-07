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

#ifndef PS2DEVICEDEBUG_H
#define PS2DEVICEDEBUG_H

#include <Arduino.h>

#define TIMEOUT_WRITE_WAIT 1000
#define TIMEOUT_READ_WAIT 1000


class PS2Device
{
public:
	PS2Device(uint8_t clockPin, uint8_t dataPin);
	virtual ~PS2Device();

protected:
	bool write(uint8_t data, bool enableTimeout);
	bool read(uint8_t * data, bool enableTimeout);
	void golo(uint8_t pin);
	void gohi(uint8_t pin);
	uint8_t _clockPin;
	uint8_t _dataPin;

private:
	void startTimeoutCtr();
	bool hasTimedOut(uint64_t usecsToTimeOut);
	uint64_t _timeoutStartCtr;
	bool _timedOut;
};


#endif //PS2DEVICEDEBUG_H
