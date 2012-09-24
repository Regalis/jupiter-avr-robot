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
#include <util/atomic.h>
#include <util/delay.h>

#include "ultrasonic.h"
#include "utils.h"

#define ULTRASONIC_MAX 0xFFFF
#define TICK_LENGTH 32
#define false 0
#define true 1
#define bool uint8_t

static uint64_t counter = 0;
static volatile uint16_t signal_length;
static volatile bool busy = false;

static void ultrasonic_wait_low();
static void ultrasonic_wait_high();

ISR(TIMER0_OVF_vect) {
	++counter;
}

ISR(INT0_vect) {
	static uint64_t pulse_start;
	if (MCUCR & _BV(ISC00)) {
		pulse_start = counter;
		ultrasonic_wait_low();
	} else {
		// Counter overflow detection
		if (counter > pulse_start)
			signal_length = counter - pulse_start;
		else
			signal_length = ((uint64_t)0xFFFFFFFF - pulse_start) + counter;
		busy = false;
		ultrasonic_wait_high();
	}
}

static void ultrasonic_wait_high() {
	MCUCR &= ~(_BV(ISC00) | _BV(ISC01));
	/* Wait for rising edge */
	MCUCR |= _BV(ISC00) | _BV(ISC01);
}

static void ultrasonic_wait_low() {
	MCUCR &= ~(_BV(ISC00) | _BV(ISC01));
	/* Wait for falling edge */
	MCUCR |= _BV(ISC01);
}

inline void ultrasonic_init() {
	/* Timer/Counter0 1x prescaler (31250Hz) */
	TCCR0 |= _BV(CS00);
	/* Enable everflow interrupt */
	TIMSK |= _BV(TOIE0);
	/* Set ultrasonic pins */
	DDRD &= ~(_BV(PD2)); // PD2 as input
	PORTD |= _BV(PD2);
	DDRC |= _BV(PC0); // PC0 as output
	/* Wait for rising edge */
	ultrasonic_wait_high();
	/* Enable external interrupt request INT0 */
	GICR |= _BV(INT0);
}

uint64_t ultrasonic_get_ticks() {
	uint64_t ticks;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		ticks = counter;
	}
	return ticks;
}

void ultrasonic_trigger() {
	PORTC |= _BV(PC0);
	_delay_us(15);
	PORTC &= ~(_BV(PC0));
	busy = true;
}

void ultrasonic_trigger_wait() {
	ultrasonic_trigger();
	while (busy) {}
}

uint16_t ultrasonic_get_distance() {
	return (signal_length * TICK_LENGTH) / 57;
}

inline uint16_t ultrasonic_trigger_get_distance() {
	ultrasonic_trigger_wait();
	return ultrasonic_get_distance();
}
