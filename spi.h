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

//SPI interface driver

#ifndef __SPI_H__
#define __SPI_H__
#include <avr/io.h>

//Pin definitions (for ATMega8)
#define SPI_DDR	DDRB
#define MOSI_PIN	3
#define SCK_PIN		5
#define SS_PIN		2

extern void spi_init(void);
extern uint8_t spi_send(uint8_t data);
extern void spi_read(uint8_t* buf, uint8_t len);

#endif//__SPI_H__
