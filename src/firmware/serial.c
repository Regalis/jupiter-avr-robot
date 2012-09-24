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
#include "serial.h"

inline void serial_init(uint32_t baud_rate) {
	uint16_t ubrr = 8000000 / 16 / baud_rate - 1;
	UBRRH = (uint8_t)(ubrr >> 8);
	UBRRL = (uint8_t)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1 << RXEN) | ( 1 << TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = ( 1 << URSEL) | ( 1 << USBS) | (3 << UCSZ0);
}

void serial_putc(uint8_t byte) {
	while (!(UCSRA & _BV(UDRE))) {}
	UDR = byte;
}

void serial_puts(const char *str) {
	while (*str != '\0')
		serial_putc(*(str++));
}

void serial_println(const char *str) {
	serial_puts(str);
	serial_putc('\n');
}
