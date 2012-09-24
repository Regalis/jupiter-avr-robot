/*
* 
* Copyright (C) Patryk Jaworski <regalis@regalis.com.pl>
*
* Visit: http://regalis.com.pl
* 
* This program is free software: you can redistribute it and/or modify
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
* 
*/

#include <avr/io.h>
#include "servo.h"
#include "utils.h"

inline void servo_init() {
	TCCR1A = 0;
	// PB1 as output
	DDRB |= _BV(PB1);
	// Phase and Frequency correct, TOP at ICR1
	TCCR1B |= _BV(WGM13);
	// Non-inverted mode
	TCCR1A |= _BV(COM1A1);
	// 50Hz
	ICR1 = 10000;
	// 8x prescaler
	TCCR1B |= _BV(CS11);
}

void servo_set(uint8_t angle) {
	// pulse width ~540us to 2400us
	OCR1A = map(angle, 0, 180, 256, 1200);
}

