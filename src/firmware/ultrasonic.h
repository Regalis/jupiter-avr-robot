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

#ifndef __ULTRASONIC_H_
#define __ULTRASONIC_H_

/** Initialize ultrasonic sensor
 * Ultrasonic must be connected to specified pins:
 * PD2 - echo pin
 * PC0 - trig pin
 * WARNING, this function will configure
 * Timer/Counter0
 */
void ultrasonic_init();

/** Get number of 31250Hz (32us) ticks
 * @return number of 32us ticks
 */
uint64_t ultrasonic_get_ticks();

/** Trigger ultrasonic sensor (echo request) */ 
void ultrasonic_trigger();

/** Trigger and wait for response */
void ultrasonic_trigger_wait();

/** Get measured distance in centimeters */
uint16_t ultrasonic_get_distance();

/** Trigger, wait for reposonse and get distance */
uint16_t ultrasonic_trigger_get_distance();

#endif
