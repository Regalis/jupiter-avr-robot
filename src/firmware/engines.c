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
#include <util/delay.h>

#include "engines.h"
#include "utils.h"

#define ENGINE_LEFT_I1_DDR DDRB
#define ENGINE_LEFT_I1_PORT PORTB
#define ENGINE_LEFT_I1_PIN 0
#define ENGINE_LEFT_I2_DDR DDRD
#define ENGINE_LEFT_I2_PORT PORTD
#define ENGINE_LEFT_I2_PIN 7

#define ENGINE_RIGHT_I1_DDR DDRD
#define ENGINE_RIGHT_I1_PORT PORTD
#define ENGINE_RIGHT_I1_PIN 6
#define ENGINE_RIGHT_I2_DDR DDRD
#define ENGINE_RIGHT_I2_PORT PORTD
#define ENGINE_RIGHT_I2_PIN 5

void engine_init() {
	DDRB |= _BV(PB3);
	// set speed to 0
	OCR2 = 0x00;
	// Phase correct mode, non inverting mode
	// 64x prescaler (244Hz)
	TCCR2 |= _BV(WGM20) | _BV(COM21) | _BV(CS22);

	ENGINE_LEFT_I1_DDR |= _BV(ENGINE_LEFT_I1_PIN);
	ENGINE_LEFT_I2_DDR |= _BV(ENGINE_LEFT_I2_PIN);
	ENGINE_RIGHT_I1_DDR |= _BV(ENGINE_RIGHT_I1_PIN);
	ENGINE_RIGHT_I2_DDR |= _BV(ENGINE_RIGHT_I2_PIN);
	engine_stop_all();
}

void engine_stop(uint8_t engine) {
	if (engine & ENGINE_LEFT) {
		ENGINE_LEFT_I1_PORT &= ~(_BV(ENGINE_LEFT_I1_PIN));
		ENGINE_LEFT_I2_PORT &= ~(_BV(ENGINE_LEFT_I2_PIN));
	}
	if (engine & ENGINE_RIGHT) {
		ENGINE_RIGHT_I1_PORT &= ~(_BV(ENGINE_RIGHT_I1_PIN));
		ENGINE_RIGHT_I2_PORT &= ~(_BV(ENGINE_RIGHT_I2_PIN));
	}
}

void engine_forward(uint8_t engine) {
	if (engine & ENGINE_LEFT) {
		engine_stop(ENGINE_LEFT);
		_delay_us(100);
		ENGINE_LEFT_I1_PORT |= _BV(ENGINE_LEFT_I1_PIN);
	}
	if (engine & ENGINE_RIGHT) {
		engine_stop(ENGINE_RIGHT);
		_delay_us(100);
		ENGINE_RIGHT_I1_PORT |= _BV(ENGINE_RIGHT_I1_PIN);
	}
}

void engine_backward(uint8_t engine) {
	if (engine & ENGINE_LEFT) {
		engine_stop(ENGINE_LEFT);
		_delay_us(100);
		ENGINE_LEFT_I2_PORT |= _BV(ENGINE_LEFT_I2_PIN);
	}
	if (engine & ENGINE_RIGHT) {
		engine_stop(ENGINE_RIGHT);
		_delay_us(100);
		ENGINE_RIGHT_I2_PORT |= _BV(ENGINE_RIGHT_I2_PIN);
	}
}

inline void engine_stop_all() {
	engine_stop(ENGINE_LEFT | ENGINE_RIGHT);
}

void engine_set_speed(uint8_t speed) {
	OCR2 = (uint8_t)map(speed, 0, 100, 0, 255);
}

uint8_t engine_get_speed() {
	return (uint8_t)map(OCR2, 0, 255, 0, 100);
}

