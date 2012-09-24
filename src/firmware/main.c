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
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "serial.h"
#include "ultrasonic.h"
#include "servo.h"
#include "utils.h"
#include "engines.h"

int main() {
	char *buffer = (char*)calloc(100, sizeof(char));
	servo_init();
	serial_init(9600);
	serial_println("Hello, I'm Jupiter");
	ultrasonic_init();
	engine_init();
	sei();
	_delay_ms(1000);
	while (1) {
		engine_forward(ENGINE_LEFT | ENGINE_RIGHT);
		_delay_ms(3000);
		engine_stop_all();
		_delay_ms(500);
		engine_backward(ENGINE_LEFT | ENGINE_RIGHT);
		_delay_ms(3000);
		engine_stop_all();
		_delay_ms(500);

		engine_forward(ENGINE_RIGHT);
		_delay_ms(3000);
		engine_stop_all();
		_delay_ms(500);
		engine_forward(ENGINE_LEFT);
		_delay_ms(3000);
		engine_stop_all();
		_delay_ms(500);

		engine_backward(ENGINE_RIGHT);
		_delay_ms(3000);
		engine_stop_all();
		_delay_ms(500);
		engine_backward(ENGINE_LEFT);
		_delay_ms(3000);
		engine_stop_all();
		_delay_ms(500);
	}
}
