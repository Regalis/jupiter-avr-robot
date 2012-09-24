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

#ifndef __SERIAL_H_
#define __SERIAL_H_

/** Initialize serial port
 * @baud_rate: serial port baud rate in bps
 */
void serial_init(uint32_t baud_rate);

/** Send single byte
 * @param byte unsigned 8-bit value
 */
void serial_putc(uint8_t byte);

/** Send string
 * @param str C string
 */
void serial_puts(const char *str);

/** Send string and new line character (\n)
 * @param str C string
 */
void serial_println(const char *str);

#endif
