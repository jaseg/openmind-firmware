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

#include "spi.h"

/* Caution: this function sets the SS pin to output. The SS pin is not needed,
 * but must be an output.
 */
void spi_init(){
	SPI_DDR |= (1<<MOSI_PIN) | (1<<SCK_PIN) | (1<<SS_PIN);
	//SPI enabled, master, \frac{f_{osc}}{64}=62500kHz data rate
	//SPI mode 1, it took a few days to figure that out...
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPHA);
}

uint8_t spi_send(uint8_t data){
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}

void spi_read(uint8_t* buf, uint8_t len){
	uint8_t* end=buf+(len-1);
	while(buf!=end){
		*(buf++)=spi_send(0x00);
	}
}

