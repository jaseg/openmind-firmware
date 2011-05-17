
#include "debug.h"
#include "spi.h"
#include <util/delay.h>

void debug_init(){
	DEBUG_CS_DDR |= (1<<DEBUG_CS_PIN);
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}

void debug_send_c(char c){
	DEBUG_CS_PORT &= ~(1<<DEBUG_CS_PIN);
	spi_send(c);
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}

void debug_send_s(char* str){
	DEBUG_CS_PORT &= ~(1<<DEBUG_CS_PIN);
	char c;
	while(!(c=*(str++))){
		spi_send(c);
	}
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}

void debug_send_hex(uint8_t v){
	DEBUG_CS_PORT &= ~(1<<DEBUG_CS_PIN);
	uint8_t h=v>>4;
	spi_send((h&0x0F)<0x0A?0x30+(h&0x0F):0x37+(h&0x0F));
	_delay_us(20);
	spi_send((v&0x0F)<0x0A?0x30+(v&0x0F):0x37+(v&0x0F));
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}

void debug_send_p(char* s){
	DEBUG_CS_PORT &= ~(1<<DEBUG_CS_PIN);
	char c;
	uint8_t i=0;
	while((c=pgm_read_byte(s++))){
		spi_send(c);
		_delay_us(20);
	}
	DEBUG_CS_PORT |= (1<<DEBUG_CS_PIN);
}
				

