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


#include "main.h"
#include "ads1194.h"
#include <util/delay.h>

int main(void){
	ads_init_pass1();
	DDRD |= 0x1C;
	_delay_ms(500); //Wait for the power supplies to settle (Should not need that much time)
	ads_init_pass2();
	_delay_ms(1000); //Wait for the ads to initialize...
	ads_init_pass3();
	_delay_ms(4);
	_delay_ms(500); //Wait for the ads's internal reference to settle
	ads_init_pass4();
	DDRD|=0x02;
	while(1){
		PORTD|=0x02;
		ads_read_register(ADS_REG_ID);
		PORTD&=0xFD;
		_delay_us(100);
	}
	//The ads is ready for use!
	uint8_t val=0;
	while(1){
		val = ads_read_register(ADS_REG_ID);
		uint8_t i=0;
		while(i<2){
			uint8_t tmp=val;
			if(i)
				tmp&=0x0F;
			else
				tmp>>=4;
			for(uint8_t j=0; j<tmp; j++){
				PORTD |= 0x10;
				_delay_ms(250);
				PORTD &= ~0x10;
				_delay_ms(250);
			}
			PORTD |= 0x08;
			_delay_ms(500);
			PORTD &= ~0x08;
			_delay_ms(500);
			i++;
		}
		PORTD |= 0x04;
		_delay_ms(2000);
		PORTD &= ~0x04;
		_delay_ms(2000);
	}
}

