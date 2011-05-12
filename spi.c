
#include "spi.h"

/* Caution: this function sets the SS pin to output. The SS pin is not needed,
 * but must be an output.
 */
void spi_init(){
	SPI_DDR |= (1<<MOSI_PIN) | (1<<SCK_PIN) | (1<<SS_PIN);
	//SPI enabled, master, \frac{f_{osc}}{64}=62500kHz data rate
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1);
}

uint8_t spi_send(uint8_t data){
	SPDR = data;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}

