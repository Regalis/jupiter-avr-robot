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

#ifndef __ENGINES_H_
#define __ENGINES_H_

#define ENGINE1 0x01
#define ENGINE2 0x02
#define ENGINE_RIGHT 0x01
#define ENGINE_LEFT 0x02

/** Engines inittialization (set DDRX values)
 * WARNING, this function will configure
 * Timer/Counter2
 */
void engine_init();

/** Run engine forward
 * @param engine ENGINE_RIGHT, ENGINE_LEFT (you can use bitwise OR)
 */
void engine_forward(uint8_t engine);

/** Run engine backward
 * @param engine ENGINE_RIGHT, ENGINE_LEFT (you can use bitwise OR)
 */
void engine_backward(uint8_t engine);


/** Stop engine
 * @param engine ENGINE_RIGHT, ENGINE_LEFT (you can use bitwise OR)
 */
void engine_stop(uint8_t engine);

/** Stop all engines */
void engine_stop_all();

/** Set engines speed
 * @param speed value from 0 to 100
 */
void engine_set_speed(uint8_t speed);

/** Get current engine speed
 * @return current engine speed (0 to 100)
 */
uint8_t engine_get_speed();

#endif
