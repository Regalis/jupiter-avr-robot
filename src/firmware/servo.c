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
	// PB1 and PB2 as output
	DDRB |= _BV(PB1) | _BV(PB2);
	// Phase and Frequency correct, TOP at ICR1
	TCCR1B |= _BV(WGM13);
	// Non-inverted mode for OC1 and OC2
	TCCR1A |= _BV(COM1A1);
	TCCR1A |= _BV(COM1B1);
	// 50Hz
	ICR1 = 10000;
	// 8x prescaler
	TCCR1B |= _BV(CS11);
	OCR1A = 0;
	OCR1B = 0;
}

void servo_set(uint8_t servo_select, uint8_t angle) {
	// pulse width ~540us to 2400us
	long angle_value = map(angle, 0, 180, 256, 1200);
	if (servo_select & SERVO1) 
		OCR1A = angle_value;
	if (servo_select & SERVO2)
		OCR1B = angle_value;
}

