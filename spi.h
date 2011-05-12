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

#endif//__SPI_H__
