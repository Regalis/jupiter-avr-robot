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


/** Init servo
 * Servo must be connected to specified pins:
 * PB1, PB2 - servo's control line
 * WARNING, this function will configure
 * 16-bit Timer/Counter1:
 *  Frequency: 50Hz
 *  Mode: Phase and Frequency correct
 *  Prescaler: 8x
 */
void servo_init();

/** Set servo angle:
 * @param servo_select select servro (SERVO1 or/and SERVO2)
 * @param angle value from range 0-180
 */
void servo_set(uint8_t servo_select, uint8_t angle);

#define SERVO1 0x0F
#define SERVO2 0xF0
