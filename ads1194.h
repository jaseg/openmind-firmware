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



#ifndef __ADS1194_H__
#define __ADS1194_H__
#include <avr/io.h>
#include "spi.h"

#define ADS_PWDN_DDR	DDRC
#define ADS_PWDN_PORT	PORTC
#define ADS_PWDN_PIN	4
#define ADS_RESET_DDR	DDRC
#define ADS_RESET_PORT	PORTC
#define ADS_RESET_PIN	3
#define ADS_CS_DDR	DDRC
#define ADS_CS_PORT	PORTC
#define ADS_CS_PIN	1
#define ADS_START_DDR	DDRC
#define ADS_START_PORT	PORTC
#define ADS_START_PIN	2
#define ADS_DRDY_INPUT	PINC
#define ADS_DRDY_PIN	0

typedef struct {
	struct {
		uint8_t padding:4;
		uint8_t loff_statp:8;
		uint8_t loff_statn:8;
		uint8_t gpio_data:4;
	} stat;
	uint16_t ch[4];
} sample_data;

//API functions
extern void ads_init_pass1(void);
extern void ads_init_pass2(void);
extern void ads_init_pass3(void);
extern void ads_init_pass4(void);
extern void ads_read_registers(uint8_t address, uint8_t count, uint8_t* buffer);
extern void ads_write_registers(uint8_t address, uint8_t count, uint8_t* buffer);
extern uint8_t ads_read_register(uint8_t address);
extern void ads_write_register(uint8_t address, uint8_t value);
extern uint8_t ads_spi_send(uint8_t data);
inline uint8_t ads_data_ready(void);
void ads_read(sample_data* sample);

//Low-level functions
inline void ads_select(void);
inline void ads_deselect(void);

//ADS1X9X SPI commands
#define ADS_CMD_WAKEUP	0x02
#define ADS_CMD_STANDBY	0x04
#define ADS_CMD_RESET	0x06
#define ADS_CMD_START	0x08
#define ADS_CMD_STOP	0x0A
#define ADS_CMD_RDATAC	0x10
#define ADS_CMD_SDATAC	0x11
#define ADS_CMD_RDATA	0x12

//ADS1X9X command macros
#define ads_wakeup()	ads_spi_send(ADS_CMD_WAKEUP)
#define ads_standby()	ads_spi_send(ADS_CMD_STANDBY)
#define ads_reset()	ads_spi_send(ADS_CMD_RESET)
#define ads_start()	ads_spi_send(ADS_CMD_START)
#define ads_stop()	ads_spi_send(ADS_CMD_STOP)
#define ads_rdatac()	ads_spi_send(ADS_CMD_RDATAC)
#define ads_sdatac()	ads_spi_send(ADS_CMD_SDATAC)
#define ads_rdata()	ads_spi_send(ADS_CMD_RDATA)

//ADS119X register addresses
#define ADS_REG_ID		0x00
#define ADS_REG_CONFIG1		0x01
#define ADS_REG_CONFIG2		0x02
#define ADS_REG_CONFIG3		0x03
#define ADS_REG_LOFF		0x04
#define ADS_REG_CH1SET		0x05
#define ADS_REG_CH2SET		0x06
#define ADS_REG_CH3SET		0x07
#define ADS_REG_CH4SET		0x08
#define ADS_REG_CH5SET		0x09
#define ADS_REG_CH6SET		0x0A
#define ADS_REG_CH7SET		0x0B
#define ADS_REG_CH8SET		0x0C
#define ADS_REG_RLD_SENSP	0x0D
#define ADS_REG_RLD_SENSN	0x0E
#define ADS_REG_LOFF_SENSP	0x0F
#define ADS_REG_LOFF_SENSN	0x10
#define ADS_REG_LOFF_FLIP	0x11
#define ADS_REG_LOFF_STATP	0x12
#define ADS_REG_LOFF_STATN	0x13
#define ADS_REG_GPIO		0x14
#define ADS_REG_PACE		0x15
//0x16: reserved.
#define ADS_REG_CONFIG4		0x17
#define ADS_REG_WCT1		0x18
#define ADS_REG_WCT2		0x19

inline void ads_select(){
	ADS_CS_PORT &= ~(1<<ADS_CS_PIN);
}

inline void ads_deselect(){
	ADS_CS_PORT |= (1<<ADS_CS_PIN);
}

/* This method tests whether the ads signalizes the readiness of data by pulling
 * its !DRDY pin low.
 */
inline uint8_t ads_data_ready(){
	return !(ADS_DRDY_INPUT&ADS_DRDY_PIN);
}

#endif//__ADS1194_H__
