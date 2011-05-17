/*   OpenMind open source eeg adc board firmware
 *   Copyright (C) 2011  Sebastian Götte <s@jaseg.de>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __DEBUG_H__
#define __DEBUG_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

#define DEBUG_CS_DDR	DDRD
#define DEBUG_CS_PORT 	PORTD
#define DEBUG_CS_PIN	6

extern void debug_init(void);
extern void debug_send_c(char c);
extern void debug_send_s(char* str);
extern void debug_send_p(char* s);
extern void debug_send_hex(uint8_t v);
extern void debug_send_hex_raw(uint8_t v);
extern void debug_begin(void);
extern void debug_end(void);

#endif//__DEBUG_H__
