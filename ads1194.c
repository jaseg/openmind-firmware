

#include <avr/io.h>
#include <util/delay.h>
#include "ads1194.h"

/* FIXME/Note:
 * This method assumes nothing else than the ADS is on the spi when the !CS pin of the ADS is
 * pulled low. If you want to change this, you will have to pull it low each time a command or
 * data is sent/to be received to/from the ADS.
 * 
 * This method is run right at the startup of the avr.
 */
void init_ads_pass1(){
	ADS_CKSEL_DDR |= 1<<ADS_CKSEL_PIN;
	ADS_PWDN_DDR |= 1<<ADS_PWDN_PIN;
	ADS_RESET_DDR |= 1<<ADS_RESET_PIN;
	ADS_CS_DDR |= 1<<ADS_CS_PIN;
	ADS_START_DDR |= 1<<ADS_START_PIN;
}

//This method is run when the power supplies are stable. If the avr has a
//sufficiently high startup delay it may be run right after pass1. Whether the
//startup delay is o.k. (the ads's datasheet says all pins must be "low" on
//startup, which collides with the avr's high-impedance policy) has yet to be
//found out... 
void init_ads_pass2(){
	//Select the ads's internal clock
	ADS_CKSEL_PORT |= 1<<ADS_CKSEL_PIN;
}

//This method is run t_por after pass2. t_por is 2^16 t_clk, i.e about 33ms. For
//safety (since according to the datasheet the 2^16 is a minimum value and we
//are not in a hurry) I would recommend about 50ms.
void init_ads_pass3(){
	ADS_RESET_PORT &= ~(1<<ADS_RESET_PIN);
	_delay_us(2); //spec: 2t_clk ~= 1us
	ADS_RESET_PORT |= 1<<ADS_RESET_PIN;
	_delay_us(16); //according to the datasheet at least 18 t_clk
	               //(where t_clk means the ads's t_clk i.e. 1/2048kHz) 
	//Congratulations, your ADS1194 just went alive!
}

//These methods assume the spi interface is clocked at 4MHz at maximum. According to the ads's
//datasheet, with 4MHz everything is fine, but at some higher spi frequencies a delay is needed
//between the two bytes of the command.
//FIXME The whole spi stuff is still synchronous, so a slow spi speed means a slow program.
void ads_read_register(uint8_t address, uint8_t count, uint8_t* buffer){
	spi_send(0x20 | (address&0x0F));
	spi_send((count-1)&0x1F);
	while(count--){
		buffer[count] = spi_send(0x00);
	}
}

void ads_write_register(uint8_t address, uint8_t count, uint8_t* buffer){
	spi_send(0x40 | (address&0x0F));
	spi_send((count-1)&0x1F);
	while(count--){
		spi_send(buffer[count]);
	}
}

//This is here in case multi-slave capabilities are added somewhere in the
//future.
void ads_send_command(uint8_t command){
	spi_send(command);
}

