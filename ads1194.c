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


#include <util/delay.h>
#include "ads1194.h"
#include "spi.h"

/* FIXME/Note:
 * This method assumes nothing else than the ADS is on the spi when the !CS pin of the ADS is
 * pulled low. If you want to change this, you will have to pull it low each time a command or
 * data is sent/to be received to/from the ADS.
 * 
 * This method is run right at the startup of the avr.
 * 
 * For future boards the cksel input should also be considered here. On the
 * current revision it is set by a solder jumper on the board.
 */
void ads_init_pass1(){
	spi_init();
	ADS_PWDN_DDR	|= 1<<ADS_PWDN_PIN;
	ADS_RESET_DDR	|= 1<<ADS_RESET_PIN;
	ADS_CS_DDR	|= 1<<ADS_CS_PIN;
	ADS_START_DDR	|= 1<<ADS_START_PIN;
}

/* This method is run when the power supplies are stable. If the avr has a
 * sufficiently high startup delay it may be run right after pass1. Whether the
 * startup delay is o.k. (the ads's datasheet says all pins must be "low" on
 * startup, which collides with the avr's high-impedance policy) has yet to be
 * found out... 
 */
void ads_init_pass2(){
	//This would be the place to set the ads's cksel line.
	ADS_RESET_PORT	|= 1<<ADS_RESET_PIN;
	ADS_PWDN_PORT	|= 1<<ADS_PWDN_PIN;
}

/* This method is run t_por after pass2. t_por is 2^16 t_clk, i.e about 33ms. For
 * safety (since according to the datasheet the 2^16 is a minimum value and we
 * are not in a hurry) I would recommend about 50ms.
 * I just noticed: If I understand the datasheet correctly, a flow chart on its
 * bottom advises this delay to be 1s.
 */
void ads_init_pass3(){
	ADS_RESET_PORT &= ~(1<<ADS_RESET_PIN);
	_delay_us(16); //spec: 2t_clk ~= 1us
	ADS_RESET_PORT |= 1<<ADS_RESET_PIN;
	_delay_us(16); //according to the datasheet at least 18 t_clk
	               //(where t_clk means the ads's t_clk i.e. 1/2048kHz) 
	spi_send(ADS_SDATAC);
	spi_send(ADS_STOP);
	//enable internal reference, set vref to 2.4V
	//ads_write_register(ADS_REG_CONFIG3, 0xE0);
}

/* This method is run when the ads's internal reference has settled. So far I
 * did only estimate the time needed for that, I begin with 500ms.
 */
void ads_init_pass4(){
	
	//Disable daisy-chain mode, set sample rate to 125SPS
	ads_write_register(ADS_REG_CONFIG1, 0x46);
	//Nothing special
	ads_write_register(ADS_REG_CONFIG2, 0x20);
	//Set PGA gain to 6, short inputs
	ads_write_register(ADS_REG_CH1SET, 0x01);
	ads_write_register(ADS_REG_CH2SET, 0x01);
	ads_write_register(ADS_REG_CH3SET, 0x01);
	ads_write_register(ADS_REG_CH4SET, 0x01);
	//Congratulations, your ADS1194 just went alive!
	
}

/* These methods assume the spi interface is clocked at 4MHz at maximum. According to the ads's
 * datasheet, with 4MHz everything is fine, but at some higher spi frequencies a delay is needed
 * between the two bytes of the command.
 * FIXME The whole spi stuff is still synchronous, so a slow spi speed means a slow program.
 */
void ads_read_registers(uint8_t address, uint8_t count, uint8_t* buffer){
	spi_send(0x20 | (address&0x0F));
	spi_send((count-1)&0x1F);
	for(uint8_t i=0;i<count;i++){
		buffer[i] = spi_send(0x00);
	}
}

void ads_write_registers(uint8_t address, uint8_t count, uint8_t* buffer){
	spi_send(0x40 | (address&0x0F));
	spi_send((count-1)&0x1F);
	for(uint8_t i=0;i<count;i++){
		spi_send(buffer[i]);
	}
}

uint8_t ads_read_register(uint8_t address){
	spi_send(0x20 | (address&0x0F));
	_delay_us(20);
	spi_send(0x00);
	_delay_us(20);
	return spi_send(0x00);
}

void ads_write_register(uint8_t address, uint8_t value){
	spi_send(0x40 | (address&0x0F));
	spi_send(0x00);
	spi_send(value);
}

//This is here in case multi-slave capabilities are added somewhere in the
//future.
void ads_send_command(uint8_t command){
	spi_send(command);
}

