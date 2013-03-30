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
	engine_init();
	servo_init();
	servo_set(SERVO1, 90);
	servo_set(SERVO2, 85);
	serial_init(9600);
	serial_println("Hello, I'm Jupiter");
	ultrasonic_init();
	sei();
	_delay_ms(1000);
	while (1) {
		engine_set_speed(50);
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

		_delay_ms(3000);
		engine_forward(ENGINE_LEFT | ENGINE_RIGHT);
		engine_set_speed(0);
		_delay_ms(3000);
		engine_set_speed(20);
		_delay_ms(3000);
		engine_set_speed(40);

		engine_backward(ENGINE_LEFT);
		_delay_ms(3000);
		engine_forward(ENGINE_LEFT);

		_delay_ms(3000);
		engine_set_speed(25);
		_delay_ms(3000);
		engine_set_speed(100);
		_delay_ms(3000);
		engine_set_speed(25);
		_delay_ms(3000);
		engine_set_speed(100);
		_delay_ms(3000);
	}
}
